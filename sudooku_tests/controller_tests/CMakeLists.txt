add_executable(
        controller_tests
        ../main.cpp
        controllerTest.cpp
        fileInputHandlerTest.cpp
        fileOutputHandlerTest.cpp
        helper_classes/mockInputHandler.h
        helper_classes/mockOutputHandler.h
)

target_link_libraries(
        controller_tests
        core
        controller
        gmock_main
)

add_test(
        NAME
        controller_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/controller_tests
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/sudooku_tests/testInputs
)