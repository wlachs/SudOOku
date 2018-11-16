//
// Created by Borbély László on 2018. 10. 25..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include <sudooku_core/strategies/rowStrategy.h>
#include <sudooku_core/strategies/columnStrategy.h>
#include <sudooku_core/strategies/groupStrategy.h>

/**
 * FileInputHandler test fixture class
 */
class FileInputHandlerTests : public ::testing::Test {
protected:
    InputHandler *inputHandler{};
    std::vector<SolvingStrategy *> solvingStrategies = {new RowStrategy{}, new ColumnStrategy{}, new GroupStrategy{}};

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Initialize FileInputHandler object */
        inputHandler = new FileInputHandler{solvingStrategies, "small1.mat"};
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Free InputHandler object to prevent memory leak */
        delete inputHandler;

        /* Deallocate SolvingStrategy pointers */
        for (SolvingStrategy *solvingStrategy : solvingStrategies) {
            /* Delete object */
            delete solvingStrategy;
        }
    }
};

/**
 * Test case to check whether the object is able to read a Matrix from the input
 */
TEST_F(FileInputHandlerTests, matrix_read_test) {
    /* Reading input file */
    auto m1 = inputHandler->readInput();

    /* Construct matching local Matrix */
    Matrix m2{4, {
            {{1, 1}, Field{1}},
            {{2, 1}, Field{2}},
            {{3, 1}, Field{3}},
    }};

    /* Compare the two Matrices */
    ASSERT_EQ(m1, m2);
}