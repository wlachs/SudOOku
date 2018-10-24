//
// Created by Borbély László on 2018. 10. 21..
//

#include <strategies/groupStrategy.h>
#include <matrix/matrixReader.h>
#include "gtest/gtest.h"

class GroupStrategyTests : public ::testing::Test {
protected:
    GroupStrategy groupStrategy;
    Matrix m1;

    void SetUp() override {
        m1 = (Matrix) MatrixReader{"small3.mat"};

        m1[{1, 3}].removeValue(4);
        m1[{1, 4}].removeValue(4);
        m1[{2, 3}].removeValue(4);
    }
};

TEST_F(GroupStrategyTests, validation_check_false) {
    Matrix invalid = (Matrix) MatrixReader{"invalid3.mat"};

    ASSERT_FALSE(groupStrategy.validate(invalid));
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