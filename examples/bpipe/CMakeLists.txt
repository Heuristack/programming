include_directories(~/blp/include)
link_directories(~/blp/lib)
add_executable(BpipeClient main.cpp)
target_link_libraries(BpipeClient blpapi3_64)
