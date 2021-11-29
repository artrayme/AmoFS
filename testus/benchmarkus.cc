//
// Created by artrayme on 11/28/21.
//

#include "benchmarkus.h"
#include "../amofs/amo_fs.h"
#include <iostream>

std::string *strings;

std::string gen_random(const int len) {
  static const char alphanum[] =
      "0123456789"
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz";
  std::string tmp_s;
  tmp_s.reserve(len);

  for (int i = 0; i < len; ++i) {
    tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
  }

  return tmp_s;
}

void Benchmarkus::testAll() {
  size_t filesCount = 1000;
  size_t blockSize = 1000;
  strings = new std::string[filesCount];
  for (int i = 0; i < filesCount; ++i) {
    strings[i] = gen_random(filesCount);
  }
  double *results = filesCreatingBenchmark(blockSize, filesCount);
  for (int i = 0; i < filesCount; ++i) {
    std::cout << results[i] << std::endl;
  }

  size_t bytesCount = 100;
  double *results2 = writingToFileBenchmark(blockSize, bytesCount);
  for (int i = 0; i < bytesCount; ++i) {
    std::cout << i << " " << results2[i] << std::endl;
  }

}

double *Benchmarkus::filesCreatingBenchmark(size_t blockSize, size_t filesCount) {
  auto *timeResults = new double[filesCount];
  auto filesystem = AmoFS(blockSize);
  for (int i = 0; i < filesCount; ++i) {
    clock_t tStart = clock();
    filesystem.createFile(strings[i]);
    timeResults[i] = (double) (clock() - tStart);
  }
  return timeResults;
}
double *Benchmarkus::writingToFileBenchmark(size_t blockSize, size_t dataSize) {
  auto *timeResults = new double[dataSize];
  auto filesystem = AmoFS(blockSize);
  auto file = filesystem.createFile("test");
  auto buf = std::shared_ptr<char>(new char[dataSize]);
  for (int i = 0; i < dataSize; ++i) {
    clock_t tStart = clock();
    filesystem.writeToFile(file->getFilename(), buf, i);
    timeResults[i] = (double) (clock() - tStart);
  }
  return timeResults;
}
