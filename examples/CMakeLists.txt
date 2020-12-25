cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_subdirectory(compute)
add_subdirectory(kqueue)
add_subdirectory(lock_free)
add_subdirectory(bpipe)
add_subdirectory(orion)
add_subdirectory(quant)
add_subdirectory(rdtsc)
add_subdirectory(program_options)

add_executable(accumulator accumulator/main.cpp)

add_executable(microbenchmark benchmark/main.cpp)
target_link_libraries(microbenchmark benchmark)
