//
// Created by Borbély László on 2018. 10. 20..
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

/**
 * Main testing function
 * Activates GoogleTest and GoogleMock
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}