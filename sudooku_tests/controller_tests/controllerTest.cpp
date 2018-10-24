//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sudookuController.h>
#include <controller_tests/helper_classes/mockInputHandler.h>
#include <controller_tests/helper_classes/mockOutputHandler.h>

using ::testing::AtLeast;

class ControllerTests : public ::testing::Test {
protected:
    SudookuController *sudookuController = nullptr;
    MockInputHandler mockInputHandler{};
    MockOutputHandler mockOutputHandler;

    void SetUp() override {
        sudookuController = new SudookuController{&mockInputHandler, nullptr};
    }

    void TearDown() override {
        delete sudookuController;
    }
};

TEST_F(ControllerTests, input_called_only_once_test) {
    EXPECT_CALL(mockInputHandler, readInput())
            .Times(1);
}

TEST_F(ControllerTests, output_handler_start_test) {
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::RUN_START, testing::_))
            .Times(1);
}

TEST_F(ControllerTests, output_handler_solution_test) {
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::SOLUTION, testing::_))
            .Times(AtLeast(1));
}

TEST_F(ControllerTests, output_handler_end_test) {
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::RUN_END, testing::_))
            .Times(1);
}