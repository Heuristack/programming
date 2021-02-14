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
add_executable(partition structure/array/partition.cpp)
add_executable(k-way_merge structure/heap/k-way_merge.cpp)
add_executable(linked_list structure/linked_list/linked_list.cpp)
add_executable(binary_tree structure/binary_tree/binary_tree.cpp)
add_executable(hash_string structure/hash_table/hash_string.cpp)
add_executable(union_find structure/union_find/union_find.cpp)
add_executable(stack structure/stack/stack.cpp)
add_executable(queue structure/queue/queue.cpp)
add_executable(cyclic_list structure/linked_list/cyclic_list.cpp)
add_executable(heap_usages structure/heap/heap_usages.cpp)
add_executable(is_heap structure/heap/is_heap.cpp)
add_executable(priority_queue_usages structure/heap/priority_queue_usages.cpp)
add_executable(count_bits structure/bitset/count_bits.cpp)
add_executable(merge_interval structure/interval/merge.cpp)
add_executable(disjoint_interval structure/interval/is_disjoint.cpp)

#
# 02 Algo Techniques - RBBDDG
#
add_executable(iteration_n_recursion algorithm/iteration_n_recursion/iteration_n_recursion.cpp)
add_executable(backtracking algorithm/backtracking/n-permutation.cpp)
add_executable(branch_n_bound algorithm/branch_n_bound/knapsack.cpp)
add_executable(divide_n_conquer algorithm/divide_n_conquer/divide_n_conquer.cpp)
add_executable(dynamic_programming algorithm/dynamic_programming/minimum_coins_change.cpp)
add_executable(greedy_strategy algorithm/greedy_strategy/greedy_coins_change.cpp)
add_executable(generate_canonical algorithm/monte_carlo_method/generate_canonical.cpp)
add_executable(generate_gausslan algorithm/monte_carlo_method/generate_gausslan.cpp)


add_executable(euclidean algorithm/iteration_n_recursion/euclidean.cpp)
add_executable(fibonacci algorithm/iteration_n_recursion/fibonacci.cpp)
add_executable(factorial algorithm/iteration_n_recursion/factorial.cpp)
add_executable(powerset  algorithm/iteration_n_recursion/powerset.cpp)
add_executable(enumerate_pairs algorithm/iteration_n_recursion/enumerate_pairs.cpp)
add_executable(tsp algorithm/branch_n_bound/traveling_salesman.cpp)
add_executable(n-queens algorithm/backtracking/n-queens.cpp)
add_executable(maximum_subarray algorithm/divide_n_conquer/maximum_subarray.cpp)
add_executable(count_paths algorithm/dynamic_programming/count_paths_on_board.cpp)

#
# 03 Searching - BT
#
add_executable(binary_search searching/binary_search/binary_search.cpp)
add_executable(board_search searching/binary_search/board_search.cpp)
add_executable(lower_bound searching/binary_search/bound_search.cpp)
add_executable(tree_search searching/tree_search/binary_search_tree.cpp)
add_executable(k_largest_bst searching/tree_search/k_largest.cpp)
add_executable(lca_bst searching/tree_search/lowest_common_ancestor.cpp)
add_executable(construct_bst searching/tree_search/construct.cpp)
add_executable(n-puzzle searching/puzzle/puzzle.cpp)
add_executable(region searching/puzzle/region.cpp)
add_executable(maze searching/puzzle/maze.cpp)
add_executable(noughts_n_crosses searching/game/noughts_n_crosses.cpp)
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
add_executable(graph_flood graph/examples/flood.cpp)
add_executable(graph_class graph/examples/class.cpp)
add_executable(graph_simple graph/examples/simple.cpp)
add_executable(graph_tree graph/examples/tree.cpp)

