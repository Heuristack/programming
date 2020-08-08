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
# Project
#
project(programming)

#
# Kernel Queue - kqueue
#
add_subdirectory(examples/kqueue)

#
# Lock Free Data Structures
#
add_subdirectory(examples/lkfree)

#
# Bloomberg B-PIPE
#
add_subdirectory(examples/bpipe)

#
# Orion Message
#
add_subdirectory(examples/orion)

#
# Read Timestamp Counter
#
add_subdirectory(examples/rdtsc)

