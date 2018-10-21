//
// Created by Borbély László on 2018. 10. 21..
//

#include <strategies/rowStrategy.h>
#include "gtest/gtest.h"

class RowStrategyTests : public ::testing::Test {
protected:
    RowStrategy rowStrategy;
    Matrix m1;

    void SetUp() override {
        std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap = {
                {{1, 1}, 1},
                {{1, 2}, 2},
                {{1, 3}, 3},
        };
        std::vector<unsigned short int> p1 = {1, 2, 3};

        m1 = Matrix{4, inputMap};
        m1[{2, 1}].setPossibleValues(p1);
        m1[{2, 2}].setPossibleValues(p1);
        m1[{2, 3}].setPossibleValues(p1);
    }
};

TEST_F(RowStrategyTests, validation_check_false) {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap = {
            {{1, 1}, 9},
            {{1, 2}, 9}
    };
    Matrix matrix = Matrix{9, inputMap};

    ASSERT_FALSE(rowStrategy.validate(matrix));
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