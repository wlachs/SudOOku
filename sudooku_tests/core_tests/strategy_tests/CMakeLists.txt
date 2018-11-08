add_executable(
        strategy_tests
        ../../main.cpp
        columnStrategyTest.cpp
        rowStrategyTest.cpp
        groupStrategyTest.cpp
        diagonalStrategyTest.cpp
)

target_link_libraries(
        strategy_tests
        strategies
        gmock_main
        input_handler
        visual
)

add_test(
        NAME
        strategy_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/strategy_tests
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/sudooku_tests/testInputs
)