cmake_minimum_required(VERSION 3.9)
project(unbuffered_channel)

include(../CMakeLists.txt)

include_directories(include)

# #### GTest

add_executable(test_unbufchannel test/test.cpp)

target_link_libraries(test_unbufchannel gtest gtest_main)
#target_link_libraries(test_unbufchannel buffered_channel_lib)

add_benchmark(bench_unbufchannel test/bench.cpp)

