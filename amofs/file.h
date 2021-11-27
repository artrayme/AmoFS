//
// Created by artrayme on 11/27/21.
//

#ifndef AMOFS_AMOFS_FILE_H_
#define AMOFS_AMOFS_FILE_H_

#include <cstddef>
#include <memory>
#include <string>

class File {
  struct Block {
    explicit Block(size_t size) {
      data = std::make_unique<char[]>(size);
    }
    std::shared_ptr<Block> next;
    std::shared_ptr<char[]> data;
  };
  std::string filename;
  size_t blockSize;
  size_t blocksCount;
  std::shared_ptr<Block> firstBlock;
  std::shared_ptr<Block> currentBlock;

  void setFileName(const std::string &newFilename);

  friend class AmoFS;

 public:
  void readData(const std::shared_ptr<char[]> &data, size_t bytesCount) const;
  void writeData(const std::shared_ptr<char[]> &data, size_t bytesCount) const;
  std::string getFilename() const;
  size_t getBlockSize() const;
  File(std::string filename, size_t blockSize);
  bool operator==(const File &rhs) const;
  bool operator!=(const File &rhs) const;
};

#endif//AMOFS_AMOFS_FILE_H_
