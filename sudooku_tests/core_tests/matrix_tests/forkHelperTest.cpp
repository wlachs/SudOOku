//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>

class ForkHelperTests : public ::testing::Test {
protected:
    Matrix m1;
    ForkHelper *forkHelper{};

    void SetUp() override {
        m1 = FileInputHandler{{false}, "small4.mat"}.readInput();
        m1[{4, 4}].removeValue(4);
        forkHelper = new ForkHelper{&m1};
    }

    void TearDown() override {
        delete forkHelper;
    }
};

TEST_F(ForkHelperTests, fork_test) {
    auto m2 = forkHelper->fork();

    auto val1 = m1[{4, 4}].getPossibleValues();
    auto val2 = m2[{4, 4}].getPossibleValues();

    ASSERT_EQ(1, val1.size());
    ASSERT_EQ(2, val2.size());
    EXPECT_EQ(1, val1[0]);
    EXPECT_EQ(2, val2[0]);
    EXPECT_EQ(3, val2[1]);
}