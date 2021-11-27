//
// Created by artrayme on 11/27/21.
//

#ifndef AMOFS_AMOFS_AMO_FS_H_
#define AMOFS_AMOFS_AMO_FS_H_

#include "file.h"
#include <set>
#include <vector>

class AmoFS {
  struct FileCompare {
    bool operator()(const std::shared_ptr<File>& lhs, const std::shared_ptr<File>& rhs){
      return lhs->filename < rhs->filename;
    }
  };

 private:
  std::set<std::shared_ptr<File>, FileCompare> files;
  size_t blockSize;

 public:
  explicit AmoFS(size_t blockSize);
  std::shared_ptr<File> createFile(const std::string &filename);
  void deleteFile(const std::string &filename);
  void renameFile(const std::string &oldFilename, const std::string &newFilename) const;
  std::shared_ptr<File> getFileByName(const std::string &filename) const;
  void moveFile(const std::string &oldFilename, const std::string &newFilename) const;
  void writeToFile(const std::string &filename, const std::shared_ptr<char[]>& buffer, size_t bytesCount) const;
  void readFromFile(const std::string &filename, const std::shared_ptr<char[]>& buffer, size_t bytesCount) const;

};

#endif//AMOFS_AMOFS_AMO_FS_H_
