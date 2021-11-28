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
  testFileDeleting();
  testFileMoving();
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
  std::cout << "File creation test started" << std::endl;

  size_t blockSize = 10;
  AmoFS filesystem(blockSize);

  std::string expectedFilename1 = "testFile";
  filesystem.createFile(expectedFilename1);
  auto actual1 = filesystem.getFileByName(expectedFilename1);
  if (actual1->getFilename() == expectedFilename1) {
    std::cout << testPassedColoring << "Test 1 Passed" << defaultColoring << std::endl;
  } else {
    std::cout << testFailedColoring << "Test 1 Failed: "
              << "expected = " << expectedFilename1 << ", actual1 = " << actual1->getFilename()
              << defaultColoring << std::endl;
  }

  std::string nonexistentFile = "I don't exist";
  auto actual2 = filesystem.getFileByName(nonexistentFile);
  if (actual2 == nullptr) {
    std::cout << testPassedColoring << "Test 2 Passed" << defaultColoring << std::endl;
  } else {
    std::cout << testFailedColoring << "Test 2 Failed: "
              << "expected = nullptr"
              << ", actual1 = " << actual2
              << defaultColoring << std::endl;
  }

  try {
    filesystem.createFile(expectedFilename1);
    std::cout << testFailedColoring << "Test 3 Failed: expected exception, but... all ok" << defaultColoring << std::endl;
  } catch (const std::domain_error &error) {
    std::cout << testPassedColoring << "Test 3 Passed" << defaultColoring << std::endl;
  }

  std::cout
      << "File creation test ended" << std::endl;
}

void Testus::testFileDeleting() {
  std::cout << "File deleting test started" << std::endl;

  size_t blockSize = 10;
  AmoFS filesystem(blockSize);

  std::string expectedFilename1 = "testFile";
  filesystem.createFile(expectedFilename1);
  filesystem.deleteFile(expectedFilename1);
  auto file = filesystem.getFileByName(expectedFilename1);
  if (file == nullptr) {
    std::cout << testPassedColoring << "Test 1 Passed" << defaultColoring << std::endl;
  } else {
    std::cout << testFailedColoring << "Test 1 Failed: "
              << "file was not deleted"
              << defaultColoring << std::endl;
  }

  try {
    filesystem.deleteFile(expectedFilename1);
    std::cout << testFailedColoring << "Test 2 Failed: expected exception, but... all ok" << defaultColoring << std::endl;
  } catch (const std::domain_error &error) {
    std::cout << testPassedColoring << "Test 2 Passed" << defaultColoring << std::endl;
  }

  std::cout
      << "File deleting test ended" << std::endl;
}

void Testus::testFileMoving() {
  std::cout << "File moving test started" << std::endl;

  size_t blockSize = 10;
  AmoFS filesystem(blockSize);

  std::string expectedFilename1 = "testFile";
  std::string expectedFilename2 = "testFile2";
  auto actual1 = filesystem.createFile(expectedFilename1);
  filesystem.moveFile(expectedFilename1, expectedFilename2);
  if (actual1->getFilename() == expectedFilename2) {
    std::cout << testPassedColoring << "Test 1 Passed" << defaultColoring << std::endl;
  } else if (filesystem.getFileByName(expectedFilename1) != nullptr) {
    std::cout << testFailedColoring << "Test 1 Failed: "
              << "file with name \"" << expectedFilename1 << "\" also exists"
              << defaultColoring << std::endl;
  } else {
    std::cout << testFailedColoring << "Test 1 Failed: "
              << "filename was not changed"
              << defaultColoring << std::endl;
  }

  try {
    filesystem.moveFile(expectedFilename1, expectedFilename2);
    std::cout << testFailedColoring << "Test 2 Failed: expected exception, but... all ok" << defaultColoring << std::endl;
  } catch (const std::domain_error &error) {
    std::cout << testPassedColoring << "Test 2 Passed" << defaultColoring << std::endl;
  }

  std::cout
      << "File moving test ended" << std::endl;
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
