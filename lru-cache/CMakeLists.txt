cmake_minimum_required(VERSION 3.9)
project(lru_cache)

include(../CMakeLists.txt)

include_directories(include)
add_library(lru_cache_lib src/lru_cache.cpp)
    
#### GTest

add_executable(test_lru_cache test/test.cpp)

target_link_libraries(test_lru_cache gtest gtest_main)
target_link_libraries(test_lru_cache lru_cache_lib)
