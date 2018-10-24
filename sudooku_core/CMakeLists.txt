add_subdirectory(matrix)
add_subdirectory(solvers)
add_subdirectory(strategies)

add_library(
        core
        main.cpp
)

target_link_libraries(
        core
        matrix
        solvers
        strategies
)