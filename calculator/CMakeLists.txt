cmake_minimum_required(VERSION 3.9)

project(project-1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")

include_directories(include)

add_library(calc_lib 	src/eval.cpp
						src/calculator.cpp)


set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
    CACHE STRING "Compiler flags in asan build"
    FORCE)
    
#### GTest

enable_testing()
add_subdirectory(../googletest/googletest bin)
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(test_calculator test/test.cpp)

target_link_libraries(test_calculator gtest gtest_main)
target_link_libraries(test_calculator calc_lib)

