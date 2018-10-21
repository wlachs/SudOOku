//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <matrix/field.h>
#include <vector>

class FieldTests : public ::testing::Test {
protected:
    Field f1;

    void SetUp() override {
        std::vector<unsigned short int> possibleValues = {1, 2, 3, 4};
        f1 = Field{possibleValues};
    }
};

TEST_F(FieldTests, getter_test) {
    auto values = f1.getPossibleValues();

    ASSERT_EQ(4, values.size());

    for (unsigned short int i = 0; i < 4; ++i) {
        EXPECT_EQ(i + 1, values[i]);
    }
}

TEST_F(FieldTests, fixvalue_noarg_test) {
    f1.fixValue();

    ASSERT_EQ(1, f1.getPossibleValues().size());
    ASSERT_EQ(1, f1.getPossibleValues()[0]);
}

TEST_F(FieldTests, fixvalue_witharg_test) {
    f1.fixValue(3);

    ASSERT_EQ(1, f1.getPossibleValues().size());
    ASSERT_EQ(3, f1.getPossibleValues()[0]);
}

TEST_F(FieldTests, removevalue_noarg_test) {
    f1.removeValue();
    auto values = f1.getPossibleValues();

    ASSERT_EQ(3, values.size());

    for (unsigned short int i = 0; i < 3; ++i) {
        EXPECT_EQ(i + 2, values[i]);
    }
}

TEST_F(FieldTests, removevalue_witharg_test) {
    f1.removeValue(4);

    auto values = f1.getPossibleValues();

    ASSERT_EQ(3, values.size());

    for (unsigned short int i = 0; i < 3; ++i) {
        EXPECT_EQ(i + 1, values[i]);
    }
}

TEST_F(FieldTests, contains_test) {
    ASSERT_EQ(4, f1.getPossibleValues().size());

    for (unsigned short int i = 1; i <= 4; ++i) {
        EXPECT_TRUE(f1.contains(i));
    }
}