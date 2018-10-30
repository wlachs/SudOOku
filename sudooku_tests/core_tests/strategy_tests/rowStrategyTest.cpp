//
// Created by Borbély László on 2018. 10. 21..
//

#include <sudooku_core/strategies/rowStrategy.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include "gtest/gtest.h"

class RowStrategyTests : public ::testing::Test {
protected:
    RowStrategy rowStrategy;
    Matrix m1;

    void SetUp() override {
        m1 = FileInputHandler{{false}, "small2.mat"}.readInput();

        m1[{2, 1}].removeValue(4);
        m1[{2, 2}].removeValue(4);
        m1[{2, 3}].removeValue(4);
    }
};

TEST_F(RowStrategyTests, validation_check_false) {
    Matrix invalid = FileInputHandler{{false}, "invalid2.mat"}.readInput();

    ASSERT_FALSE(rowStrategy.validate(invalid));
}

TEST_F(RowStrategyTests, validation_check_true) {
    ASSERT_TRUE(rowStrategy.validate(m1));
}

TEST_F(RowStrategyTests, simplify_trivial) {
    rowStrategy.simplify(m1);

    auto values = m1[{1, 4}].getPossibleValues();
    ASSERT_EQ(1, values.size());
    ASSERT_EQ(4, values[0]);
}

TEST_F(RowStrategyTests, simplify_advanced) {
    rowStrategy.simplify(m1);

    auto values = m1[{2, 4}].getPossibleValues();
    ASSERT_EQ(1, values.size());
    ASSERT_EQ(4, values[0]);
}