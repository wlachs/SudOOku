add_subdirectory(handlers)

add_library(
        controller
        sudookuController.cpp
        sudookuController.h
)

target_link_libraries(
        controller
        input_handler
        output_handler
)