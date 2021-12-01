//
// Created by artrayme on 11/27/21.
//

#include "file.h"
#include <memory>
#include <stdexcept>
#include <utility>

File::File(std::string filename, size_t blockSize) : filename(std::move(filename)), blockSize(blockSize) {
}

void File::readData(const std::shared_ptr<char> &buffer, size_t bytesCount) const {
  if (bytesCount > blockSize * blocks.size()) throw std::invalid_argument("Try to read more bytes than available");
  if (bytesCount < 0) throw std::invalid_argument("Try to read negative number of bytes");

  size_t i = 0;
  for (const auto &item : blocks) {
    for (size_t j = 0; j < blockSize && i < bytesCount; ++j, ++i) {
      buffer.get()[i] = item[j];
    }
  }
}

void File::writeData(const std::shared_ptr<char> &buffer, size_t bytesCount) {
  if (bytesCount > blockSize * blocks.size()) throw std::invalid_argument("Try to read more bytes than available. You should reallocate this file first");
  if (bytesCount < 0) throw std::invalid_argument("Try to write negative number of bytes");

  size_t i = 0;
  for (auto &block : blocks) {
    for (auto data = block.begin(); data!=block.end() && i<bytesCount; ++data, ++i){
      *data = buffer.get()[i];
    }
  }
}
std::string File::getFilename() const {
  return filename;
}
void File::setFileName(const std::string &newFilename) {
  this->filename = newFilename;
}
size_t File::getBlockSize() const {
  return blockSize;
}

File::File(const File &other) : filename(other.filename), blockSize(other.blockSize) {
  blocks = std::list<std::vector<char>>(other.blocks);
}
