add_subdirectory(handlers)
add_subdirectory(exceptions)

add_library(
        controller
        sudookuController.cpp
        sudookuController.h
        sudookuEvents.h
)

target_link_libraries(
        controller
        controller_exceptions
        core
        visual
        input_handler
        output_handler
)