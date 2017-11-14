cmake_minimum_required(VERSION 3.6)
project(11_Week)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES calc.c stack.c)
set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS} -std=c99 -Wall -pedantic -O3" )
add_executable(11_Week ${SOURCE_FILES})