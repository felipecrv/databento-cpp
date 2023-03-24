#include "databento/dbn_file_store.hpp"

#include <utility>  // move

#include "databento/detail/file_stream.hpp"

using databento::DbnFileStore;

DbnFileStore::DbnFileStore(const std::string& file_path)
    : parser_{detail::FileStream{file_path}} {}

void DbnFileStore::Replay(const MetadataCallback& metadata_callback,
                          const RecordCallback& record_callback) {
  auto metadata = parser_.DecodeMetadata();
  if (metadata_callback) {
    metadata_callback(std::move(metadata));
  }
  const databento::Record* record;
  while ((record = parser_.DecodeRecord()) != nullptr) {
    if (record_callback(*record) == KeepGoing::Stop) {
      break;
    }
  }
}

void DbnFileStore::Replay(const RecordCallback& record_callback) {
  Replay({}, record_callback);
}
