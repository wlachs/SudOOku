add_executable(
        solver_tests
        ../main.cpp
        solverTest.cpp
)

target_link_libraries(
        solver_tests
        sudooku_core
        gmock_main
)

add_test(
        NAME
        solver_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/solver_tests
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/../sudooku_tests/testInputs
)