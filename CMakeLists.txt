cmake_minimum_required(VERSION 3.11)
project(SudOOku)

set(CMAKE_CXX_STANDARD 14)  # enable C++14 standard

add_executable(sudooku main.cpp matrix/matrix.cpp matrix/matrix.h matrix/field.cpp matrix/field.h strategies/solvingStrategy.cpp strategies/solvingStrategy.h strategies/rowStrategy.cpp strategies/strategies.h solvers/solver.cpp solvers/solver.h strategies/columnStrategy.cpp)