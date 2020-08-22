#
# Toolchain Requirements
#
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

#
# Include and Link Directories
#
include_directories(./)
add_executable(traverse examples/traverse.cpp)
add_executable(clrs2404 examples/clrs2404.cpp)

