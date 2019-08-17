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
include_directories($ENV{HOME}/blp/include)
link_directories($ENV{HOME}/blp/lib)

#
# Project
#
project(programming)

#
# Kernel Queue - kqueue
#

add_subdirectory(examples/kqueue)
#
# Bloomberg B-PIPE
#
add_subdirectory(examples/bpipe)

#
# Orion Message
#
add_subdirectory(examples/orion)


