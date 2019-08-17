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
# Target
#
add_executable(BpipeClient main.cpp)
target_link_libraries(BpipeClient blpapi3_64)

