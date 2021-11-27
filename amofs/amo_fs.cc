//
// Created by artrayme on 11/27/21.
//

#include "amo_fs.h"
#include <memory>
#include <stdexcept>

AmoFS::AmoFS(size_t blockSize) {
  if (blockSize<1) throw std::invalid_argument("Block size must be greater than 1");
  this->blockSize = blockSize;
}

std::shared_ptr<File> AmoFS::createFile(const std::string &filename) {
  if (getFileByName(filename) != nullptr) throw std::domain_error("File with this name already exist");
  auto file = std::make_shared<File>(filename, blockSize);
  files.insert(file);
  return file;
}

void AmoFS::deleteFile(const std::string &filename) {
  auto file = getFileByName(filename);
  if (file == nullptr) throw std::domain_error("File with this name doesn't exist");
  files.erase(file);
}

void AmoFS::renameFile(const std::string &oldFilename, const std::string &newFilename) const {
  auto file = getFileByName(oldFilename);
  if (file == nullptr) throw std::domain_error("File with this name doesn't exist");
  file->setFileName(newFilename);
}

std::shared_ptr<File> AmoFS::getFileByName(const std::string &filename) const {
  for (auto &file : files) {
    if (file->filename == filename) return file;
  }
  return {nullptr};
}

void AmoFS::moveFile(const std::string &oldFilename, const std::string &newFilename) const {
  renameFile(oldFilename, newFilename);// ahahahha 1-layer filesystem
}

void AmoFS::writeToFile(const std::string &filename, const std::shared_ptr<char[]> &buffer, size_t bytesCount) const {
  auto destFile = getFileByName(filename);
  for (size_t i = destFile->blockSize * destFile->blocksCount; i < bytesCount; i += destFile->blockSize) {
    destFile->currentBlock->next = std::make_shared<File::Block>(blockSize);
  }
  destFile->writeData(buffer, bytesCount);
}

void AmoFS::readFromFile(const std::string &filename, const std::shared_ptr<char[]> &buffer, size_t bytesCount) const {
  getFileByName(filename)->readData(buffer, bytesCount);
}
