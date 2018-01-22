cmake_minimum_required(VERSION 3.9)
project(cpp-practice)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
    CACHE STRING "Compiler flags in asan build"
    FORCE)
    
#### GTest

enable_testing()
add_subdirectory(../googletest/googletest bin)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})