add_executable(
        matrix_tests
        ../main.cpp
        fieldTest.cpp
)

target_link_libraries(
        matrix_tests
        sudooku_core
        gtest_main
)

add_test(
        NAME
        matrix_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/strategy_tests
)