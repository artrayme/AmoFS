//
// Created by artrayme on 11/28/21.
//

#ifndef AMOFS_TESTUS_BENCHMARKUS_H_
#define AMOFS_TESTUS_BENCHMARKUS_H_

#include <cstddef>
class Benchmarkus {
 public:
  void testAll();
  double* filesCreatingBenchmark(size_t blockSize, size_t filesCount);
  double*writingToFileBenchmark(size_t blockSize, size_t dataSize);
};

#endif//AMOFS_TESTUS_BENCHMARKUS_H_
