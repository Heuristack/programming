#
# Toolchain Requirements
#
cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

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
add_executable(d01_a 01_data-structure/01_Array.cpp)
add_executable(d02_h 01_data-structure/02_Heap.cpp)
add_executable(d03_l 01_data-structure/03_LinkedList.cpp)
add_executable(d04_b 01_data-structure/04_BinaryTree.cpp)
add_executable(d05_h 01_data-structure/05_HashTable.cpp)
add_executable(d06_u 01_data-structure/06_UnionFind.cpp)
add_executable(d07_s 01_data-structure/07_Stack.cpp)
add_executable(d08_q 01_data-structure/08_Queue.cpp)

#
# 02 Algo Techniques - BDBGDB
#
add_executable(a01_b 02_algo-technique/01_BruteForce.cpp)
add_executable(a02_d 02_algo-technique/02_DivideConquer.cpp)
add_executable(a03_b 02_algo-technique/03_Backtracking.cpp)
add_executable(a04_g 02_algo-technique/04_GreedyStrategy.cpp)
add_executable(a05_d 02_algo-technique/05_DynamicProgramming.cpp)
add_executable(a06_b 02_algo-technique/06_BranchBound.cpp)

#
# 03 Graph - BDKPBD
#
add_executable(g01_b 03_graph/01_BreadthFirstSearch.cpp)
add_executable(g02_d 03_graph/02_DepthFirstSearch.cpp)
add_executable(g03_k 03_graph/03_Kruskal.cpp)
add_executable(g04_p 03_graph/04_Prim.cpp)
add_executable(g05_b 03_graph/05_BellmanFord.cpp)
add_executable(g06_d 03_graph/06_Dijkstra.cpp)

#
# 04 Searching - BT
#
add_executable(r01_b 04_searching/01_BinarySearch.cpp)
add_executable(r02_t 04_searching/02_BinarySearchTreeSearch.cpp)

#
# 05 Sorting - ISBHMQ
#
add_executable(s01_i 05_sorting/01_InsertionSort.cpp)
add_executable(s02_s 05_sorting/02_SelectionSort.cpp)
add_executable(s03_b 05_sorting/03_BubbleSort.cpp)
add_executable(s04_h 05_sorting/04_HeapSort.cpp)
add_executable(s05_m 05_sorting/05_MergeSort.cpp)
add_executable(s06_q 05_sorting/06_QuickSort.cpp)
add_executable(mains 05_sorting/main.cpp)

