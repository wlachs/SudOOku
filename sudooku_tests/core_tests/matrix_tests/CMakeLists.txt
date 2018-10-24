add_executable(
        matrix_tests
        ../../main.cpp
        fieldTest.cpp
        forkHelperTest.cpp
        matrixTest.cpp
        helper_classes/mockMatrix.h
        helper_classes/mockMatrix.cpp
        helper_classes/mockField.h
)

target_link_libraries(
        matrix_tests
        core
        gmock_main
)

add_test(
        NAME
        matrix_tests
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/matrix_tests
        WORKING_DIRECTORY
        ${CMAKE_BINARY_DIR}/sudooku_tests/testInputs
)