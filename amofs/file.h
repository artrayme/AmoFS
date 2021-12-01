//
// Created by artrayme on 11/27/21.
//

#ifndef AMOFS_AMOFS_FILE_H_
#define AMOFS_AMOFS_FILE_H_

#include <cstddef>
#include <list>
#include <memory>
#include <string>
#include <vector>

class File {
  std::string filename;
  size_t blockSize;
  std::list<std::vector<char>> blocks;

  void setFileName(const std::string &newFilename);

  friend class AmoFS;

 public:
  void readData(const std::shared_ptr<char> &buffer, size_t bytesCount) const;
  void writeData(const std::shared_ptr<char> &buffer, size_t bytesCount);
  std::string getFilename() const;
  size_t getBlockSize() const;
  File(std::string filename, size_t blockSize);
  File(const File &other);
};

#endif//AMOFS_AMOFS_FILE_H_
