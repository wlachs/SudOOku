//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <matrix/matrix.h>
#include <matrix/matrixReader.h>

class MatrixTests : public ::testing::Test {
protected:
    Matrix m1;

    void SetUp() override {
        m1 = static_cast<Matrix>(MatrixReader{"small4.mat"});
    }
};

TEST_F(MatrixTests, getDimension_test) {
    ASSERT_EQ(4, m1.getDimension());
}

TEST_F(MatrixTests, const_operator_test) {
    Matrix const &m_const = m1;
    Field const &field = m_const[{1, 1}];
    auto const &possibleValues = field.getPossibleValues();

    ASSERT_EQ(4, possibleValues.size());
    for (unsigned short int i = 0; i < 4; ++i) {
        EXPECT_TRUE(field.contains(i + 1));
    }
}

TEST_F(MatrixTests, operator_test) {
    Field const &field = m1[{1, 1}];
    auto const &possibleValues = field.getPossibleValues();

    ASSERT_EQ(4, possibleValues.size());
    for (unsigned short int i = 0; i < 4; ++i) {
        EXPECT_TRUE(field.contains(i + 1));
    }
}

TEST_F(MatrixTests, fork_test) {
    auto m2 = m1.forkFirstReturnSecond();
    auto forkedList1 = m1[{1, 1}].getPossibleValues();
    auto forkedList2 = m2[{1, 1}].getPossibleValues();

    EXPECT_EQ(1, forkedList1.size());
    EXPECT_EQ(3, forkedList2.size());
}

TEST_F(MatrixTests, equality_operator_true_check) {
    Matrix m11 = static_cast<Matrix>(MatrixReader{"small4.mat"});

    EXPECT_EQ(m1, m11);
}

TEST_F(MatrixTests, equality_operator_false_check) {
    Matrix m2 = static_cast<Matrix>(MatrixReader{"small3.mat"});

    EXPECT_NE(m1, m2);
}

TEST_F(MatrixTests, equality_operator_dimension_false_check) {
    Matrix m2 = static_cast<Matrix>(MatrixReader{"test3.mat"});

    EXPECT_NE(m1, m2);
}