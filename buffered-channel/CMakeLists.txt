cmake_minimum_required(VERSION 3.9)
project(buffered_channel)

include(../CMakeLists.txt)

include_directories(include)
#add_library(buffered_channel_lib src/buffered_channel.h)
    
# #### GTest

add_executable(test_bufchannel test/test.cpp)

target_link_libraries(test_bufchannel gtest gtest_main)
#target_link_libraries(test_bufchannel buffered_channel_lib)

add_benchmark(bench_bufchannel test/bench.cpp)