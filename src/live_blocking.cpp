#include "databento/live_blocking.hpp"

#include <openssl/sha.h>  // SHA256, SHA256_DIGEST_LENGTH

#include <algorithm>  // copy
#include <cctype>
#include <cstdlib>
#include <ios>  //hex, setfill, setw
#include <sstream>

#include "databento/constants.hpp"  //  kApiKeyLength
#include "databento/dbn_decoder.hpp"
#include "databento/exceptions.hpp"  // LiveApiError
#include "databento/log.hpp"
#include "databento/record.hpp"     // Record
#include "databento/symbology.hpp"  // JoinSymbolStrings

using databento::LiveBlocking;

namespace {
constexpr std::size_t kBucketIdLength = 5;
}  // namespace

LiveBlocking::LiveBlocking(ILogReceiver* log_receiver, std::string key,
                           std::string dataset, bool send_ts_out)

    : log_receiver_{log_receiver},
      key_{std::move(key)},
      dataset_{std::move(dataset)},
      gateway_{DetermineGateway()},
      send_ts_out_{send_ts_out},
      client_{gateway_, 13000},
      session_id_{this->Authenticate()} {}

LiveBlocking::LiveBlocking(ILogReceiver* log_receiver, std::string key,
                           std::string dataset, std::string gateway,
                           std::uint16_t port, bool send_ts_out)
    : log_receiver_{log_receiver},
      key_{std::move(key)},
      dataset_{std::move(dataset)},
      gateway_{std::move(gateway)},
      send_ts_out_{send_ts_out},
      client_{gateway_, port},
      session_id_{this->Authenticate()} {}

void LiveBlocking::Subscribe(const std::vector<std::string>& symbols,
                             Schema schema, SType stype_in) {
  Subscribe(symbols, schema, stype_in, UnixNanos{});
}

void LiveBlocking::Subscribe(const std::vector<std::string>& symbols,
                             Schema schema, SType stype_in, UnixNanos start) {
  std::ostringstream sub_msg;
  sub_msg << "schema=" << ToString(schema) << "|stype_in=" << ToString(stype_in)
          << "|symbols="
          << JoinSymbolStrings("LiveBlocking::Subscribe", symbols);
  if (start.time_since_epoch().count()) {
    sub_msg << "|start=" << start.time_since_epoch().count();
  }
  sub_msg << '\n';

  client_.WriteAll(sub_msg.str());
}

void LiveBlocking::Subscribe(const std::vector<std::string>& symbols,
                             Schema schema, SType stype_in,
                             const std::string& start) {
  std::ostringstream sub_msg;
  sub_msg << "schema=" << ToString(schema) << "|stype_in=" << ToString(stype_in)
          << "|symbols="
          << JoinSymbolStrings("LiveBlocking::Subscribe", symbols);
  if (!start.empty()) {
    sub_msg << "|start=" << start;
  }
  sub_msg << '\n';

  client_.WriteAll(sub_msg.str());
}

databento::Metadata LiveBlocking::Start() {
  constexpr auto kMetadataPreludeSize = 8;
  client_.WriteAll("start_session\n");
  client_.ReadExact(buffer_.data(), kMetadataPreludeSize);
  const auto version_and_size = DbnDecoder::DecodeMetadataVersionAndSize(
      reinterpret_cast<std::uint8_t*>(buffer_.data()), kMetadataPreludeSize);
  std::vector<std::uint8_t> meta_buffer(version_and_size.second);
  client_.ReadExact(reinterpret_cast<char*>(meta_buffer.data()),
                    version_and_size.second);
  return DbnDecoder::DecodeMetadataFields(version_and_size.first, meta_buffer);
}

const databento::Record& LiveBlocking::NextRecord() { return *NextRecord({}); }

const databento::Record* LiveBlocking::NextRecord(
    std::chrono::milliseconds timeout) {
  // need some unread unread_bytes
  const auto unread_bytes = buffer_size_ - buffer_idx_;
  if (unread_bytes == 0) {
    const auto read_res = FillBuffer(timeout);
    if (read_res.status == detail::TcpClient::Status::Timeout) {
      return nullptr;
    }
    if (read_res.status == detail::TcpClient::Status::Closed) {
      throw DbnResponseError{"Reached end of DBN stream"};
    }
  }
  // check length
  while (buffer_size_ - buffer_idx_ < BufferRecordHeader()->Size()) {
    const auto read_res = FillBuffer(timeout);
    if (read_res.status == detail::TcpClient::Status::Timeout) {
      return nullptr;
    }
    if (read_res.status == detail::TcpClient::Status::Closed) {
      throw DbnResponseError{"Reached end of DBN stream"};
    }
  }
  current_record_ = Record{BufferRecordHeader()};
  buffer_idx_ += current_record_.Size();
  return &current_record_;
}

void LiveBlocking::Stop() { client_.Close(); }

std::string LiveBlocking::DecodeChallenge() {
  buffer_size_ = client_.ReadSome(buffer_.data(), buffer_.size()).read_size;
  if (buffer_size_ == 0) {
    throw LiveApiError{"Server closed socket during authentication"};
  }
  // first line is version
  std::string response{buffer_.data(), buffer_size_};
  {
    std::ostringstream log_ss;
    log_ss << __PRETTY_FUNCTION__ << " Challenge: " << response;
    log_receiver_->Receive(LogLevel::Debug, log_ss.str());
  }
  auto first_nl_pos = response.find('\n');
  if (first_nl_pos == std::string::npos) {
    throw LiveApiError::UnexpectedMsg("Received malformed initial message",
                                      response);
  }
  const auto version_line = response.substr(0, first_nl_pos);
  const auto find_start = first_nl_pos + 1;
  auto next_nl_pos = find_start == response.length()
                         ? std::string::npos
                         : response.find('\n', find_start);
  while (next_nl_pos == std::string::npos) {
    // read more
    buffer_size_ +=
        client_.ReadSome(&buffer_[buffer_size_], buffer_.size() - buffer_size_)
            .read_size;
    if (buffer_size_ == 0) {
      throw LiveApiError{"Server closed socket during authentication"};
    }
    response = {buffer_.data(), buffer_size_};
    next_nl_pos = response.find('\n', find_start);
  }
  const auto challenge_line =
      response.substr(find_start, next_nl_pos - find_start);
  if (challenge_line.compare(0, 4, "cram") != 0) {
    throw LiveApiError::UnexpectedMsg(
        "Did not receive CRAM challenge when expected", challenge_line);
  }
  const auto equal_pos = challenge_line.find('=');
  if (equal_pos == std::string::npos || equal_pos + 1 > challenge_line.size()) {
    throw LiveApiError::UnexpectedMsg("Received malformed CRAM challenge",
                                      challenge_line);
  }
  return challenge_line.substr(equal_pos + 1);
}

std::string LiveBlocking::DetermineGateway() const {
  std::ostringstream gateway;
  for (const char c : dataset_) {
    gateway << (c == '.' ? '-' : static_cast<char>(std::tolower(c)));
  }
  gateway << ".lsg.databento.com";
  return gateway.str();
}

std::uint64_t LiveBlocking::Authenticate() {
  const std::string challenge_key = DecodeChallenge() + '|' + key_;

  const std::string auth = GenerateCramReply(challenge_key);
  const std::string req = EncodeAuthReq(auth);
  client_.WriteAll(req);
  const std::uint64_t session_id = DecodeAuthResp();

  std::ostringstream log_ss;
  log_ss << __PRETTY_FUNCTION__
         << " Successfully authenticated with session_id " << session_id;
  log_receiver_->Receive(LogLevel::Info, log_ss.str());

  return session_id;
}

std::string LiveBlocking::GenerateCramReply(const std::string& challenge_key) {
  std::array<unsigned char, SHA256_DIGEST_LENGTH> sha{};
  const unsigned char* sha_res =
      ::SHA256(reinterpret_cast<const unsigned char*>(challenge_key.c_str()),
               challenge_key.size(), sha.data());
  if (sha_res == nullptr) {
    throw LiveApiError{"Unable to generate SHA 256"};
  }

  std::ostringstream auth_stream;
  for (const unsigned char c : sha) {
    auth_stream << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<std::uint16_t>(c);
  }
  auth_stream << '-' << key_.substr(kApiKeyLength - kBucketIdLength);
  return auth_stream.str();
}

std::string LiveBlocking::EncodeAuthReq(const std::string& auth) {
  std::ostringstream reply_stream;
  reply_stream << "auth=" << auth << "|dataset=" << dataset_ << "|encoding=dbn|"
               << "ts_out=" << send_ts_out_ << '\n';
  return reply_stream.str();
}

std::uint64_t LiveBlocking::DecodeAuthResp() {
  // handle split packet read
  std::array<char, kMaxStrLen>::const_iterator nl_it;
  buffer_size_ = 0;
  do {
    buffer_idx_ = buffer_size_;
    const auto read_size =
        client_.ReadSome(&buffer_[buffer_idx_], buffer_.size() - buffer_idx_)
            .read_size;
    if (read_size == 0) {
      throw LiveApiError{
          "Unexpected end of message received from server after replying to "
          "CRAM"};
    }
    buffer_size_ += read_size;
    nl_it = std::find(buffer_.begin() + buffer_idx_,
                      buffer_.begin() + buffer_size_, '\n');
  } while (nl_it == buffer_.end());
  const std::string response{buffer_.cbegin(), nl_it};
  {
    std::ostringstream log_ss;
    log_ss << __PRETTY_FUNCTION__ << " Authentication response: " << response;
    log_receiver_->Receive(LogLevel::Debug, log_ss.str());
  }
  // set in case Read call also read records. One beyond newline
  buffer_idx_ = response.length() + 1;

  std::size_t pos{};
  bool found_success{};
  bool is_error{};
  std::uint64_t session_id = 0;
  std::string err_details;
  while (true) {
    const size_t count = response.find('|', pos);
    if (count == response.length() - 1) {
      break;
    }
    // passing count = npos to substr will take remainder of string
    const std::string kv_pair = response.substr(pos, count - pos);
    const std::size_t eq_pos = kv_pair.find('=');
    if (eq_pos == std::string::npos) {
      throw LiveApiError::UnexpectedMsg("Malformed authentication response",
                                        response);
    }
    const std::string key = kv_pair.substr(0, eq_pos);
    if (key == "success") {
      found_success = true;
      if (kv_pair.substr(eq_pos + 1) != "1") {
        is_error = true;
      }
    } else if (key == "error") {
      err_details = kv_pair.substr(eq_pos + 1);
    } else if (key == "session_id") {
      session_id = std::stoull(kv_pair.substr(eq_pos + 1));
    }
    // no more keys to parse
    if (count == std::string::npos) {
      break;
    }
    pos = count + 1;
  }
  if (!found_success) {
    throw LiveApiError{
        "Did not receive success indicator from authentication attempt"};
  }
  if (is_error) {
    throw InvalidArgumentError{"LiveBlocking::LiveBlocking", "key",
                               "Failed to authenticate: " + err_details};
  }
  return session_id;
}

databento::detail::TcpClient::Result LiveBlocking::FillBuffer(
    std::chrono::milliseconds timeout) {
  // Shift data forward
  std::copy(buffer_.cbegin() + static_cast<std::ptrdiff_t>(buffer_idx_),
            buffer_.cend(), buffer_.begin());
  buffer_size_ -= buffer_idx_;
  buffer_idx_ = 0;
  const auto read_res = client_.ReadSome(
      &buffer_[buffer_size_], buffer_.size() - buffer_size_, timeout);
  buffer_size_ += read_res.read_size;
  return read_res;
}

databento::RecordHeader* LiveBlocking::BufferRecordHeader() {
  return reinterpret_cast<RecordHeader*>(&buffer_[buffer_idx_]);
}
