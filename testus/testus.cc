//
// Created by artrayme on 11/28/21.
//

#include "testus.h"
#include "../amofs/amo_fs.h"
#include <iostream>

void Testus::testAll() {
  testFilesystemCreation();
}

void Testus::testFilesystemCreation() {
  std::cout << "Filesystem creation test started" << std::endl;

  size_t blockSize1 = 10;
  AmoFS filesystem1(blockSize1);
  if (filesystem1.getBlockSize() == blockSize1) {
    std::cout << "Test 1 Passed" << std::endl;
  } else {
    std::cout << "Test 1 Failed: expected = " << blockSize1 << ", provided = " << filesystem1.getBlockSize() << std::endl;
  }

  size_t blockSize2 = 0;
  try {
    AmoFS filesystem2(blockSize2);
    std::cout<<"Test 2 Failed: expected exception, but... all ok";
  } catch(const std::invalid_argument &ex) {
    std::cout << "Test 2 Passed" << std::endl;
  }
}

void Testus::testFileCreation() {
}
void Testus::testFileDeleting() {
}
void Testus::testFileSearching() {
}
void Testus::testFileMoving() {
}
void Testus::testFileCoping() {
}
void Testus::testFileWritingFromFilesystem() {
}
void Testus::testFileReadingFromFilesystem() {
}
void Testus::testFileWritingFromFile() {
}
void Testus::testFileReadingFromFile() {
}
