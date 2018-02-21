cmake_minimum_required(VERSION 3.9)
project(rwlock)

include(../CMakeLists.txt)
include_directories(include)

add_executable(test_rwlock test/test.cpp)
target_link_libraries(test_rwlock gtest gtest_main)

add_benchmark(bench_rwlock test/bench.cpp ${LIB_SOURCES})