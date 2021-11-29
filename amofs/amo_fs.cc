//
// Created by artrayme on 11/27/21.
//

#include "amo_fs.h"
#include <memory>
#include <stdexcept>

AmoFS::AmoFS(size_t blockSize) {
  if (blockSize < 1) throw std::invalid_argument("Block size must be greater than 1");
  this->blockSize = blockSize;
}

std::shared_ptr<File> AmoFS::createFile(const std::string &filename) {
  auto file = std::make_shared<File>(filename, blockSize);
  auto insertionResult = files.insert(file);
  if (!insertionResult.second) throw std::domain_error("File with this name already exist");
  return file;
}

void AmoFS::deleteFile(const std::string &filename) {
  auto file = std::make_shared<File>(filename, blockSize);
  size_t erasedCount = files.erase(file);
  if (erasedCount == 0) throw std::domain_error("File with this name doesn't exist");
}

void AmoFS::renameFile(const std::string &oldFilename, const std::string &newFilename) {
  auto file = std::make_shared<File>(oldFilename, blockSize);
  auto searchingResult = getFileByName(oldFilename);
  if (searchingResult != nullptr) {
    files.erase(searchingResult);
    searchingResult->setFileName(newFilename);
    files.insert(searchingResult);
  } else {
    throw std::domain_error("File with this name doesn't exist");
  }
}

std::shared_ptr<File> AmoFS::getFileByName(const std::string &filename) {
  auto file = std::make_shared<File>(filename, blockSize);
  auto searchingResult = files.find(file);
  if (searchingResult != files.end()) {
    return *searchingResult;
  }
  return {nullptr};
}

void AmoFS::moveFile(const std::string &oldFilename, const std::string &newFilename) {
  renameFile(oldFilename, newFilename);// ahahahha 1-layer filesystem
}

std::shared_ptr<File> AmoFS::copyFile(const std::string &filenameOfOriginal, const std::string &filenameForCopy) {
  if (!getFileByName(filenameOfOriginal)) throw std::domain_error("File with this name doesn't exist");
  if (getFileByName(filenameForCopy)) throw std::domain_error("File with this name already exist");

  auto result = std::make_shared<File>(*getFileByName(filenameOfOriginal));
  result->setFileName(filenameForCopy);
  files.insert(result);
  return result;
}

void AmoFS::writeToFile(const std::string &filename, const std::shared_ptr<char> &buffer, size_t bytesCount) {
  auto destFile = getFileByName(filename);
  for (size_t i = destFile->blockSize * destFile->blocksCount; i < bytesCount; i += destFile->blockSize) {
    destFile->currentBlock->next = std::make_shared<File::Block>(blockSize);
    destFile->currentBlock = destFile->currentBlock->next;
    destFile->blocksCount++;
  }
  destFile->writeData(buffer, bytesCount);
}

void AmoFS::readFromFile(const std::string &filename, const std::shared_ptr<char> &buffer, size_t bytesCount) {
  getFileByName(filename)->readData(buffer, bytesCount);
}
size_t AmoFS::getBlockSize() const {
  return blockSize;
}
