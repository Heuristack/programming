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
include_directories(structure)
include_directories(algorithm)
include_directories(searching)
include_directories(sorting)
include_directories(sorting/include)
include_directories(graph)
include_directories(graph/include)

#
# 01 Data Structures - AHLBHUSQ
#
add_executable(array structure/array/partition_forward.cpp)
add_executable(heap structure/heap/n_way_merge.cpp)
add_executable(linked_list structure/linked_list/linked_list.cpp)
add_executable(binary_tree structure/binary_tree/binary_tree.cpp)
add_executable(hash_table structure/hash_table/hash_string.cpp)
add_executable(union_find structure/union_find/union_find.cpp)
add_executable(stack structure/stack/stack.cpp)
add_executable(queue structure/queue/queue.cpp)
add_executable(cyclic_list structure/linked_list/cyclic_list.cpp)

#
# 02 Algo Techniques - BBBDDG
#
add_executable(brute_force algorithm/brute_force/powerset.cpp)
add_executable(backtracking algorithm/backtracking/n-permutation.cpp)
add_executable(branch_n_bound algorithm/branch_n_bound/knapsack.cpp)
add_executable(divide_n_conquer algorithm/divide_n_conquer/maximum_subarray.cpp)
add_executable(dynamic_programming algorithm/dynamic_programming/minimum_coins_change.cpp)
add_executable(greedy_strategy algorithm/greedy_strategy/greedy_coins_change.cpp)

add_executable(euclidean algorithm/brute_force/euclidean.cpp)
add_executable(fibonacci algorithm/brute_force/fibonacci.cpp)
add_executable(factorial algorithm/brute_force/factorial.cpp)
add_executable(state_expansion algorithm/brute_force/state_expansion_recursion.cpp)
add_executable(board_count algorithm/dynamic_programming/count_paths_on_board.cpp)
add_executable(traveling_salesman algorithm/branch_n_bound/traveling_salesman.cpp)
add_executable(n-queens algorithm/backtracking/n-queens.cpp)
add_executable(space_division algorithm/divide_n_conquer/space_division_recursion.cpp)

#
# 03 Searching - BT
#
add_executable(binary_search searching/binary_search/binary_search.cpp)
add_executable(tree_search searching/tree_search/binary_search_tree.cpp)
add_executable(noughts_n_crosses searching/game/noughts_n_crosses.cpp)
add_executable(n-puzzle searching/puzzle/n-puzzle.cpp)
add_executable(board_explore searching/state_space/enumerate_paths_on_board.cpp)

#
# 04 Sorting - ISBHMQ
#
add_executable(sorting_compare sorting/examples/compare.cpp)

#
# 05 Graph - BDKPBD
#
add_executable(graph_generate graph/examples/generate.cpp)
add_executable(graph_traverse graph/examples/traverse.cpp)
add_executable(graph_search graph/examples/search.cpp)
add_executable(graph_sssp graph/examples/sssp.cpp)
add_executable(graph_mst graph/examples/mst.cpp)
add_executable(graph_flood_fill graph/examples/flood_fill.cpp)
