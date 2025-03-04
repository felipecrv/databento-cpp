#include "databento/enums.hpp"

#include <cstdint>
#include <ostream>
#include <string>

#include "databento/exceptions.hpp"  // InvalidArgumentError

namespace databento {
const char* UrlFromGateway(HistoricalGateway gateway) {
  switch (gateway) {
    case HistoricalGateway::Bo1: {
      return "https://hist.databento.com";
    }
    default: {
      throw InvalidArgumentError{
          "UrlFromGateway", "gateway",
          "unknown value " +
              std::to_string(static_cast<std::uint8_t>(gateway))};
    }
  }
}

const char* ToString(Schema schema) {
  switch (schema) {
    case Schema::Mbo: {
      return "mbo";
    }
    case Schema::Mbp1: {
      return "mbp-1";
    }
    case Schema::Mbp10: {
      return "mbp-10";
    }
    case Schema::Tbbo: {
      return "tbbo";
    }
    case Schema::Trades: {
      return "trades";
    }
    case Schema::Ohlcv1S: {
      return "ohlcv-1s";
    }
    case Schema::Ohlcv1M: {
      return "ohlcv-1m";
    }
    case Schema::Ohlcv1H: {
      return "ohlcv-1h";
    }
    case Schema::Ohlcv1D: {
      return "ohlcv-1d";
    }
    case Schema::Definition: {
      return "definition";
    }
    case Schema::Imbalance: {
      return "imbalance";
    }
    case Schema::Statistics: {
      return "statistics";
    }
    case Schema::Status: {
      return "status";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(Encoding encoding) {
  switch (encoding) {
    case Encoding::Dbn: {
      return "dbn";
    }
    case Encoding::Csv: {
      return "csv";
    }
    case Encoding::Json: {
      return "json";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(FeedMode mode) {
  switch (mode) {
    case FeedMode::Historical: {
      return "historical";
    }
    case FeedMode::HistoricalStreaming: {
      return "historical-streaming";
    }
    case FeedMode::Live: {
      return "live";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(Compression compression) {
  switch (compression) {
    case Compression::None: {
      return "none";
    }
    case Compression::Zstd: {
      return "zstd";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(SType stype) {
  switch (stype) {
    case SType::InstrumentId: {
      return "instrument_id";
    }
    case SType::RawSymbol: {
      return "raw_symbol";
    }
    case SType::Continuous: {
      return "continuous";
    }
    case SType::Parent: {
      return "parent";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(SplitDuration duration_interval) {
  switch (duration_interval) {
    case SplitDuration::Day: {
      return "day";
    }
    case SplitDuration::Week: {
      return "week";
    }
    case SplitDuration::Month: {
      return "month";
    }
    case SplitDuration::None: {
      return "none";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(Packaging packaging) {
  switch (packaging) {
    case Packaging::None: {
      return "none";
    }
    case Packaging::Zip: {
      return "zip";
    }
    case Packaging::Tar: {
      return "tar";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(Delivery delivery) {
  switch (delivery) {
    case Delivery::Download: {
      return "download";
    }
    case Delivery::S3: {
      return "s3";
    }
    case Delivery::Disk: {
      return "disk";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(JobState state) {
  switch (state) {
    case JobState::Received: {
      return "received";
    }
    case JobState::Queued: {
      return "queued";
    }
    case JobState::Processing: {
      return "processing";
    }
    case JobState::Done: {
      return "done";
    }
    case JobState::Expired: {
      return "expired";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(DatasetCondition condition) {
  switch (condition) {
    case DatasetCondition::Available: {
      return "available";
    }
    case DatasetCondition::Degraded: {
      return "degraded";
    }
    case DatasetCondition::Pending: {
      return "pending";
    }
    case DatasetCondition::Missing: {
      return "missing";
    }
    case DatasetCondition::Bad: {  // Deprecated
      return "bad";
    }
    default: {
      return "unknown";
    }
  }
}

const char* ToString(RType rtype) {
  switch (rtype) {
    case RType::Mbp0: {
      return "Mbp0";
    }
    case RType::Mbp1: {
      return "Mbp1";
    }
    case RType::Mbp10: {
      return "Mbp10";
    }
    case RType::OhlcvDeprecated: {
      return "OhlcvDeprecated";
    }
    case RType::Ohlcv1S: {
      return "Ohlcv1S";
    }
    case RType::Ohlcv1M: {
      return "Ohlcv1M";
    }
    case RType::Ohlcv1H: {
      return "Ohlcv1H";
    }
    case RType::Ohlcv1D: {
      return "Ohlcv1D";
    }
    case RType::InstrumentDef: {
      return "InstrumentDef";
    }
    case RType::Imbalance: {
      return "Imbalance";
    }
    case RType::Error: {
      return "Error";
    }
    case RType::SymbolMapping: {
      return "SymbolMapping";
    }
    case RType::System: {
      return "System";
    }
    case RType::Statistics: {
      return "Statistics";
    }
    case RType::Mbo: {
      return "Mbo";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(Action action) {
  switch (action) {
    case Action::Modify: {
      return "Modify";
    }
    case Action::Trade: {
      return "Trade";
    }
    case Action::Fill: {
      return "Fill";
    }
    case Action::Cancel: {
      return "Cancel";
    }
    case Action::Add: {
      return "Add";
    }
    case Action::Clear: {
      return "Clear";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(Side side) {
  switch (side) {
    case Side::Ask: {
      return "Ask";
    }
    case Side::Bid: {
      return "Bid";
    }
    case Side::None: {
      return "None";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(InstrumentClass instrument_class) {
  switch (instrument_class) {
    case instrument_class::Bond: {
      return "Bond";
    }
    case instrument_class::Call: {
      return "Call";
    }
    case instrument_class::Future: {
      return "Future";
    }
    case instrument_class::Stock: {
      return "Stock";
    }
    case instrument_class::MixedSpread: {
      return "MixedSpread";
    }
    case instrument_class::Put: {
      return "Put";
    }
    case instrument_class::FutureSpread: {
      return "FutureSpread";
    }
    case instrument_class::OptionSpread: {
      return "OptionSpread";
    }
    case instrument_class::FxSpot: {
      return "FxSpot";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(MatchAlgorithm match_algorithm) {
  switch (match_algorithm) {
    case match_algorithm::Fifo: {
      return "Fifo";
    }
    case match_algorithm::Configurable: {
      return "Configurable";
    }
    case match_algorithm::ProRata: {
      return "ProRata";
    }
    case match_algorithm::FifoLmm: {
      return "FifoLmm";
    }
    case match_algorithm::ThresholdProRata: {
      return "ThresholdProRata";
    }
    case match_algorithm::FifoTopLmm: {
      return "FifoTopLmm";
    }
    case match_algorithm::ThresholdProRataLmm: {
      return "ThresholdProRataLmm";
    }
    case match_algorithm::EurodollarOptions: {
      return "EurodollarOptions";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(SecurityUpdateAction update_action) {
  switch (update_action) {
    case SecurityUpdateAction::Add: {
      return "Add";
    }
    case SecurityUpdateAction::Modify: {
      return "Modify";
    }
    case SecurityUpdateAction::Delete: {
      return "Delete";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(UserDefinedInstrument user_def_instr) {
  switch (user_def_instr) {
    case UserDefinedInstrument::No: {
      return "No";
    }
    case UserDefinedInstrument::Yes: {
      return "Yes";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(StatType stat_type) {
  switch (stat_type) {
    case StatType::OpeningPrice: {
      return "OpeningPrice";
    }
    case StatType::IndicativeOpeningPrice: {
      return "IndicativeOpeningPrice";
    }
    case StatType::SettlementPrice: {
      return "SettlementPrice";
    }
    case StatType::TradingSessionLowPrice: {
      return "TradingSessionLowPrice";
    }
    case StatType::TradingSessionHighPrice: {
      return "TradingSessionHighPrice";
    }
    case StatType::ClearedVolume: {
      return "ClearedVolume";
    }
    case StatType::LowestOffer: {
      return "LowestOffer";
    }
    case StatType::HighestBid: {
      return "HighestBid";
    }
    case StatType::OpenInterest: {
      return "OpenInterest";
    }
    case StatType::FixingPrice: {
      return "FixingPrice";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(StatUpdateAction stat_update_action) {
  switch (stat_update_action) {
    case StatUpdateAction::New: {
      return "New";
    }
    case StatUpdateAction::Delete: {
      return "Delete";
    }
    default: {
      return "Unknown";
    }
  }
}

const char* ToString(VersionUpgradePolicy upgrade_policy) {
  switch (upgrade_policy) {
    case VersionUpgradePolicy::AsIs: {
      return "AsIs";
    }
    case VersionUpgradePolicy::Upgrade: {
      return "Upgrade";
    }
    default: {
      return "Unknown";
    }
  }
}

std::ostream& operator<<(std::ostream& out, Schema schema) {
  out << ToString(schema);
  return out;
}

std::ostream& operator<<(std::ostream& out, Encoding encoding) {
  out << ToString(encoding);
  return out;
}

std::ostream& operator<<(std::ostream& out, FeedMode mode) {
  out << ToString(mode);
  return out;
}

std::ostream& operator<<(std::ostream& out, Compression compression) {
  out << ToString(compression);
  return out;
}

std::ostream& operator<<(std::ostream& out, SType stype) {
  out << ToString(stype);
  return out;
}

std::ostream& operator<<(std::ostream& out, SplitDuration duration_interval) {
  out << ToString(duration_interval);
  return out;
}

std::ostream& operator<<(std::ostream& out, Packaging packaging) {
  out << ToString(packaging);
  return out;
}

std::ostream& operator<<(std::ostream& out, Delivery delivery) {
  out << ToString(delivery);
  return out;
}

std::ostream& operator<<(std::ostream& out, JobState state) {
  out << ToString(state);
  return out;
}

std::ostream& operator<<(std::ostream& out, DatasetCondition condition) {
  out << ToString(condition);
  return out;
}

std::ostream& operator<<(std::ostream& out, RType rtype) {
  out << ToString(rtype);
  return out;
}

std::ostream& operator<<(std::ostream& out, Action action) {
  out << ToString(action);
  return out;
}

std::ostream& operator<<(std::ostream& out, Side side) {
  out << ToString(side);
  return out;
}

std::ostream& operator<<(std::ostream& out, InstrumentClass instrument_class) {
  out << ToString(instrument_class);
  return out;
}

std::ostream& operator<<(std::ostream& out, MatchAlgorithm match_algorithm) {
  out << ToString(match_algorithm);
  return out;
}

std::ostream& operator<<(std::ostream& out,
                         SecurityUpdateAction update_action) {
  out << ToString(update_action);
  return out;
}

std::ostream& operator<<(std::ostream& out,
                         UserDefinedInstrument user_def_instr) {
  out << ToString(user_def_instr);
  return out;
}

std::ostream& operator<<(std::ostream& out, StatType stat_type) {
  out << ToString(stat_type);
  return out;
}

std::ostream& operator<<(std::ostream& out,
                         StatUpdateAction stat_update_action) {
  out << ToString(stat_update_action);
  return out;
}

std::ostream& operator<<(std::ostream& out,
                         VersionUpgradePolicy upgrade_policy) {
  out << ToString(upgrade_policy);
  return out;
}

template <>
Schema FromString(const std::string& str) {
  if (str == "mbo") {
    return Schema::Mbo;
  }
  if (str == "mbp-1") {
    return Schema::Mbp1;
  }
  if (str == "mbp-10") {
    return Schema::Mbp10;
  }
  if (str == "tbbo") {
    return Schema::Tbbo;
  }
  if (str == "trades") {
    return Schema::Trades;
  }
  if (str == "ohlcv-1s") {
    return Schema::Ohlcv1S;
  }
  if (str == "ohlcv-1m") {
    return Schema::Ohlcv1M;
  }
  if (str == "ohlcv-1h") {
    return Schema::Ohlcv1H;
  }
  if (str == "ohlcv-1d") {
    return Schema::Ohlcv1D;
  }
  if (str == "definition") {
    return Schema::Definition;
  }
  if (str == "imbalance") {
    return Schema::Imbalance;
  }
  if (str == "statistics") {
    return Schema::Statistics;
  }
  if (str == "status") {
    return Schema::Status;
  }
  throw InvalidArgumentError{"FromString<Schema>", "str",
                             "unknown value '" + str + '\''};
}

template <>
Encoding FromString(const std::string& str) {
  if (str == "dbn") {
    return Encoding::Dbn;
  }
  if (str == "csv") {
    return Encoding::Csv;
  }
  if (str == "json") {
    return Encoding::Json;
  }
  throw InvalidArgumentError{"FromString<Encoding>", "str",
                             "unknown value '" + str + '\''};
}

template <>
FeedMode FromString(const std::string& str) {
  if (str == "historical") {
    return FeedMode::Historical;
  }
  if (str == "historical-streaming") {
    return FeedMode::HistoricalStreaming;
  }
  if (str == "live") {
    return FeedMode::Live;
  }
  throw InvalidArgumentError{"FromString<FeedMode>", "str",
                             "unknown value '" + str + '\''};
}

template <>
Compression FromString(const std::string& str) {
  if (str == "none") {
    return Compression::None;
  }
  if (str == "zstd") {
    return Compression::Zstd;
  }
  throw InvalidArgumentError{"FromString<Compression>", "str",
                             "unknown value '" + str + '\''};
}

template <>
SType FromString(const std::string& str) {
  if (str == "instrument_id") {
    return SType::InstrumentId;
  }
  if (str == "raw_symbol") {
    return SType::RawSymbol;
  }
  if (str == "continuous") {
    return SType::Continuous;
  }
  if (str == "parent") {
    return SType::Parent;
  }
  throw InvalidArgumentError{"FromString<SType>", "str",
                             "unknown value '" + str + '\''};
}

template <>
SplitDuration FromString(const std::string& str) {
  if (str == "day") {
    return SplitDuration::Day;
  }
  if (str == "week") {
    return SplitDuration::Week;
  }
  if (str == "month") {
    return SplitDuration::Month;
  }
  if (str == "none") {
    return SplitDuration::None;
  }
  throw InvalidArgumentError{"FromString<SplitInterval>", "str",
                             "unknown value '" + str + '\''};
}

template <>
Packaging FromString(const std::string& str) {
  if (str == "none") {
    return Packaging::None;
  }
  if (str == "zip") {
    return Packaging::Zip;
  }
  if (str == "tar") {
    return Packaging::Tar;
  }
  throw InvalidArgumentError{"FromString<Packaging>", "str",
                             "unknown value '" + str + '\''};
}

template <>
Delivery FromString(const std::string& str) {
  if (str == "download") {
    return Delivery::Download;
  }
  if (str == "s3") {
    return Delivery::S3;
  }
  if (str == "disk") {
    return Delivery::Disk;
  }
  throw InvalidArgumentError{"FromString<Delivery>", "str",
                             "unknown value '" + str + '\''};
}

template <>
JobState FromString(const std::string& str) {
  if (str == "received") {
    return JobState::Received;
  }
  if (str == "queued") {
    return JobState::Queued;
  }
  if (str == "processing") {
    return JobState::Processing;
  }
  if (str == "done") {
    return JobState::Done;
  }
  if (str == "expired") {
    return JobState::Expired;
  }
  throw InvalidArgumentError{"FromString<JobState>", "str",
                             "unknown value '" + str + '\''};
}

template <>
DatasetCondition FromString(const std::string& str) {
  if (str == "available") {
    return DatasetCondition::Available;
  }
  if (str == "degraded") {
    return DatasetCondition::Degraded;
  }
  if (str == "pending") {
    return DatasetCondition::Pending;
  }
  if (str == "missing") {
    return DatasetCondition::Missing;
  }
  if (str == "bad") {
    return DatasetCondition::Bad;  // Deprecated
  }
  throw InvalidArgumentError{"FromString<DatasetCondition>", "str",
                             "unknown value '" + str + '\''};
}
}  // namespace databento
