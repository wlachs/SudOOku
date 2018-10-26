//
// Created by Borbély László on 2018. 10. 21..
//

#include <strategies/diagonalStrategy.h>
#include <matrix/matrixReader.h>
#include "gtest/gtest.h"

class DiagonalStrategyTests : public ::testing::Test {
protected:
    SolvingStrategy *diagonalStrategy = nullptr;
    Matrix m1;

    void SetUp() override {
        diagonalStrategy = new DiagonalStrategy{};
        m1 = static_cast<Matrix>(MatrixReader{"small4.mat"});

        m1[{1, 1}].removeValue(4);
        m1[{2, 2}].removeValue(4);
        m1[{3, 3}].removeValue(4);
    }

    void TearDown() override {
        delete diagonalStrategy;
    }
};

TEST_F(DiagonalStrategyTests, validation_check_false_1) {
    Matrix invalid = static_cast<Matrix>(MatrixReader{"invalid4.mat"});
    ASSERT_FALSE(diagonalStrategy->validate(invalid));
}

TEST_F(DiagonalStrategyTests, validation_check_false_2) {
    Matrix invalid = static_cast<Matrix>(MatrixReader{"invalid5.mat"});
    ASSERT_FALSE(diagonalStrategy->validate(invalid));
}

TEST_F(DiagonalStrategyTests, validation_check_true) {
    ASSERT_TRUE(diagonalStrategy->validate(m1));
}

TEST_F(DiagonalStrategyTests, simplify_empty) {
    ASSERT_FALSE(diagonalStrategy->simplify(m1));
}