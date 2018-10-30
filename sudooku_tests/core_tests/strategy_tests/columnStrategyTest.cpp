//
// Created by Borbély László on 2018. 10. 16..
//

#include <strategies/columnStrategy.h>
#include <handlers/input_handlers/fileInputHandler.h>
#include "gtest/gtest.h"

class ColumnStrategyTests : public ::testing::Test {
protected:
    ColumnStrategy columnStrategy;
    Matrix m1;

    void SetUp() override {
        m1 = FileInputHandler{{false}, "small1.mat"}.readInput();

        m1[{1, 2}].removeValue(4);
        m1[{2, 2}].removeValue(4);
        m1[{3, 2}].removeValue(4);
    }
};

TEST_F(ColumnStrategyTests, validation_check_false) {
    Matrix invalid = FileInputHandler{{false}, "invalid1.mat"}.readInput();
    ASSERT_FALSE(columnStrategy.validate(invalid));
}

TEST_F(ColumnStrategyTests, validation_check_true) {
    ASSERT_TRUE(columnStrategy.validate(m1));
}

TEST_F(ColumnStrategyTests, simplify_trivial) {
    columnStrategy.simplify(m1);

    auto values = m1[{4, 1}].getPossibleValues();
    ASSERT_EQ(1, values.size());
    ASSERT_EQ(4, values[0]);
}

TEST_F(ColumnStrategyTests, simplify_advanced) {
    columnStrategy.simplify(m1);

    auto values = m1[{4, 2}].getPossibleValues();
    ASSERT_EQ(1, values.size());
    ASSERT_EQ(4, values[0]);
}