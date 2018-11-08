//
// Created by Borbély László on 2018. 10. 21..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sudooku_controller/sudookuController.h>
#include <controller_tests/helper_classes/mockInputHandler.h>
#include <controller_tests/helper_classes/mockOutputHandler.h>
#include <sudooku_core/strategies/groupStrategy.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>

using ::testing::AtLeast;
using ::testing::Return;

/**
 * Controller test fixture class
 */
class ControllerTests : public ::testing::Test {
protected:
    /* Object used for all test cases */
    Solver solver;
    SudookuController *sudookuController = nullptr;
    MockInputHandler mockInputHandler{};
    MockOutputHandler mockOutputHandler{};
    std::vector<SolvingStrategy *> rules = {};

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Initialize controller object */
        sudookuController = new SudookuController{&mockInputHandler, &mockOutputHandler, &solver};

        /* Add a sample rule to the list of rules
         * Note that this pointer doesn't have to be freed because the controller does it instead */
        rules = {new GroupStrategy{}};
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Free controller object to prevent memory leak */
        delete sudookuController;
    }
};

/**
 * Test case for checking whether the InputHandler has only been called once
 */
TEST_F(ControllerTests, input_called_only_once_test) {
    /* The rules should be called once, because the pointers inside must be freed by the controller */
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));

    /* Controller will check whether there are any puzzles to solve */
    EXPECT_CALL(mockInputHandler, hasInput())
            .WillOnce(Return(true))
            .WillOnce(Return(false));

    /* The input should also only be read once since there is only one Matrix puzzle being solved */
    EXPECT_CALL(mockInputHandler, readInput())
            .WillOnce(Return(Matrix{1, {{{1, 1}, Field{1}}}}));

    /* Execute method */
    sudookuController->run();
}

/**
 * Test case for the OutputHandler object
 * It should be called when the execution starts
 */
TEST_F(ControllerTests, output_handler_start_test) {
    /* The InputHandler should be called once again for the rules */
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));

    /* Controller will check whether there are any puzzles to solve */
    EXPECT_CALL(mockInputHandler, hasInput())
            .WillOnce(Return(true))
            .WillOnce(Return(false));

    /* The input should also only be read once since there is only one Matrix puzzle being solved */
    EXPECT_CALL(mockInputHandler, readInput())
            .WillOnce(Return(Matrix{1, {{{1, 1}, Field{1}}}}));

    /* The OutputHandler can be called with any kind of parameters */
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));

    /* But with the RUN_START parameter, exactly once */
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::RUN_START, testing::_))
            .Times(1);

    /* Execute method */
    sudookuController->run();
}

/**
 * Test case for checking whether the solutions of a puzzle are also passed to the OutputHandler object
 */
TEST_F(ControllerTests, output_handler_solution_test) {
    /* The InputHandler should return the rules for solving the puzzle */
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));

    /* Controller will check whether there are any puzzles to solve */
    EXPECT_CALL(mockInputHandler, hasInput())
            .WillOnce(Return(true))
            .WillOnce(Return(false));

    /* The input should also only be read once since there is only one Matrix puzzle being solved */
    EXPECT_CALL(mockInputHandler, readInput())
            .WillOnce(Return(Matrix{1, {{{1, 1}, Field{1}}}}));

    /* The OutputHandler can be called with any kind of parameters */
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));

    /* But with the SOLUTION parameter, at least once
     * Note that this is not always the case. An unsolvable puzzle won't return anything */
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::SOLUTION, testing::_))
            .Times(AtLeast(1));

    /* Execute method */
    sudookuController->run();
}

/**
 * Test case for checking whether the OutputHandler gets notified of the end of execution
 */
TEST_F(ControllerTests, output_handler_end_test) {
    /* The InputHandler should return the rules for solving the puzzle */
    EXPECT_CALL(mockInputHandler, readRules())
            .WillOnce(Return(rules));

    /* Controller will check whether there are any puzzles to solve */
    EXPECT_CALL(mockInputHandler, hasInput())
            .WillOnce(Return(true))
            .WillOnce(Return(false));

    /* The input should also only be read once since there is only one Matrix puzzle being solved */
    EXPECT_CALL(mockInputHandler, readInput())
            .WillOnce(Return(Matrix{1, {{{1, 1}, Field{1}}}}));

    /* The OutputHandler can be called with any kind of parameters */
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));

    /* But with the RUN_END parameter, exactly once */
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::RUN_END, testing::_))
            .Times(1);

    /* Execute method */
    sudookuController->run();
}

/**
 * Test case for checking the behavior in a real life situation
 */
TEST_F(ControllerTests, real_solve_test) {
    /* The OutputHandler can be called with any kind of parameters */
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));

    /* But with the SOLUTION parameter, exactly 4 times */
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::SOLUTION, testing::_))
            .Times(4);

    /* Initialize a real instance of the InputHandler */
    FileInputHandler f{{false}, "test3.mat"};

    /* Initialize a real instance of the controller with the matching pointers */
    SudookuController c{&f, &mockOutputHandler, &solver};

    /* Execute method */
    c.run();
}

/**
 * Test case for checking whether the controller is also able to solve puzzles with a diagonal strategy flag enabled
 */
TEST_F(ControllerTests, real_solve_diagonal_test) {
    /* The OutputHandler can be called with any kind of parameters */
    EXPECT_CALL(mockOutputHandler, notifyEvent(testing::_, testing::_))
            .Times(AtLeast(0));

    /* But with the SOLUTION parameter, exactly once */
    EXPECT_CALL(mockOutputHandler, notifyEvent(SudookuEvent::SOLUTION, testing::_))
            .Times(1);

    /* Initialize a real instance of the InputHandler */
    FileInputHandler f{{true}, "test5.mat"};

    /* Initialize a real instance of the controller with the matching pointers */
    SudookuController c{&f, &mockOutputHandler, &solver};

    /* Execute method */
    c.run();
}