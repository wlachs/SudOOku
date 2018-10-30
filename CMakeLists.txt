cmake_minimum_required(VERSION 3.5)
project(SudOOku)

# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# we use this to get code coverage
if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -Wall -Wextra -fmax-errors=5 -Wstrict-aliasing -pedantic -Werror -Wunreachable-code -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wno-unused -Wno-variadic-macros -Wno-parentheses -fdiagnostics-show-option")
endif ()

set(CMAKE_CXX_STANDARD 14)  # enable C++14 standard

add_executable(SudOOku main.cpp)

include_directories(sudooku_core)
include_directories(sudooku_visual)
include_directories(sudooku_controller)
include_directories(sudooku_tests)

add_subdirectory(sudooku_core)
add_subdirectory(sudooku_visual)
add_subdirectory(sudooku_controller)
add_subdirectory(sudooku_tests)

target_link_libraries(
        SudOOku
        core
        visual
        controller
)

include(cmake/googletest.cmake)
fetch_googletest(
        ${PROJECT_SOURCE_DIR}/cmake
        ${PROJECT_BINARY_DIR}/googletest
)

enable_testing()