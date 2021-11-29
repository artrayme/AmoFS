//
// Created by artrayme on 11/27/21.
//

#include "file.h"
#include <memory>
#include <stdexcept>
#include <utility>

File::File(std::string filename, size_t blockSize) : filename(std::move(filename)), blockSize(blockSize) {
  firstBlock = std::make_unique<Block>(blockSize);
  blocksCount = 1;
}

void File::readData(const std::shared_ptr<char> &buffer, size_t bytesCount) const {
  if (bytesCount > blockSize * blocksCount) throw std::invalid_argument("Try to read more bytes than available");
  if (bytesCount < 0) throw std::invalid_argument("Try to read negative number of bytes");

  size_t i = 0;
  //    for each block

  for (std::shared_ptr<Block> thisBlock(this->firstBlock); thisBlock != nullptr; thisBlock = std::move(thisBlock->next)) {
    //      for each file buffer byte
    for (size_t j = 0; j < blockSize && i < bytesCount; ++j, ++i) {
      buffer.get()[i] = thisBlock->data.get()[j];
    }
  }
}

void File::writeData(const std::shared_ptr<char> &buffer, size_t bytesCount) const {
  if (bytesCount > blockSize * blocksCount) throw std::invalid_argument("Try to read more bytes than available. You should reallocate this file first");
  if (bytesCount < 0) throw std::invalid_argument("Try to write negative number of bytes");

  //    for each block
  size_t i = 0;
  for (std::shared_ptr<Block> thisBlock(this->firstBlock); thisBlock != nullptr; thisBlock = std::move(thisBlock->next)) {
    //      for each file buffer byte
    for (size_t j = 0; j < blockSize && i < bytesCount; ++j, ++i) {
      thisBlock->data.get()[j] = buffer.get()[i];
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

bool File::operator==(const File &rhs) const {
  return filename == rhs.filename;
}

bool File::operator!=(const File &rhs) const {
  return !(rhs == *this);
}

File::File(const File &other): filename(other.filename), blockSize(other.blockSize) {
  bool initFlag = true;
  std::shared_ptr<Block> curBlock;
  for (auto thisBlock(other.firstBlock); thisBlock != nullptr; thisBlock = std::move(thisBlock->next)) {
    curBlock = std::make_shared<Block>(blockSize);
    currentBlock = curBlock;
    if (initFlag){
      firstBlock = curBlock;
      initFlag = false;
    }
    for (size_t j = 0; j < blockSize; ++j) {
      curBlock->data.get()[j] = thisBlock->data.get()[j];
    }
    curBlock = curBlock->next;
  }
}
