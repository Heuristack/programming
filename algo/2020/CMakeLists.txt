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
add_executable(array structure/array/partition_forward.cpp)
add_executable(heap structure/heap/n_way_merge.cpp)
add_executable(linked_list structure/linked_list/linked_list.cpp)
add_executable(binary_tree structure/binary_tree/traverse.cpp)
add_executable(hash_table structure/hash_table/hash_string.cpp)
add_executable(union_find structure/union_find/union_find.cpp)
add_executable(stack structure/stack/stack.cpp)
add_executable(queue structure/queue/queue.cpp)

#
# 02 Algo Techniques - BDBGDB
#
add_executable(brute_force algorithm/brute_force/iteration_vs_recursion.cpp)
add_executable(divide_conquer algorithm/divide_conquer/recursion_tree.cpp)
add_executable(backtracking algorithm/backtracking/permutation.cpp)
add_executable(greedy_strategy algorithm/greedy_strategy/greedy_coin_changing.cpp)
add_executable(dynamic_programming algorithm/dynamic_programming/dynamic_coin_changing.cpp)
add_executable(branch_bound algorithm/branch_bound/main.cpp)

#
# 03 Searching - BT
#
add_executable(binary_search searching/binary_search/binary_search.cpp)
add_executable(binary_search_tree_search searching/binary_search_tree_search/binary_search_tree_search.cpp)

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

