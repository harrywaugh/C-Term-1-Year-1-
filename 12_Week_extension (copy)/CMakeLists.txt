cmake_minimum_required(VERSION 3.6)
project(Week_12)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES tree.c tree.h huffman.c list.c list.h)
set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS} -std=c99 -Wall -pedantic -O3" )
add_executable(Week_12 ${SOURCE_FILES})