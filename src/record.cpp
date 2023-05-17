#include "databento/record.hpp"

#include <string>

#include "databento/enums.hpp"
#include "databento/exceptions.hpp"  // InvalidArgumentError
#include "databento/fixed_price.hpp"
#include "stream_op_helper.hpp"

using databento::Record;
using databento::RecordHeader;
using databento::RType;

std::size_t RecordHeader::Size() const {
  return static_cast<size_t>(length) * kLengthMultiplier;
}

std::size_t Record::Size() const { return record_->Size(); }

std::size_t Record::SizeOfSchema(const Schema schema) {
  switch (schema) {
    case Schema::Mbo: {
      return sizeof(MboMsg);
    }
    case Schema::Mbp1: {
      return sizeof(Mbp1Msg);
    }
    case Schema::Mbp10: {
      return sizeof(Mbp10Msg);
    }
    case Schema::Trades: {
      return sizeof(TradeMsg);
    }
    case Schema::Tbbo: {
      return sizeof(Mbp1Msg);
    }
    case Schema::Ohlcv1S:  // fallthrough
    case Schema::Ohlcv1M:  // fallthrough
    case Schema::Ohlcv1H:  // fallthrough
    case Schema::Ohlcv1D: {
      return sizeof(OhlcvMsg);
    }
    case Schema::Definition: {
      return sizeof(InstrumentDefMsg);
    }
    case Schema::Statistics: {
      return sizeof(StatMsg);
    }
    case Schema::Imbalance: {
      return sizeof(ImbalanceMsg);
    }
    default: {
      throw InvalidArgumentError{
          "Record::SizeOfSchema", "schema",
          "unknown value '" +
              std::to_string(static_cast<std::uint16_t>(schema)) + "'"};
    }
  }
}

RType Record::RTypeFromSchema(const Schema schema) {
  switch (schema) {
    case Schema::Mbo: {
      return RType::Mbo;
    }
    case Schema::Mbp1: {
      return RType::Mbp1;
    }
    case Schema::Mbp10: {
      return RType::Mbp10;
    }
    case Schema::Trades: {
      return RType::Mbp0;
    }
    case Schema::Tbbo: {
      return RType::Mbp1;
    }
    case Schema::Ohlcv1S: {
      return RType::Ohlcv1S;
    }
    case Schema::Ohlcv1M: {
      return RType::Ohlcv1M;
    }
    case Schema::Ohlcv1H: {
      return RType::Ohlcv1H;
    }
    case Schema::Ohlcv1D: {
      return RType::Ohlcv1D;
    }
    case Schema::Definition: {
      return RType::InstrumentDef;
    }
    case Schema::Statistics: {
      return RType::Statistics;
    }
    case Schema::Imbalance: {
      return RType::Imbalance;
    }
    default: {
      throw InvalidArgumentError{
          "Record::RTypeFromSchema", "schema",
          "unknown value '" +
              std::to_string(static_cast<std::uint16_t>(schema)) + "'"};
    }
  }
}

using databento::InstrumentDefMsg;

bool databento::operator==(const InstrumentDefMsg& lhs,
                           const InstrumentDefMsg& rhs) {
  return lhs.hd == rhs.hd && lhs.ts_recv == rhs.ts_recv &&
         lhs.min_price_increment == rhs.min_price_increment &&
         lhs.display_factor == rhs.display_factor &&
         lhs.expiration == rhs.expiration && lhs.activation == rhs.activation &&
         lhs.high_limit_price == rhs.high_limit_price &&
         lhs.low_limit_price == rhs.low_limit_price &&
         lhs.max_price_variation == rhs.max_price_variation &&
         lhs.trading_reference_price == rhs.trading_reference_price &&
         lhs.unit_of_measure_qty == rhs.unit_of_measure_qty &&
         lhs.min_price_increment_amount == rhs.min_price_increment_amount &&
         lhs.price_ratio == rhs.price_ratio &&
         lhs.inst_attrib_value == rhs.inst_attrib_value &&
         lhs.underlying_id == rhs.underlying_id &&
         lhs.market_depth_implied == rhs.market_depth_implied &&
         lhs.market_depth == rhs.market_depth &&
         lhs.market_segment_id == rhs.market_segment_id &&
         lhs.max_trade_vol == rhs.max_trade_vol &&
         lhs.min_lot_size == rhs.min_lot_size &&
         lhs.min_lot_size_block == rhs.min_lot_size_block &&
         lhs.min_lot_size_round_lot == rhs.min_lot_size_round_lot &&
         lhs.min_trade_vol == rhs.min_trade_vol &&
         lhs.contract_multiplier == rhs.contract_multiplier &&
         lhs.decay_quantity == rhs.decay_quantity &&
         lhs.original_contract_size == rhs.original_contract_size &&
         lhs.trading_reference_date == rhs.trading_reference_date &&
         lhs.appl_id == rhs.appl_id && lhs.maturity_year == rhs.maturity_year &&
         lhs.decay_start_date == rhs.decay_start_date &&
         lhs.channel_id == rhs.channel_id && lhs.currency == rhs.currency &&
         lhs.settl_currency == rhs.settl_currency &&
         lhs.secsubtype == rhs.secsubtype && lhs.raw_symbol == rhs.raw_symbol &&
         lhs.group == rhs.group && lhs.exchange == rhs.exchange &&
         lhs.asset == rhs.asset && lhs.cfi == rhs.cfi &&
         lhs.security_type == rhs.security_type &&
         lhs.unit_of_measure == rhs.unit_of_measure &&
         lhs.underlying == rhs.underlying &&
         lhs.strike_price_currency == rhs.strike_price_currency &&
         lhs.instrument_class == rhs.instrument_class &&
         lhs.strike_price == rhs.strike_price &&
         lhs.match_algorithm == rhs.match_algorithm &&
         lhs.md_security_trading_status == rhs.md_security_trading_status &&
         lhs.main_fraction == rhs.main_fraction &&
         lhs.price_display_format == rhs.price_display_format &&
         lhs.settl_price_type == rhs.settl_price_type &&
         lhs.sub_fraction == rhs.sub_fraction &&
         lhs.underlying_product == rhs.underlying_product &&
         lhs.security_update_action == rhs.security_update_action &&
         lhs.maturity_month == rhs.maturity_month &&
         lhs.maturity_day == rhs.maturity_day &&
         lhs.maturity_week == rhs.maturity_week &&
         lhs.user_defined_instrument == rhs.user_defined_instrument &&
         lhs.contract_multiplier_unit == rhs.contract_multiplier_unit &&
         lhs.flow_schedule_type == rhs.flow_schedule_type &&
         lhs.tick_rule == rhs.tick_rule;
}

using databento::ImbalanceMsg;

bool operator==(const ImbalanceMsg& lhs, const ImbalanceMsg& rhs) {
  return lhs.hd == rhs.hd && lhs.ts_recv == rhs.ts_recv &&
         lhs.ref_price == rhs.ref_price &&
         lhs.auction_time == rhs.auction_time &&
         lhs.cont_book_clr_price == rhs.cont_book_clr_price &&
         lhs.auct_interest_clr_price == rhs.auct_interest_clr_price &&
         lhs.ssr_filling_price == rhs.ssr_filling_price &&
         lhs.ind_match_price == rhs.ind_match_price &&
         lhs.upper_collar == rhs.upper_collar &&
         lhs.lower_collar == rhs.lower_collar &&
         lhs.paired_qty == rhs.paired_qty &&
         lhs.total_imbalance_qty == rhs.total_imbalance_qty &&
         lhs.market_imbalance_qty == rhs.market_imbalance_qty &&
         lhs.unpaired_qty == rhs.unpaired_qty &&
         lhs.auction_type == rhs.auction_type && lhs.side == rhs.side &&
         lhs.auction_status == rhs.auction_status &&
         lhs.freeze_status == rhs.freeze_status &&
         lhs.num_extensions == rhs.num_extensions &&
         lhs.unpaired_side == rhs.unpaired_side &&
         lhs.significant_imbalance == rhs.significant_imbalance;
}

namespace databento {
namespace detail {
template <>
std::string ToString(const Mbp1Msg& mbp_msg) {
  return MakeString(mbp_msg);
}
template <>
std::string ToString(const Mbp10Msg& mbp_msg) {
  return MakeString(mbp_msg);
}
template <>
std::ostream& operator<<(std::ostream& stream, const Mbp1Msg& mbp_msg) {
  return StreamOpBuilder{stream}
      .SetTypeName("Mbp1Msg")
      .SetSpacer("\n    ")
      .Build()
      .AddField("hd", mbp_msg.hd)
      .AddField("price", FixPx{mbp_msg.price})
      .AddField("size", mbp_msg.size)
      .AddField("action", mbp_msg.action)
      .AddField("side", mbp_msg.side)
      .AddField("flags", mbp_msg.flags)
      .AddField("depth", mbp_msg.depth)
      .AddField("ts_recv", mbp_msg.ts_recv)
      .AddField("ts_in_delta", mbp_msg.ts_in_delta)
      .AddField("sequence", mbp_msg.sequence)
      .AddField("levels", std::get<0>(mbp_msg.levels))
      .Finish();
}
template <>
std::ostream& operator<<(std::ostream& stream, const Mbp10Msg& mbp_msg) {
  std::ostringstream levelss;
  auto levels_helper =
      StreamOpBuilder{levelss}.SetSpacer("\n    ").SetIndent("    ").Build();
  for (const auto& levels : mbp_msg.levels) {
    levels_helper.AddItem(levels);
  }
  return StreamOpBuilder{stream}
      .SetTypeName("Mbp10Msg")
      .SetSpacer("\n    ")
      .Build()
      .AddField("hd", mbp_msg.hd)
      .AddField("price", FixPx{mbp_msg.price})
      .AddField("size", mbp_msg.size)
      .AddField("action", mbp_msg.action)
      .AddField("side", mbp_msg.side)
      .AddField("flags", mbp_msg.flags)
      .AddField("depth", mbp_msg.depth)
      .AddField("ts_recv", mbp_msg.ts_recv)
      .AddField("ts_in_delta", mbp_msg.ts_in_delta)
      .AddField("sequence", mbp_msg.sequence)
      .AddField("levels",
                static_cast<std::ostringstream&>(levels_helper.Finish()))
      .Finish();
}
}  // namespace detail

std::string ToString(const RecordHeader& header) { return MakeString(header); }
std::ostream& operator<<(std::ostream& stream, const RecordHeader& header) {
  return StreamOpBuilder{stream}
      .SetSpacer(" ")
      .SetTypeName("RecordHeader")
      .Build()
      .AddField("length", header.length)
      .AddField("rtype", header.rtype)
      .AddField("publisher_id", header.publisher_id)
      .AddField("instrument_id", header.instrument_id)
      .AddField("ts_event", header.ts_event)
      .Finish();
}
std::string ToString(const MboMsg& mbo_msg) { return MakeString(mbo_msg); }
std::ostream& operator<<(std::ostream& stream, const MboMsg& mbo_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("MboMsg")
      .Build()
      .AddField("hd", mbo_msg.hd)
      .AddField("order_id", mbo_msg.order_id)
      .AddField("price", FixPx{mbo_msg.price})
      .AddField("size", mbo_msg.size)
      .AddField("flags", mbo_msg.flags)
      .AddField("channel_id", mbo_msg.channel_id)
      .AddField("action", mbo_msg.action)
      .AddField("side", mbo_msg.side)
      .AddField("ts_recv", mbo_msg.ts_recv)
      .AddField("ts_in_delta", mbo_msg.ts_in_delta)
      .AddField("sequence", mbo_msg.sequence)
      .Finish();
}
std::string ToString(const BidAskPair& ba_pair) { return MakeString(ba_pair); }
std::ostream& operator<<(std::ostream& stream, const BidAskPair& ba_pair) {
  return StreamOpBuilder{stream}
      .SetSpacer(" ")
      .SetTypeName("BidAskPair")
      .Build()
      .AddField("bid_px", FixPx{ba_pair.bid_px})
      .AddField("ask_px", FixPx{ba_pair.ask_px})
      .AddField("bid_sz", ba_pair.bid_sz)
      .AddField("ask_sz", ba_pair.ask_sz)
      .AddField("bid_ct", ba_pair.bid_ct)
      .AddField("ask_ct", ba_pair.ask_ct)
      .Finish();
}
std::string ToString(const TradeMsg& trade_msg) {
  return MakeString(trade_msg);
}
std::ostream& operator<<(std::ostream& stream, const TradeMsg& trade_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("TradeMsg")
      .Build()
      .AddField("hd", trade_msg.hd)
      .AddField("price", FixPx{trade_msg.price})
      .AddField("size", trade_msg.size)
      .AddField("action", trade_msg.action)
      .AddField("side", trade_msg.side)
      .AddField("flags", trade_msg.flags)
      .AddField("depth", trade_msg.depth)
      .AddField("ts_recv", trade_msg.ts_recv)
      .AddField("ts_in_delta", trade_msg.ts_in_delta)
      .AddField("sequence", trade_msg.sequence)
      .Finish();
}
std::string ToString(const OhlcvMsg& ohlcv_msg) {
  return MakeString(ohlcv_msg);
}
std::ostream& operator<<(std::ostream& stream, const OhlcvMsg& ohlcv_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("OhlcvMsg")
      .Build()
      .AddField("hd", ohlcv_msg.hd)
      .AddField("open", FixPx{ohlcv_msg.open})
      .AddField("high", FixPx{ohlcv_msg.high})
      .AddField("low", FixPx{ohlcv_msg.low})
      .AddField("close", FixPx{ohlcv_msg.close})
      .AddField("volume", ohlcv_msg.volume)
      .Finish();
}
std::string ToString(const InstrumentDefMsg& instr_def_msg) {
  return MakeString(instr_def_msg);
}
std::ostream& operator<<(std::ostream& stream,
                         const InstrumentDefMsg& instr_def_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("InstrumentDefMsg")
      .Build()
      .AddField("hd", instr_def_msg.hd)
      .AddField("ts_recv", instr_def_msg.ts_recv)
      .AddField("min_price_increment", FixPx{instr_def_msg.min_price_increment})
      .AddField("display_factor", instr_def_msg.display_factor)
      .AddField("expiration", instr_def_msg.expiration)
      .AddField("activation", instr_def_msg.activation)
      .AddField("high_limit_price", FixPx{instr_def_msg.high_limit_price})
      .AddField("low_limit_price", FixPx{instr_def_msg.low_limit_price})
      .AddField("max_price_variation", FixPx{instr_def_msg.max_price_variation})
      .AddField("trading_reference_price",
                FixPx{instr_def_msg.trading_reference_price})
      .AddField("unit_of_measure_qty", instr_def_msg.unit_of_measure_qty)
      .AddField("min_price_increment_amount",
                FixPx{instr_def_msg.min_price_increment_amount})
      .AddField("price_ratio", instr_def_msg.price_ratio)
      .AddField("inst_attrib_value", instr_def_msg.inst_attrib_value)
      .AddField("underlying_id", instr_def_msg.underlying_id)
      .AddField("market_depth_implied", instr_def_msg.market_depth_implied)
      .AddField("market_depth", instr_def_msg.market_depth)
      .AddField("market_segment_id", instr_def_msg.market_segment_id)
      .AddField("max_trade_vol", instr_def_msg.max_trade_vol)
      .AddField("min_lot_size", instr_def_msg.min_lot_size)
      .AddField("min_lot_size_block", instr_def_msg.min_lot_size_block)
      .AddField("min_lot_size_round_lot", instr_def_msg.min_lot_size_round_lot)
      .AddField("min_trade_vol", instr_def_msg.min_trade_vol)
      .AddField("contract_multiplier", instr_def_msg.contract_multiplier)
      .AddField("decay_quantity", instr_def_msg.decay_quantity)
      .AddField("original_contract_size", instr_def_msg.original_contract_size)
      .AddField("trading_reference_date", instr_def_msg.trading_reference_date)
      .AddField("appl_id", instr_def_msg.appl_id)
      .AddField("maturity_year", instr_def_msg.maturity_year)
      .AddField("decay_start_date", instr_def_msg.decay_start_date)
      .AddField("channel_id", instr_def_msg.channel_id)
      .AddField("currency", instr_def_msg.currency)
      .AddField("settl_currency", instr_def_msg.settl_currency)
      .AddField("secsubtype", instr_def_msg.secsubtype)
      .AddField("raw_symbol", instr_def_msg.raw_symbol)
      .AddField("group", instr_def_msg.group)
      .AddField("exchange", instr_def_msg.exchange)
      .AddField("asset", instr_def_msg.asset)
      .AddField("cfi", instr_def_msg.cfi)
      .AddField("security_type", instr_def_msg.security_type)
      .AddField("unit_of_measure", instr_def_msg.unit_of_measure)
      .AddField("underlying", instr_def_msg.underlying)
      .AddField("strike_price_currency", instr_def_msg.strike_price_currency)
      .AddField("instrument_class", instr_def_msg.instrument_class)
      .AddField("strike_price", FixPx{instr_def_msg.strike_price})
      .AddField("match_algorithm", instr_def_msg.match_algorithm)
      .AddField("md_security_trading_status",
                instr_def_msg.md_security_trading_status)
      .AddField("main_fraction", instr_def_msg.main_fraction)
      .AddField("price_display_format", instr_def_msg.price_display_format)
      .AddField("settl_price_type", instr_def_msg.settl_price_type)
      .AddField("sub_fraction", instr_def_msg.sub_fraction)
      .AddField("underlying_product", instr_def_msg.underlying_product)
      .AddField("security_update_action", instr_def_msg.security_update_action)
      .AddField("maturity_month", instr_def_msg.maturity_month)
      .AddField("maturity_day", instr_def_msg.maturity_day)
      .AddField("maturity_week", instr_def_msg.maturity_week)
      .AddField("user_defined_instrument",
                instr_def_msg.user_defined_instrument)
      .AddField("contract_multiplier_unit",
                instr_def_msg.contract_multiplier_unit)
      .AddField("flow_schedule_type", instr_def_msg.flow_schedule_type)
      .AddField("tick_rule", instr_def_msg.tick_rule)
      .Finish();
}

std::string ToString(const ImbalanceMsg& imbalance_msg) {
  return MakeString(imbalance_msg);
}
std::ostream& operator<<(std::ostream& stream,
                         const ImbalanceMsg& imbalance_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("ImbalanceMsg")
      .Build()
      .AddField("hd", imbalance_msg.hd)
      .AddField("ts_recv", imbalance_msg.ts_recv)
      .AddField("ref_price", FixPx{imbalance_msg.ref_price})
      .AddField("auction_time", imbalance_msg.auction_time)
      .AddField("cont_book_clr_price", FixPx{imbalance_msg.cont_book_clr_price})
      .AddField("auct_interest_clr_price",
                FixPx{imbalance_msg.auct_interest_clr_price})
      .AddField("ssr_filling_price", FixPx{imbalance_msg.ssr_filling_price})
      .AddField("ind_match_price", FixPx{imbalance_msg.ind_match_price})
      .AddField("upper_collar", FixPx{imbalance_msg.upper_collar})
      .AddField("lower_collar", FixPx{imbalance_msg.lower_collar})
      .AddField("paired_qty", imbalance_msg.paired_qty)
      .AddField("total_imbalance_qty", imbalance_msg.total_imbalance_qty)
      .AddField("market_imbalance_qty", imbalance_msg.market_imbalance_qty)
      .AddField("unpaired_qty", imbalance_msg.unpaired_qty)
      .AddField("auction_type", imbalance_msg.auction_type)
      .AddField("side", imbalance_msg.side)
      .AddField("auction_status", imbalance_msg.auction_status)
      .AddField("freeze_status", imbalance_msg.freeze_status)
      .AddField("num_extensions", imbalance_msg.num_extensions)
      .AddField("unpaired_side", imbalance_msg.unpaired_side)
      .AddField("significant_imbalance", imbalance_msg.significant_imbalance)
      .Finish();
}

std::string ToString(const StatMsg& stat_msg) { return MakeString(stat_msg); }
std::ostream& operator<<(std::ostream& stream, const StatMsg& stat_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("StatMsg")
      .Build()
      .AddField("hd", stat_msg.hd)
      .AddField("ts_recv", stat_msg.ts_recv)
      .AddField("ts_ref", stat_msg.ts_ref)
      .AddField("price", FixPx{stat_msg.price})
      .AddField("quantity", stat_msg.quantity)
      .AddField("sequence", stat_msg.sequence)
      .AddField("ts_in_delta", stat_msg.ts_in_delta)
      .AddField("stat_type", stat_msg.stat_type)
      .AddField("channel_id", stat_msg.channel_id)
      .AddField("update_action", stat_msg.update_action)
      .AddField("stat_flags", stat_msg.stat_flags)
      .Finish();
}

std::string ToString(const ErrorMsg& err_msg) { return MakeString(err_msg); }
std::ostream& operator<<(std::ostream& stream, const ErrorMsg& err_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("ErrorMsg")
      .Build()
      .AddField("hd", err_msg.hd)
      .AddField("err", err_msg.err)
      .Finish();
}

std::string ToString(const SystemMsg& system_msg) {
  return MakeString(system_msg);
}
std::ostream& operator<<(std::ostream& stream, const SystemMsg& system_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("SystemMsg")
      .Build()
      .AddField("hd", system_msg.hd)
      .AddField("msg", system_msg.msg)
      .Finish();
}

std::string ToString(const SymbolMappingMsg& symbol_mapping_msg) {
  return MakeString(symbol_mapping_msg);
}
std::ostream& operator<<(std::ostream& stream,
                         const SymbolMappingMsg& symbol_mapping_msg) {
  return StreamOpBuilder{stream}
      .SetSpacer("\n    ")
      .SetTypeName("SymbolMappingMsg")
      .Build()
      .AddField("hd", symbol_mapping_msg.hd)
      .AddField("stype_in_symbol", symbol_mapping_msg.stype_in_symbol)
      .AddField("stype_out_symbol", symbol_mapping_msg.stype_out_symbol)
      .AddField("start_ts", symbol_mapping_msg.start_ts)
      .AddField("end_ts", symbol_mapping_msg.end_ts)
      .Finish();
}
}  // namespace databento
