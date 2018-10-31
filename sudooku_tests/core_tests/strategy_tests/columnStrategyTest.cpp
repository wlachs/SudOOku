//
// Created by Borbély László on 2018. 10. 16..
//

#include <sudooku_core/strategies/columnStrategy.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include <sudooku_core/matrix/matrix.h>
#include "gtest/gtest.h"

/**
 * ColumnStrategy test fixture class
 */
class ColumnStrategyTests : public ::testing::Test {
protected:
    ColumnStrategy columnStrategy;
    Matrix m1;

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Initialize input Matrix */
        m1 = FileInputHandler{{false}, "small1.mat"}.readInput();

        /* Remove some values to test column strategy functionality */
        m1[{1, 2}].removeValue(4);
        m1[{2, 2}].removeValue(4);
        m1[{3, 2}].removeValue(4);
    }
};

/**
 * Test case to check whether a Matrix is valid or not
 * This case should return false as the input Matrix has multiple times the same values in column
 */
TEST_F(ColumnStrategyTests, validation_check_false) {
    /* Initialize input Matrix */
    Matrix invalid = FileInputHandler{{false}, "invalid1.mat"}.readInput();

    /* Check validity
     * Should return false */
    ASSERT_FALSE(columnStrategy.validate(invalid));
}

/**
 * Test case to check whether a Matrix is valid or not
 * This case should return true
 */
TEST_F(ColumnStrategyTests, validation_check_true) {
    /* Check validity
     * Should return true */
    ASSERT_TRUE(columnStrategy.validate(m1));
}

/**
 * Test case to check whether it's possible to simplify a given Matrix
 */
TEST_F(ColumnStrategyTests, simplify_trivial) {
    /* Execute method */
    columnStrategy.simplify(m1);

    /* Retrieve possible values */
    auto &values = m1[{4, 1}].getPossibleValues();

    /* The simplified vector should have a length of 1 */
    ASSERT_EQ(1, values.size());

    /* The value should equal 4 */
    ASSERT_EQ(4, values[0]);
}

/**
 * Test case to check whether unique simplification also works
 */
TEST_F(ColumnStrategyTests, simplify_advanced) {
    /* Execute method */
    columnStrategy.simplify(m1);

    /* Retrieve possible values */
    auto &values = m1[{4, 2}].getPossibleValues();

    /* The simplified vector should have a length of 1 */
    ASSERT_EQ(1, values.size());

    /* The value should equal 4 */
    ASSERT_EQ(4, values[0]);
}