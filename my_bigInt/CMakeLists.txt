cmake_minimum_required(VERSION 3.12)
project(my_bigInt)

set(CMAKE_CXX_STANDARD 14)

add_executable(my_bigInt main.cpp bigint.cpp bigint.h big_integer_testing.cpp big_integer_testing.h gtest.h gtest-all.cc gtest_main.cc)