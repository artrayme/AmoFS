//
// Created by artrayme on 11/27/21.
//

#include "amo_fs.h"
#include <memory>
#include <stdexcept>

AmoFS::AmoFS(size_t blockSize) {
  if (blockSize < 1) throw std::invalid_argument("Block size must be greater than 0");
  this->blockSize = blockSize;
}

std::shared_ptr<File> AmoFS::createFile(const std::string &filename) {
  auto file = std::make_shared<File>(filename, blockSize);
  auto insertionResult = files.insert(file);
  if (!insertionResult.second) throw std::domain_error("File with name \"" + filename + "\" doesn't exist");
  return file;
}

void AmoFS::deleteFile(const std::string &filename) {
  auto file = std::make_shared<File>(filename, blockSize);
  size_t erasedCount = files.erase(file);
  if (erasedCount == 0) throw std::domain_error("File with name \"" + filename + "\" doesn't exist");
  file->blocks.clear();
}

void AmoFS::renameFile(const std::string &oldFilename, const std::string &newFilename) {
  auto file = std::make_shared<File>(oldFilename, blockSize);
  auto searchingResult = getFileByName(oldFilename);

  if (searchingResult == nullptr) {
    throw std::domain_error("File with name \"" + oldFilename + "\" doesn't exist");
  }
  if (getFileByName(newFilename) != nullptr) {
    throw std::domain_error("File with name \"" + newFilename + "\" already exist");
  }

  files.erase(searchingResult);
  searchingResult->setFileName(newFilename);
  files.insert(searchingResult);
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
  if (getFileByName(filenameOfOriginal) == nullptr) throw std::domain_error("File with name \"" + filenameOfOriginal + "\" doesn't exist");
  if (getFileByName(filenameForCopy) != nullptr) throw std::domain_error("File with name \"" + filenameForCopy + "\" already exist");

  auto result = std::make_shared<File>(*getFileByName(filenameOfOriginal));
  result->setFileName(filenameForCopy);
  files.insert(result);
  return result;
}

void AmoFS::writeToFile(const std::string &filename, const std::shared_ptr<char> &buffer, size_t bytesCount) {
  auto destFile = getFileByName(filename);
  if (destFile == nullptr) {
    throw std::domain_error("File with name \"" + filename + "\" doesn't exist");
  }
  for (size_t i = blockSize * destFile->blocks.size(); i < bytesCount; i += blockSize) {
    destFile->blocks.emplace_back(std::vector<char>(blockSize));
  }
  destFile->writeData(buffer, bytesCount);
}

void AmoFS::readFromFile(const std::string &filename, const std::shared_ptr<char> &buffer, size_t bytesCount) {
  auto file = getFileByName(filename);
  if (file == nullptr) {
    throw std::domain_error("File with name \"" + filename + "\" doesn't exist");
  }
  file->readData(buffer, bytesCount);
}
size_t AmoFS::getBlockSize() const {
  return blockSize;
}
std::string AmoFS::createDump() {
  std::string dumpStr = "{\n  \"Files\": {";
  for (const auto &file : files) {
    dumpStr += "\n    \"" + file->getFilename() + "\": {\n      \"DataSize\": \"" + std::to_string(file->blocks.size()) + "\"\n    },";
  }
  dumpStr.pop_back();
  dumpStr += "\n  }\n}\n";
  return dumpStr;
}
