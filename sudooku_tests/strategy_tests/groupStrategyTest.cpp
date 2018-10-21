//
// Created by Borbély László on 2018. 10. 21..
//

#include <strategies/groupStrategy.h>
#include "gtest/gtest.h"

class GroupStrategyTests : public ::testing::Test {
protected:
    GroupStrategy groupStrategy;
    Matrix m1;

    void SetUp() override {
        std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap = {
                {{1, 1}, 1},
                {{1, 2}, 2},
                {{2, 1}, 3},
        };
        std::vector<unsigned short int> p1 = {1, 2, 3};

        m1 = Matrix{4, inputMap};
        m1[{1, 3}].setPossibleValues(p1);
        m1[{1, 4}].setPossibleValues(p1);
        m1[{2, 3}].setPossibleValues(p1);
    }
};

TEST_F(GroupStrategyTests, validation_check_false) {
    std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap = {
            {{1, 1}, 9},
            {{2, 2}, 9}
    };
    Matrix matrix = Matrix{9, inputMap};

    ASSERT_FALSE(groupStrategy.validate(matrix));
}

TEST_F(GroupStrategyTests, validation_check_true) {
    ASSERT_TRUE(groupStrategy.validate(m1));
}

TEST_F(GroupStrategyTests, simplify_trivial) {
    groupStrategy.simplify(m1);

    auto values = m1[{2, 2}].getPossibleValues();
    ASSERT_EQ(1, values.size());
    ASSERT_EQ(4, values[0]);
}

TEST_F(GroupStrategyTests, simplify_advanced) {
    groupStrategy.simplify(m1);

    auto values = m1[{2, 4}].getPossibleValues();
    ASSERT_EQ(1, values.size());
    ASSERT_EQ(4, values[0]);
}