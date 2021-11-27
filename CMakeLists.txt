cmake_minimum_required(VERSION 3.20)
project(AmoFS)

set(CMAKE_CXX_STANDARD 14)

add_executable(AmoFS main.cpp amofs/amo_fs.cc amofs/amo_fs.h amofs/file.cc amofs/file.h testus/testus.cc testus/testus.h testus/benchmarkus.cc testus/benchmarkus.h)
