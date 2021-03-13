#
# Toolchain Requirements
#
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O0")

#
# Include and Link Directories
#
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

#
# Project - Boot Camp
#
add_executable(BC01 bootcamp/01_linked_list.cpp)
add_executable(BC02 bootcamp/02_binary_tree.cpp)

