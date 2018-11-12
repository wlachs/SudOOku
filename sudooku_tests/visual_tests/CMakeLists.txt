add_executable(
        visual_tests
        ../main.cpp
        readMatrixFromFileTest.cpp
        printMatrixToFileTest.cpp
)

target_link_libraries(
        visual_tests
        visual
        core
        gmock_main
)

add_test(
        NAME
        visual_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/visual_tests
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/sudooku_tests/testInputs
)