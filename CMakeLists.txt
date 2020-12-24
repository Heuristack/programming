cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

project(programming)

add_subdirectory(algorithm)
add_subdirectory(books/ecpp)
add_subdirectory(examples)
add_subdirectory(problems)
