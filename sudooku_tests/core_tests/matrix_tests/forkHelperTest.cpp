//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include <sudooku_core/strategies/rowStrategy.h>
#include <sudooku_core/strategies/columnStrategy.h>
#include <sudooku_core/strategies/groupStrategy.h>

/**
 * ForkHelper test fixture class
 */
class ForkHelperTests : public ::testing::Test {
protected:
    Matrix m1;
    ForkHelper *forkHelper{};
    std::vector<SolvingStrategy *> solvingStrategies = {new RowStrategy{}, new ColumnStrategy{}, new GroupStrategy{}};

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Read input Matrix from file */
        m1 = FileInputHandler{solvingStrategies, "small4.mat"}.readInput();

        /* Remove one value so that the ForkHelper class chooses that value as the optimal forking Field */
        m1[{4, 4}].removeValue(4);

        /* Construct ForkHelper object */
        forkHelper = new ForkHelper{&m1};
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Free ForkHelper object to prevent memory leak */
        delete forkHelper;

        /* Deallocate SolvingStrategy pointers */
        for (SolvingStrategy *solvingStrategy : solvingStrategies) {
            /* Delete object */
            delete solvingStrategy;
        }
    }
};

/**
 * Test case for the fork() fuction of the ForkHelper class
 */
TEST_F(ForkHelperTests, fork_test) {
    /* Execute function */
    auto const m2 = forkHelper->fork();

    /* Retrieve possible values of the initial Matrix */
    auto const &val1 = m1[{4, 4}].getPossibleValues();

    /* Retrieve possible values of the new Matrix */
    auto const &val2 = m2[{4, 4}].getPossibleValues();

    /* The vector length of the initial Matrix should be equal to 1
     * It was 3 initially but the first one got fixed by the ForkHelper */
    ASSERT_EQ(1, val1.size());

    /* The vector length of the new Matrix should be equal to 2
     * It was 3 initially but the first one got removed by the ForkHelper */
    ASSERT_EQ(2, val2.size());

    /* Check the value of the first Field */
    EXPECT_EQ(1, val1[0]);

    /* Check the values of the new Field */
    EXPECT_EQ(2, val2[0]);
    EXPECT_EQ(3, val2[1]);
}