cmake_minimum_required(VERSION 3.9)
project(cpp-practice)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -g ")

set(CMAKE_CXX_FLAGS_ASAN "-g -fsanitize=address,undefined -fno-sanitize-recover=all"
    CACHE STRING "Compiler flags in asan build"
    FORCE)

#### GTest

enable_testing()
add_subdirectory(../common/googletest/googletest bin/gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# add_benchmark
function(add_benchmark BINARY_NAME)
  	list(REMOVE_AT ARGV 0)

	set(GTEST_LIBRARY ${gtest_SOURCE_DIR})
	set(GTEST_INCLUDE_DIR ${gtest_SOURCE_DIR}/include)
	set(GTEST_MAIN_LIBRARY ${gtest_SOURCE_DIR})

	add_subdirectory(../common/benchmark bin/benchmark)
	include_directories(../common/benchmark/include)

	add_executable(${BINARY_NAME} ${ARGV})
	target_link_libraries(${BINARY_NAME} benchmark pthread)
endfunction(add_benchmark)

