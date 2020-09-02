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
# Project - DAGSS
#
project(algo)

#
# 01 Data Structures - AHLBHUSQ
#

#
# 02 Algo Techniques - BDBGDB
#

#
# 03 Graph - BDKPBD
#
include_directories(graph)
add_executable(graph_traverse graph/examples/traverse.cpp)
add_executable(graph_clrs2404 graph/examples/clrs2404.cpp)

#
# 04 Searching - BT
#

#
# 05 Sorting - ISBHMQ
#
#add_subdirectory(sorting)
include_directories(sorting)
add_executable(sorting_compete sorting/examples/compete.cpp)

