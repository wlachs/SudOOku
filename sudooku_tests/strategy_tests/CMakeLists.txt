add_executable(
        strategy_tests
        ../main.cpp
        columnStrategyTest.cpp
        rowStrategyTest.cpp
        groupStrategyTest.cpp
        diagonalStrategyTest.cpp
)

target_link_libraries(
        strategy_tests
        sudooku_core
        gmock_main
)

add_test(
        NAME
        strategy_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/strategy_tests
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/sudooku_tests/testInputs
)