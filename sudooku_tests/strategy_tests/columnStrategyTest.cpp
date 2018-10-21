//
// Created by Borbély László on 2018. 10. 16..
//

#include <strategies/columnStrategy.h>
#include "gtest/gtest.h"

class ColumnStrategyTests : public ::testing::Test {
protected:
    ColumnStrategy columnStrategy;
    Matrix m1;

    void SetUp() override {
        std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap = {
                {{1, 1}, 1},
                {{2, 1}, 2},
                {{3, 1}, 3},
        };
        std::vector<unsigned short int> p1 = {1, 2, 3};

        m1 = Matrix{4, inputMap};
        m1[{1, 2}].setPossibleValues(p1);
        m1[{2, 2}].setPossibleValues(p1);
        m1[{3, 2}].setPossibleValues(p1);
    }
};

TEST_F(ColumnStrategyTests, validation_check_false) {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap = {
            {{1, 1}, 9},
            {{2, 1}, 9}
    };
    Matrix matrix = Matrix{9, inputMap};

    ASSERT_FALSE(columnStrategy.validate(matrix));
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