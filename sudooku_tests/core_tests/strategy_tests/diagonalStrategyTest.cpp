//
// Created by Borbély László on 2018. 10. 21..
//

#include <sudooku_core/strategies/diagonalStrategy.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include "gtest/gtest.h"

/**
 * DiagonalStrategy test fixture class
 */
class DiagonalStrategyTests : public ::testing::Test {
protected:
    SolvingStrategy *diagonalStrategy = nullptr;
    Matrix m1;

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Initialize DiagonalStrategy */
        diagonalStrategy = new DiagonalStrategy{};

        /* Initialize input Matrix */
        m1 = FileInputHandler{{false}, "small4.mat"}.readInput();

        /* Remove some values to test diagonal strategy functionality */
        m1[{1, 1}].removeValue(4);
        m1[{2, 2}].removeValue(4);
        m1[{3, 3}].removeValue(4);
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Free DiagonalStrategy object to prevent memory leak */
        delete diagonalStrategy;
    }
};

/**
 * Test case to check whether a Matrix is valid or not
 */
TEST_F(DiagonalStrategyTests, validation_check_false_1) {
    /* Initialize input Matrix */
    Matrix invalid = FileInputHandler{{false}, "invalid4.mat"}.readInput();

    /* Check validity
     * Should return false */
    ASSERT_FALSE(diagonalStrategy->validate(invalid));
}

/**
 * Test case to check whether a Matrix is valid or not
 */
TEST_F(DiagonalStrategyTests, validation_check_false_2) {
    /* Initialize input Matrix */
    Matrix invalid = FileInputHandler{{false}, "invalid5.mat"}.readInput();

    /* Check validity
     * Should return false */
    ASSERT_FALSE(diagonalStrategy->validate(invalid));
}

/**
 * Test case to check whether a Matrix is valid or not
 */
TEST_F(DiagonalStrategyTests, validation_check_true) {
    /* Check validity
     * Should return true */
    ASSERT_TRUE(diagonalStrategy->validate(m1));
}

/**
 * Test case to check whether it's possible to simplify a given Matrix
 */
TEST_F(DiagonalStrategyTests, simplify_empty) {
    /* Execute method and check whether the return value is true or not
     * Should return false as the simplification function isn't implemented yet */
    ASSERT_FALSE(diagonalStrategy->simplify(m1));
}