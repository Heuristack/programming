cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(BpipeClient)

include_directories(~/blp/include)
link_directories(~/blp/lib)
add_executable(BpipeClient main.cpp)
target_link_libraries(BpipeClient blpapi3_64)

