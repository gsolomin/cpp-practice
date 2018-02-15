cmake_minimum_required(VERSION 3.9)
project(reduce)

include(../CMakeLists.txt)

include_directories(include)
set(LIB_SOURCES src/commons.cpp include/reduce.h)

add_library(reduce_lib ${LIB_SOURCES})

add_executable(test_reduce test/test.cpp)

target_link_libraries(test_reduce gtest gtest_main)
target_link_libraries(test_reduce reduce_lib)

add_benchmark(bench_reduce test/bench.cpp ${LIB_SOURCES})