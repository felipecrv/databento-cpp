#pragma once

#include <cstdint>
#include <iosfwd>
#include <string>

#include "databento/publishers.hpp"  // Dataset, Publisher, Venue, FromString

namespace databento {
// Represents a historical data center gateway location.
enum class HistoricalGateway : std::uint8_t {
  Bo1,
};

// Represents a data feed mode.
enum class FeedMode : std::uint8_t {
  Historical,
  HistoricalStreaming,
  Live,
};

// Represents a data record schema.
enum class Schema : std::uint16_t {
  Mbo = 0,
  Mbp1 = 1,
  Mbp10 = 2,
  Tbbo = 3,
  Trades = 4,
  Ohlcv1S = 5,
  Ohlcv1M = 6,
  Ohlcv1H = 7,
  Ohlcv1D = 8,
  Definition = 9,
  Statistics = 10,
  Status = 11,
  Imbalance = 12,
};

// Represents a data output encoding.
enum class Encoding : std::uint8_t {
  Dbn = 0,
  Csv = 1,
  Json = 2,
};

// Represents a data compression format (if any).
enum class Compression : std::uint8_t {
  None = 0,
  Zstd = 1,
};

// Represents a symbology type.
namespace stype {
enum SType : std::uint8_t {
  // Symbology using a unique numeric ID.
  InstrumentId = 0,
  // Symbology using the original symbols provided by the publisher.
  RawSymbol = 1,
  // A Databento-specific symbology where one symbol may point to different
  // instruments at different points of time, e.g. to always refer to the front
  // month future.
  Continuous = 3,
  // A Databento-specific symbology for referring to a group of symbols by one
  // "parent" symbol, e.g. ES.FUT to refer to all ES futures.
  Parent = 4,
  // Symbology for US equities using NASDAQ Integrated suffix conventions.
  Nasdaq = 5,
  // Symbology for US equities using CMS suffix conventions.
  Cms = 6,
};
}  // namespace stype
using SType = stype::SType;

// Represents the duration of time at which batch files will be split.
enum class SplitDuration : std::uint8_t {
  Day = 0,
  Week,
  Month,
  None,
};

// Represents how a batch job will be packaged.
enum class Packaging : std::uint8_t {
  None = 0,
  Zip,
  Tar,
};

// Represents how a batch job will be delivered.
enum class Delivery : std::uint8_t {
  Download,
  S3,
  Disk,
};

// The current state of a batch job.
enum class JobState : std::uint8_t {
  Received,
  Queued,
  Processing,
  Done,
  Expired,
};

// The condition of a dataset at a point in time.
enum class DatasetCondition : std::uint8_t {
  Available,
  Degraded,
  Pending,
  Missing,
  Bad,  // Deprecated
};

// Sentinel values for different DBN record types.
//
// Additional rtypes may be added in the future.
namespace rtype {
enum RType : std::uint8_t {
  Mbp0 = 0x00,
  Mbp1 = 0x01,
  Mbp10 = 0x0A,
  // Deprecated in 0.4.0. Separated into separate rtypes for each OHLCV schema.
  OhlcvDeprecated = 0x11,
  Ohlcv1S = 0x20,
  Ohlcv1M = 0x21,
  Ohlcv1H = 0x22,
  Ohlcv1D = 0x23,
  InstrumentDef = 0x13,
  Imbalance = 0x14,
  Error = 0x15,
  SymbolMapping = 0x16,
  System = 0x17,
  Statistics = 0x18,
  Mbo = 0xA0,
};
}  // namespace rtype
using rtype::RType;

// A tick action.
//
// Additional actions may be added in the future.
namespace action {
// enum because future variants may be added in the future.
enum Action : char {
  // An existing order was modified.
  Modify = 'M',
  // A trade executed.
  Trade = 'T',
  // An existing order was filled.
  Fill = 'F',
  // An order was cancelled.
  Cancel = 'C',
  // A new order was added.
  Add = 'A',
  // Reset the book; clear all orders for an instrument.
  Clear = 'R',
};
}  // namespace action
using action::Action;

// A side of the market. The side of the market for resting orders, or the side
// of the aggressor for trades.
enum class Side : char {
  // A sell order.
  Ask = 'A',
  // A buy order.
  Bid = 'B',
  // None or unknown.
  None = 'N',
};

namespace instrument_class {
// enum because future variants may be added in the future.
enum InstrumentClass : char {
  Bond = 'B',
  Call = 'C',
  Future = 'F',
  Stock = 'K',
  MixedSpread = 'M',
  Put = 'P',
  FutureSpread = 'S',
  OptionSpread = 'T',
  FxSpot = 'X',
};
}  // namespace instrument_class
using instrument_class::InstrumentClass;

namespace match_algorithm {
enum MatchAlgorithm : char {
  Fifo = 'F',
  Configurable = 'K',
  ProRata = 'C',
  FifoLmm = 'T',
  ThresholdProRata = 'O',
  FifoTopLmm = 'S',
  ThresholdProRataLmm = 'Q',
  EurodollarOptions = 'Y',
};
}  // namespace match_algorithm
using match_algorithm::MatchAlgorithm;

namespace security_update_action {
enum SecurityUpdateAction : char {
  Add = 'A',
  Modify = 'M',
  Delete = 'D',
};
}
using security_update_action::SecurityUpdateAction;

enum class UserDefinedInstrument : char {
  No = 'N',
  Yes = 'Y',
};

namespace stat_type {
// The type of statistic contained in a StatMsg.
enum StatType : std::uint16_t {
  // The price of the first trade of an instrument. `price` will be set.
  OpeningPrice = 1,
  // The probable price of the first trade of an instrument published during
  // pre-open. Both `price` and `quantity` will be set.
  IndicativeOpeningPrice = 2,
  // The settlement price of an instrument. `price` will be set and `flags`
  // indicate whether the price is final or preliminary and actual or
  // theoretical. `ts_ref` will indicate the trading date of the settlement
  // price.
  SettlementPrice = 3,
  // The lowest trade price of an instrument during the trading session.
  // `price` will be set.
  TradingSessionLowPrice = 4,
  // The highest trade price of an instrument during the trading session.
  // `price` will be set.
  TradingSessionHighPrice = 5,
  // The number of contracts cleared for an instrument on the previous trading
  // date. `quantity` will be set. `ts_ref` will indicate the trading date of
  // the volume.
  ClearedVolume = 6,
  // The lowest offer price for an instrument during the trading session.
  // `price` will be set.
  LowestOffer = 7,
  // The highest bid price for an instrument during the trading session.
  // `price` will be set.
  HighestBid = 8,
  // The current number of outstanding contracts of an instrument. `quantity`
  // will be set. `ts_ref` will indicate the trading date for which the open
  // interest was calculated.
  OpenInterest = 9,
  // The volume-weighted average price (VWAP) for a fixing period. `price` will
  // be set.
  FixingPrice = 10,
  // The last trade price during a trading session. `price` will be set.
  ClosePrice = 11,
  // The change in price from the close price of the previous trading session to
  // the most recent trading session. `price` will be set.
  NetChange = 12,
};
}  // namespace stat_type
using stat_type::StatType;

// The type of StatMsg update.
enum class StatUpdateAction : std::uint8_t {
  New = 1,
  Delete = 2,
};

// How to handle decoding DBN data from a prior version.
enum class VersionUpgradePolicy : std::uint8_t {
  AsIs = 0,
  Upgrade = 1,
};

// Convert a HistoricalGateway to a URL.
const char* UrlFromGateway(HistoricalGateway gateway);

const char* ToString(Schema schema);
const char* ToString(Encoding encoding);
const char* ToString(FeedMode mode);
const char* ToString(Compression compression);
const char* ToString(SType stype);
const char* ToString(SplitDuration duration_interval);
const char* ToString(Packaging packaging);
const char* ToString(Delivery delivery);
const char* ToString(JobState state);
const char* ToString(DatasetCondition condition);
const char* ToString(RType rtype);
const char* ToString(Action action);
const char* ToString(Side side);
const char* ToString(InstrumentClass instrument_class);
const char* ToString(MatchAlgorithm match_algorithm);
const char* ToString(SecurityUpdateAction update_action);
const char* ToString(UserDefinedInstrument user_def_instr);
const char* ToString(StatType stat_type);
const char* ToString(StatUpdateAction stat_update_action);
const char* ToString(VersionUpgradePolicy upgrade_policy);

std::ostream& operator<<(std::ostream& out, Schema schema);
std::ostream& operator<<(std::ostream& out, Encoding encoding);
std::ostream& operator<<(std::ostream& out, FeedMode mode);
std::ostream& operator<<(std::ostream& out, Compression compression);
std::ostream& operator<<(std::ostream& out, SType stype);
std::ostream& operator<<(std::ostream& out, SplitDuration duration_interval);
std::ostream& operator<<(std::ostream& out, Packaging packaging);
std::ostream& operator<<(std::ostream& out, Delivery delivery);
std::ostream& operator<<(std::ostream& out, JobState state);
std::ostream& operator<<(std::ostream& out, DatasetCondition condition);
std::ostream& operator<<(std::ostream& out, RType rtype);
std::ostream& operator<<(std::ostream& out, Action action);
std::ostream& operator<<(std::ostream& out, Side side);
std::ostream& operator<<(std::ostream& out, InstrumentClass instrument_class);
std::ostream& operator<<(std::ostream& out, MatchAlgorithm match_algorithm);
std::ostream& operator<<(std::ostream& out, SecurityUpdateAction update_action);
std::ostream& operator<<(std::ostream& out,
                         UserDefinedInstrument user_def_instr);
std::ostream& operator<<(std::ostream& out, StatType stat_type);
std::ostream& operator<<(std::ostream& out,
                         StatUpdateAction stat_update_action);
std::ostream& operator<<(std::ostream& out,
                         VersionUpgradePolicy upgrade_policy);

template <>
Schema FromString(const std::string& str);
template <>
Encoding FromString(const std::string& str);
template <>
FeedMode FromString(const std::string& str);
template <>
Compression FromString(const std::string& str);
template <>
SType FromString(const std::string& str);
template <>
SplitDuration FromString(const std::string& str);
template <>
Packaging FromString(const std::string& str);
template <>
Delivery FromString(const std::string& str);
template <>
JobState FromString(const std::string& str);
template <>
DatasetCondition FromString(const std::string& str);
}  // namespace databento
