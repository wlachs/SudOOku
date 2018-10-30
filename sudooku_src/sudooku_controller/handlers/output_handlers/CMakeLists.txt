add_library(
        output_handler
        outputHandler.h
        fileOutputHandler.cpp
        fileOutputHandler.h
)

target_link_libraries(
        output_handler
        controller_exceptions
        core
        visual
)