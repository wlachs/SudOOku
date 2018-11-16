//
// Created by Borbély László on 2018. 10. 21..
//

#include <sudooku_core/strategies/rowStrategy.h>
#include <sudooku_core/strategies/columnStrategy.h>
#include <sudooku_core/strategies/groupStrategy.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include "gtest/gtest.h"

/**
 * GroupStrategy test fixture class
 */
class GroupStrategyTests : public ::testing::Test {
protected:
    GroupStrategy groupStrategy;
    Matrix m1;
    std::vector<SolvingStrategy *> solvingStrategies = {new RowStrategy{}, new ColumnStrategy{}, new GroupStrategy{}};

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Initialize input Matrix */
        m1 = FileInputHandler{solvingStrategies, "small3.mat"}.readInput();

        /* Remove some values to test group strategy functionality */
        m1[{1, 3}].removeValue(4);
        m1[{1, 4}].removeValue(4);
        m1[{2, 3}].removeValue(4);
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Deallocate SolvingStrategy pointers */
        for (SolvingStrategy *solvingStrategy : solvingStrategies) {
            /* Delete object */
            delete solvingStrategy;
        }
    }
};

/**
 * Test case to check whether a Matrix is valid or not
 */
TEST_F(GroupStrategyTests, validation_check_false) {
    /* Initialize input Matrix */
    Matrix invalid = FileInputHandler{solvingStrategies, "invalid3.mat"}.readInput();

    /* Check validity
     * Should return false */
    ASSERT_FALSE(groupStrategy.validate(invalid));
}

/**
 * Test case to check whether a Matrix is valid or not
 * This case should return true
 */
TEST_F(GroupStrategyTests, validation_check_true) {
    /* Check validity
     * Should return true */
    ASSERT_TRUE(groupStrategy.validate(m1));
}

/**
 * Test case to check whether it's possible to simplify a given Matrix
 */
TEST_F(GroupStrategyTests, simplify_trivial) {
    /* Execute method */
    groupStrategy.simplify(m1);

    /* Retrieve possible values */
    auto const &values = m1[{2, 2}].getPossibleValues();

    /* The simplified vector should have a length of 1 */
    ASSERT_EQ(1, values.size());

    /* The value should equal 4 */
    ASSERT_EQ(4, values[0]);
}

/**
 * Test case to check whether unique simplification also works
 */
TEST_F(GroupStrategyTests, simplify_advanced) {
    /* Execute method */
    groupStrategy.simplify(m1);

    /* Retrieve possible values */
    auto const &values = m1[{2, 4}].getPossibleValues();

    /* The simplified vector should have a length of 1 */
    ASSERT_EQ(1, values.size());

    /* The value should equal 4 */
    ASSERT_EQ(4, values[0]);
}