cmake_minimum_required(VERSION 3.9)
project(calculator)

include(../CMakeLists.txt)

include_directories(include)
add_library(calc_lib 	src/eval.cpp
						src/calculator.cpp)

# #### GTest

add_executable(test_calculator test/test.cpp)

target_link_libraries(test_calculator gtest gtest_main)
target_link_libraries(test_calculator calc_lib)

