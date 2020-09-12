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
# Project - DASSG
#
project(algo)

#
# 01 Data Structures - AHLBHUSQ
#
add_executable(array structure/array/partition.cpp)
add_executable(heap structure/heap/merge.cpp)
add_executable(linked_list structure/linked_list/linked_list.cpp)
add_executable(binary_tree structure/binary_tree/binary_tree_depth_order_traverse.cpp)
add_executable(hash_table structure/hash_table/hash_string.cpp)
#add_executable(union_find structure/union_find/)
add_executable(stack structure/stack/stack.cpp)
add_executable(queue structure/queue/queue.cpp)

#
# 02 Algo Techniques - BDBGDB
#

#
# 03 Searching - BT
#

#
# 04 Sorting - ISBHMQ
#
include_directories(sorting)
add_executable(sorting_compete sorting/examples/compete.cpp)

#
# 05 Graph - BDKPBD
#
include_directories(graph)
add_executable(graph_traverse graph/examples/traverse.cpp)
add_executable(graph_clrs2404 graph/examples/clrs2404.cpp)

