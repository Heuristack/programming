cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
add_executable(equity_option_pricing EquityOption.cpp)
target_link_libraries(equity_option_pricing quantlib)
add_executable(quant_main main.cpp)
target_link_libraries(quant_main quantlib)

