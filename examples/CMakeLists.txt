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

add_subdirectory(kqueue)
add_subdirectory(lkfree)
add_subdirectory(bpipe)
add_subdirectory(orion)
add_subdirectory(rdtsc)
add_subdirectory(program_options)

