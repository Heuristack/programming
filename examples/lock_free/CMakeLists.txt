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
# Target
#
add_executable(lock_free_queue queue.cpp)
add_executable(lock_free_stack stack.cpp)
add_executable(lock_spsc_queue spsc.cpp)

