include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runStrategyTests
        columnStrategyTest.cpp)

target_link_libraries(runStrategyTests gtest gtest_main)
target_link_libraries(runStrategyTests sudooku_core)
