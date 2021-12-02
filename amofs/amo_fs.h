//
// Created by artrayme on 11/27/21.
//

#ifndef AMOFS_AMOFS_AMO_FS_H_
#define AMOFS_AMOFS_AMO_FS_H_

#include "file.h"
#include <set>

class AmoFS {
  // Set comparator
  struct FileCompare {
    bool operator()(const std::shared_ptr<File> &lhs, const std::shared_ptr<File> &rhs) {
      return lhs->filename < rhs->filename;
    }
  };

 private:
  std::set<std::shared_ptr<File>, FileCompare> files;
  size_t blockSize;

 public:
  /**
   * Main constructor.
   *
   * @param blockSize - size of a one file block.
   * @throw std::invalid_argument if you try to pass number that less than 1
   * */
  explicit AmoFS(size_t blockSize);

  /**
   * Method for creating a file.
   *
   * @param filename - name of the created file. Should be unique for filesystem.
   * @return Pointer on the created file.
   * @throw  std::domain_error if you try to crate file with name that already exists in the filesystem.
   * */
  std::shared_ptr<File> createFile(const std::string &filename);

  /**
   * Method for deleting a file.
   *
   * @param filename - nome of the file that you are want to delete.
   * @throw std::domain_error if you try to delete file that does not exist
   * */

  void deleteFile(const std::string &filename);

  /**
   * Method for renaming a file.
   *
   * @param oldFilename name of file that you are want to rename.
   * @param newFilename new name for file.
   * @throw std::domain_error if you try to rename file that does not exist or set new file name that already exists.
   * */
  void renameFile(const std::string &oldFilename, const std::string &newFilename);

  /**
   * Method to get a file object by its name.
   *
   * @param filename - name of file.
   * @return file with passed name or nullptr if file does not exist.
  */
  std::shared_ptr<File> getFileByName(const std::string &filename);

  /**
   * Method for moving a file.
   * Actually, this method just rename file, because filesystem has only one level.
   *
   * @param oldFilename - name of the file for moving
   * @param newFilename - name of destination place for moved file
   * @throw see renameFile method
   *
   * */
  void moveFile(const std::string &oldFilename, const std::string &newFilename);

  /**
   * Method for coping a file.
   *
   * @param filenameOfOriginal - name of a file for coping.
   * @param filenameForCopy - name for the file copy
   * @throw  std::domain_error if you try to copy file that does not exist
   * or create file copy with name that already exists
   * */
  std::shared_ptr<File> copyFile(const std::string &filenameOfOriginal, const std::string &filenameForCopy);

  /**
   * Method for writing data to file.
   *
   * @param filename - the name of the file into which the writing will be made.
   * @param buffer - char array, that will be writen to the file.
   * @param bytesCount - count of chars (bytes), that will be writen to the file.
   * */
  void writeToFile(const std::string &filename, const std::shared_ptr<char> &buffer, size_t bytesCount);

  /**
   * Method for reading data from file.
   *
   * @param filename - the name of the file from which the reading will be made.
   * @param buffer - char array, into which the information will be read.
   * @param bytesCount - count of chars (bytes), that will be read from the file.
   * */
  void readFromFile(const std::string &filename, const std::shared_ptr<char> &buffer, size_t bytesCount);

  /**
   * Method for dumping filesystem.
   *
   * @return string with filesystem structure.
   * */
  std::string createDump();

  size_t getBlockSize() const;
};

#endif//AMOFS_AMOFS_AMO_FS_H_
