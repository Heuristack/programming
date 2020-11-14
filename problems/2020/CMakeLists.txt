cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0")
project(prob)
include_directories(~/repositories/programming/algo/2020)
add_executable(linked_list_test linked_list_test.cpp)
add_executable(binary_tree_test binary_tree_test.cpp)

