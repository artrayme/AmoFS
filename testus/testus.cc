//
// Created by artrayme on 11/28/21.
//

#include "testus.h"
#include "../amofs/amo_fs.h"
#include <iostream>

Color::Modifier testFailedColoring(Color::FG_RED);
Color::Modifier testPassedColoring(Color::FG_GREEN);
Color::Modifier defaultColoring(Color::FG_DEFAULT);

void Testus::testAll() {
  testFilesystemCreation();
  testFileCreation();
}

void Testus::testFilesystemCreation() {

  std::cout << "Filesystem creation test started" << std::endl;

  size_t blockSize1 = 10;
  AmoFS filesystem1(blockSize1);
  if (filesystem1.getBlockSize() == blockSize1) {
    std::cout << testPassedColoring << "Test 1 Passed" << defaultColoring << std::endl;
  } else {
    std::cout << testFailedColoring << "Test 1 Failed: "
              << "expected = " << blockSize1 << ", actual = " << filesystem1.getBlockSize()
              << defaultColoring << std::endl;
  }

  size_t blockSize2 = 0;
  try {
    AmoFS filesystem2(blockSize2);
    std::cout << testFailedColoring << "Test 2 Failed: expected exception, but... all ok" << defaultColoring << std::endl;
  } catch (const std::invalid_argument &ex) {
    std::cout << testPassedColoring << "Test 2 Passed" << defaultColoring << std::endl;
  }

  std::cout << "Filesystem creation test ended" << std::endl;
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
