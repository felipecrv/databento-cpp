# Changelog

## 0.15.0 - 2023-01-16

### Breaking changes
- Increased size of `SystemMsg` and `ErrorMsg` to provide better messages from Live
  gateway
  - Increased length of `err` and `msg` fields for more detailed messages
  - Added `is_last` field to `ErrorMsg` to indicate the last error in a chain
  - Added `code` field to `SystemMsg` and `ErrorMsg`, although currently unused
  - Added new `is_last` parameter to `ErrorMsg::new`
  - Decoding these is backwards-compatible and records with longer messages won't be
    sent during the DBN version 2 migration period
  - Renamed previous records to `ErrorMsgV1` and `SystemMsgV1`

## 0.14.1 - 2023-12-18

### Enhancements
- Added `PitSymbolMap` helper for keeping track of symbology mappings in Live
- Added new publisher value for OPRA MIAX Sapphire

### Bug fixes
- Fixed misaligned read undefined behavior when decoding records

## 0.14.0 - 2023-11-23

This release adds support for DBN v2.

DBN v2 delivers improvements to the `Metadata` header symbology, new `stype_in` and `stype_out`
fields for `SymbolMappingMsg`, and extends the symbol field length for `SymbolMappingMsg` and
`InstrumentDefMsg`. The entire change notes are available [here](https://github.com/databento/dbn/releases/tag/v0.14.0).
Users who wish to convert DBN v1 files to v2 can use the `dbn-cli` tool available in the [databento-dbn](https://github.com/databento/dbn/) crate.
On a future date, the Databento live and historical APIs will stop serving DBN v1.

This release is fully compatible with both DBN v1 and v2, and so should be seamless for most users.

### Enhancements
- Added support for DBN encoding version 2 (DBNv2), affecting `SymbolMappingMsg`,
  `InstrumentDefMsg`, and `Metadata`
  - Version 1 structs can be converted to version 2 structs with the `ToV2()` method
- Added `symbol_cstr_len` field to `Metadata` to indicate the length of fixed symbol
  strings
- Added `stype_in` and `stype_out` fields to `SymbolMappingMsg` to provide more context
  with live symbology updates
- Added `IndexTs` methods to every record type which returns the primary timestamp
- Added `VersionUpgradePolicy` enum to allow specifying how to handle decoding records
  from prior DBN versions
- Added `InstrumentDefMsgV2` and `SymbolMappingMsgV2` type aliases
- Added `kDbnVersion` constant for current DBN version
- Added `kSymbolCstrLen`, `kSymbolCstrLenV1`, and `kSymbolCstrLenV2` constants for the
  length of fixed-length symbol strings in different DBN versions
- Added new publisher values in preparation for IFEU.IMPACT and NDEX.IMPACT datasets
- Added new publisher values for consolidated DBEQ.BASIC and DBEQ.PLUS
- Added `kMaxRecordLen` constant for the the length of the largest record type
- Added ability to convert `FlagSet` to underlying representation

### Breaking changes
- The old `InstrumentDefMsg` is now `InstrumentDefMsgV1` in `compat.hpp`
- The old `SymbolMappingMsg` is now `SymbolMappingMsgV1` in `compat.hpp`
- Converted the following enums to enum classes to allow safely adding new variants:
  `SecurityUpdateAction` and `SType`
- Renamed `dummy` to `reserved` in `InstrumentDefMsg`
- Removed `reserved2`, `reserved3`, `reserved4`, and `reserved5` from `InstrumentDefMsg`
- Moved position of `strike_price` within `InstrumentDefMsg`
- Removed deprecated `SecurityUpdateAction::Invalid` variant

## 0.13.1 - 2023-10-23
### Enhancements
- Added new publisher values in preparation for DBEQ.PLUS
- Added `ToIso8601` for `UnixNanos` for converting to human-readable ISO8601 datetime
  string
- Added `kUndefTimestamp` and `kUndefStatQuantity` constants
- Added flag `kTob` for top-of-book messages

## 0.13.0 - 2023-09-21
### Enhancements
- Added `pretty_px` option for `BatchSubmitJob`, which formats prices to the correct
  scale using the fixed-precision scalar 1e-9 (available for CSV and JSON text
  encodings)
- Added `pretty_ts` option for `BatchSubmitJob`, which formats timestamps as ISO 8601
  strings (available for CSV and JSON text encodings)
- Added `map_symbols` option to `BatchSubmitJob`, which appends appends the raw symbol
  to every record (available for CSV and JSON text encodings) reducing the need to look
  at the `symbology.json` file
- Added `split_symbols` option for `BatchSubmitJob`, which will split files by raw symbol
- Added `encoding` option to `BatchSubmitJob` to allow requesting non-DBN encoded
  data through the client
- Added `map_symbols`, `pretty_px`, and `pretty_ts` to `BatchJob` response
- Added `ARCX.PILLAR.ARCX` publisher
- Added `ClosePrice` and `NetChange` `StatType`s used in the `OPRA.PILLAR` dataset

### Breaking changes
- Remove `default_value` parameter from `Historical::SymbologyResolve`

## 0.12.1 - 2023-08-25
### Bug fixes
- Fixed typo in `BATY.PITCH.BATY` publisher

## 0.12.0 - 2023-08-24

##### Enhancements
- Added the `Publisher`, `Venue`, and `Dataset` enums
- Added `Publisher` getters to `Record` and `RecordHeader` to convert the
  `publisher_id` to its enum

## 0.11.0 - 2023-08-10

#### Enhancements
- Added `raw_instrument_id` to definition schema
- Added `operator==` and `operator!=` implementations for `DatasetConditionDetail` and
  `DatasetRange`

#### Breaking changes
- Changed `MetadataListPublishers` to return a `vector<PublisherDetail>`
- `MetadataListFields`:
  - Changed return type to `vector<FieldDetail>`
  - Made `encoding` and `schema` parameters required
  - Removed `dataset` parameter
- `MetadataListUnitPrices`:
  - Changed return type to `vector<UnitPricesForMode>`
  - Made `dataset` parameter required
  - Removed `mode` and `schema` parameters

#### Bug fixes
- Fixed installation of `nlohmann_json` when using bundled version
- Added missing `operator!=` implementations for `Metadata`, `MappingInterval`, and
  `SymbolMapping`

## 0.10.0 - 2023-07-20

#### Enhancements
- Added preliminary support for Windows
- Added `LiveThreaded::BlockForStop` to make it easier to wait for one or more records
  before closing the session
- Changed `TimeseriesGetRange` to request a Zstd-compressed result for more efficient
  data transfer
- Switched `BatchSubmitJob` to use form data to avoid query param length limit
- Switched `SymbologyResolve` to use POST request with form data to avoid query param
  length limit

#### Breaking changes
- Changed size-related fields and `limit` parameters to use `std::uint64_t` for consistency
  across architectures

#### Bug fixes
- Removed usage of non-portable `__PRETTY_FUNCTION__`

## 0.9.1 - 2023-07-11

#### Enhancements
- Added constants for dataset codes for Databento Equity Basic and OPRA Pillar
- Added `const char*` getters to records for fixed-length `char` arrays
- Added `RType` getter to `Record`

#### Bug fixes
- Added batching for live subscriptions to avoid hitting max message length
- Fixed bug in Zstd decompression
- Fixed `Historical::BatchDownload` truncating file before writing each chunk

## 0.9.0 - 2023-06-13

#### Enhancements
- Added `Reconnect` methods to `LiveBlocking` and `LiveThreaded`
- Added optional `exception_callback` argument to `LiveThreaded::Start` to improve
  error handling options
- Added batch download support data files (`condition.json` and `symbology.json`)
- Added support for logging warnings from Historical API
- Relaxed 10 minute minimum request time range restriction

#### Breaking changes
- Changed `use_ts_out` default to `false`

#### Bug fixes
- Fixed missing definition for `operator==` for `ImbalanceMsg`

## 0.8.0 - 2023-05-16

#### Enhancements
- Changed `end` and `end_date` to optional to support new forward-fill behaviour

#### Breaking changes
- Renamed `booklevel` MBP field to `levels` for brevity and consistent naming
- Removed `open_interest_qty` and `cleared_volume` fields from definition schema
  that were always unset

## 0.7.0 - 2023-04-28

#### Enhancements
- Added initial support for live data with `LiveBlocking` and `LiveThreaded` clients
- Added support for statistics schema
- Added `SystemMsg` and `ErrorMsg` records for use in live data
- Added `strike_price`, `strike_price_currency`, and `instrument_class` to
  `InstrumentDefMsg`
- Added `FixedPx` helper class for formatting fixed prices
- Added configurable log receiver `ILogReceiver`
- Added `instrument_class`, `strike_price`, and `strike_price_currency` to definition
  schema
- Added additional `condition` variants for `DatasetConditionDetail` (degraded, pending,
  missing)
- Added additional member `last_modified_date` to `DatasetConditionDetail`
- Added `has_mixed_schema`, `has_mixed_stype_in`, and `ts_out` to `Metadata` to support
  live data
- Added optional `compression` parameter to `BatchSubmitJob`

#### Breaking changes
- Removed `related` and `related_security_id` from `InstrumentDefMsg`
- Renamed `BatchJob.cost` to `cost_usd` and value now expressed as US dollars
- Renamed `SType::ProductId` to `SType::InstrumentId` and `SType::Native` to
  `SType::RawSymbol`
- Renamed `RecordHeader::product_id` to `instrument_id`
- Renamed `InstrumentDefMsg::symbol` to `raw_symbol`
- Renamed `SymbolMapping::native_symbol` to `raw_symbol`
- Changed `expiration` and `action` type to `UnixNanos`
- Changed some fields to enums in `InstrumentDefMsg`

#### Deprecations
- Deprecated `SType::Smart` to split into `SType::Parent` and `SType::Continuous`

#### Bug fixes
- Fixed parsing of `BatchSubmitJob` response
- Fixed invalid read in `DbnDecoder`
- Fixed memory leak in `TryCreateDir`

## 0.6.1 - 2023-03-28

#### Breaking changes
- Removed usage of unreliable `std::ifstream::readsome`

#### Bug fixes
- Fixed Zstd decoding of files with multiple frames

## 0.6.0 - 2023-03-24

#### Enhancements
- Added support for imbalance schema
- Added support for decoding `ts_out` field
- Added flags `kSnapshot` and `kMaybeBadBook`

#### Breaking changes
- Removed `record_count` from `Metadata`
- Changed `Historical::BatchDownload` to return the paths of the downloaded files

## 0.5.0 - 2023-03-13

#### Enhancements
- Added `Historical::MetadataGetDatasetRange`

#### Breaking changes
- Changed `MetadataGetDatasetCondition` to return `vector<DatasetConditionDetail>`
- Removed `MetadataListCompressions` (redundant with docs)
- Removed `MetadataListEncodings` (redundant with docs)
- Removed optional `start` and `end` params from `MetadataListSchemas` (redundant)
- Renamed `FileBento` to `DbnFileStore`

## 0.4.0 - 2023-03-02

#### Enhancements

- Added live gateway resolution
- Added `SymbolMappingMsg` and `ErrorMsg` records
- Added `Action` and `Side` enums
- Added `available_start_date` and `available_end_date` to
  `DatasetConditionInfo`
- Made `start_date` and `end_date` optional for
  `Historical::MetadataGetDatasetCondition`
- Improved API for `flags` record fields
- Added `PKGBUILD` to demonstrate installation
- Disabled unit testing by default

#### Breaking changes
- Removed `is_full_universe` and `is_example` fields from `BatchJob`
- Refactored rtypes
  - Introduced separate rtypes for each OHLCV schema
- Renamed DBZ to DBN
  - Renamed `DbzParser` to `DbnDecoder`
- Renamed `TimeseriesStream` to `TimeseriesGetRange`
- Changed `kAllSymbols` representation

#### Bug fixes
- Fixed usage of as a system library

## 0.3.0 - 2023-01-06

#### Enhancements
- Added support for definition schema
- Added option for CMake to download gtest
- Updated `Flag` enum

#### Breaking changes
- Standardized getter method names to pascal case
- Renamed `is_full_book` to `is_full_universe`
- Renamed `TickMsg` to `MboMsg`
- Changed `flags` fields to unsigned

#### Bug fixes
- Fixed cancellation in `Historical::TimeseriesStream`
- Fixed race condition in `Historical::TimeseriesStream` exception handling
- Fixed gtest linker error on macOS

## 0.2.0 - 2022-12-01

#### Enhancements
- Added `Historical::MetadataGetDatasetCondition`
- Improved Zstd CMake integration

#### Bug fixes
- Fixed requesting all symbols for a dataset

## 0.1.0 - 2022-11-07
- Initial release with support for historical data
