add_library(
        input_handler
        inputHandler.h
        fileInputHandler.cpp
        fileInputHandler.h
)

target_link_libraries(
        input_handler
        core
)