add_executable(SudOOku main.cpp)

include_directories(sudooku_core)
include_directories(sudooku_visual)
include_directories(sudooku_controller)

add_subdirectory(sudooku_core)
add_subdirectory(sudooku_visual)
add_subdirectory(sudooku_controller)

target_link_libraries(
        SudOOku
        core
        visual
        controller
)