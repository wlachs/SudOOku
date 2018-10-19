cmake_minimum_required(VERSION 3.11)
project(SudOOku)

set(CMAKE_CXX_STANDARD 14)  # enable C++14 standard

add_executable(SudOOku main.cpp)

include_directories(sudooku_core)
add_subdirectory(sudooku_core)
add_subdirectory(sudooku_tests)

target_link_libraries(SudOOku sudooku_core)