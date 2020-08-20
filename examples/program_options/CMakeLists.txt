cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)
add_executable(program_options program_options.cpp)
target_link_libraries(program_options boost_program_options)

