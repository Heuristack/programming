cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(OrionClient)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(OrionClient src/main.cpp)
target_link_libraries(OrionClient boost_system yaml-cpp)
