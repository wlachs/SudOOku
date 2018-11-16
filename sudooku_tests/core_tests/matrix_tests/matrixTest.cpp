//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <sudooku_core/matrix/matrix.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include <sudooku_core/strategies/rowStrategy.h>
#include <sudooku_core/strategies/columnStrategy.h>
#include <sudooku_core/strategies/groupStrategy.h>

/**
 * Matrix test fixture class
 */
class MatrixTests : public ::testing::Test {
protected:
    Matrix m1;
    std::vector<SolvingStrategy *> solvingStrategies = {new RowStrategy{}, new ColumnStrategy{}, new GroupStrategy{}};

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Read input Matrix from file */
        m1 = FileInputHandler{solvingStrategies, "small4.mat"}.readInput();
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
 * Test case for the getDimension() function
 */
TEST_F(MatrixTests, getDimension_test) {
    /* Should return 4 as the dimension of the Matrix read from file is 4 too */
    ASSERT_EQ(4, m1.getDimension());
}

/**
 * Test case for the const operator[] of the Matrix class
 */
TEST_F(MatrixTests, const_operator_test) {
    /* Initialize a const reference to the Matrix constructed in the SetUp() method */
    Matrix const &m_const = m1;

    /* This way the operator[] should invoke the const operator[] function instead of the non constant one */
    Field const &field = m_const[{1, 1}];

    /* Get possible values of the Field */
    auto const &possibleValues = field.getPossibleValues();

    /* The vector of Field values should have the length of 4 */
    ASSERT_EQ(4, possibleValues.size());

    /* The values should match the values read from the input file */
    for (unsigned short int i = 0; i < 4; ++i) {
        EXPECT_TRUE(field.contains(i + 1));
    }
}

/**
 * Test case for the non const operator[] of the Matrix class
 */
TEST_F(MatrixTests, operator_test) {
    /* This time the operator[] should invoke the non const operator[] function instead of the constant one */
    Field const &field = m1[{1, 1}];

    /* Get possible values of the Field */
    auto const &possibleValues = field.getPossibleValues();

    /* The vector of Field values should have the length of 4 */
    ASSERT_EQ(4, possibleValues.size());

    /* The values should match the values read from the input file */
    for (unsigned short int i = 0; i < 4; ++i) {
        EXPECT_TRUE(field.contains(i + 1));
    }
}

/**
 * Test case for the fork() function of the Matrix class
 */
TEST_F(MatrixTests, fork_test) {
    /* Execute function */
    auto m2 = m1.forkFirstReturnSecond();

    /* On the initial Matrix the fixValue() method should be invoked thus returning a vector with the length 1 */
    auto forkedList1 = m1[{1, 1}].getPossibleValues();
    EXPECT_EQ(1, forkedList1.size());

    /* On the new Matrix the removeValue() method should be invoked thus returning a vector with the length 3 */
    auto forkedList2 = m2[{1, 1}].getPossibleValues();
    EXPECT_EQ(3, forkedList2.size());
}

/**
 * Test case for the equality operator of the Matrix class
 */
TEST_F(MatrixTests, equality_operator_true_check) {
    /* Read the initial Matrix again */
    Matrix m11 = FileInputHandler{solvingStrategies, "small4.mat"}.readInput();

    /* Since the two sources are the same, the Matrixes should be equal too */
    EXPECT_EQ(m1, m11);
}

/**
 * Test case for the equality operator of the Matrix class
 * This time the function should return false
 */
TEST_F(MatrixTests, equality_operator_false_check) {
    /* Read another Matrix from file */
    Matrix m2 = FileInputHandler{solvingStrategies, "small3.mat"}.readInput();

    /* Since the two read Matrices were different, the operator should return false */
    EXPECT_NE(m1, m2);
}

/**
 * Test case for the equality operator of the Matrix class
 * This time even the dimensions of the two Matrices are different
 */
TEST_F(MatrixTests, equality_operator_dimension_false_check) {
    /* Read another Matrix from file */
    Matrix m2 = FileInputHandler{solvingStrategies, "small3.mat"}.readInput();

    /* Even the dimensions don't match, so the function should return false before starting to check each
     * value individually */
    EXPECT_NE(m1, m2);
}