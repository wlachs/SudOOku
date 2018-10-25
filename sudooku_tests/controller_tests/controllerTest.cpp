//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sudookuController.h>
#include <controller_tests/helper_classes/mockInputHandler.h>
#include <controller_tests/helper_classes/mockOutputHandler.h>
#include <strategies/groupStrategy.h>
#include <handlers/input_handlers/fileInputHandler.h>

using ::testing::AtLeast;
using ::testing::Return;

class ControllerTests : public ::testing::Test {
protected:
    Solver solver;
    SudookuController *sudookuController = nullptr;
    MockInputHandler mockInputHandler{};
    MockOutputHandler mockOutputHandler{};
    std::vector<SolvingStrategy *> rules = {};

    void SetUp() override {
        sudookuController = new SudookuController{&mockInputHandler, &mockOutputHandler, &solver};

        rules = {new GroupStrategy{}};
    }

    void TearDown() override {
        delete sudookuController;
    }
};

TEST_F(ControllerTests, input_called_only_once_test) {
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));
    EXPECT_CALL(mockInputHandler, readInput())
            .Times(1);

    sudookuController->run();
}

TEST_F(ControllerTests, output_handler_start_test) {
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::RUN_START, testing::_))
            .Times(1);

    sudookuController->run();
}

TEST_F(ControllerTests, output_handler_solution_test) {
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::SOLUTION, testing::_))
            .Times(AtLeast(1));

    sudookuController->run();
}

TEST_F(ControllerTests, output_handler_end_test) {
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::RUN_END, testing::_))
            .Times(1);

    sudookuController->run();
}

TEST_F(ControllerTests, real_solve_test) {
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::SOLUTION, testing::_))
            .Times(4);

    FileInputHandler f{"test3.mat"};
    SudookuController c{&f, &mockOutputHandler, &solver};

    c.run();
}