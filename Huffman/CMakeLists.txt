cmake_minimum_required(VERSION 3.12)
project(Huffman)

set(CMAKE_CXX_STANDARD 14)

add_executable(Huffman main.cpp test.cpp huffman.h huffman.cpp HuffmanArchiver.h HuffmanArchiver.cpp)