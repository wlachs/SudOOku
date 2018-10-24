//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sudookuController.h>
#include <controller_tests/helper_classes/mockInputHandler.h>

class ControllerTests : public ::testing::Test {
protected:
    SudookuController *sudookuController = nullptr;
    MockInputHandler mockInputHandler{};

    void SetUp() override {
        sudookuController = new SudookuController{&mockInputHandler, nullptr};
    }

    void TearDown() override {
        delete sudookuController;
    }
};

TEST_F(ControllerTests, input_called_only_once_test) {
    EXPECT_CALL(mockInputHandler, readInput()).Times(1);
}