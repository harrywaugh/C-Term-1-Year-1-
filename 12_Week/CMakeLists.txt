cmake_minimum_required(VERSION 3.6)
project(12_Week)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES libraryTester.c list.c)
set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS} -std=c99 -Wall -pedantic -O3" )
add_executable(12_Week ${SOURCE_FILES})