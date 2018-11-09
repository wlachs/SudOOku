//
// Created by Borbély László on 2018. 10. 25..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sudooku_controller/handlers/output_handlers/outputHandler.h>
#include <sudooku_controller/handlers/output_handlers/fileOutputHandler.h>
#include <sudooku_controller/handlers/input_handlers/fileInputHandler.h>
#include <sudooku_controller/exceptions/noMatrixProvidedException.h>
#include <sudooku_controller/exceptions/wrongEventTypeException.h>

/**
 * FileOutputHandler test fixture class
 */
class FileOutputHandlerTests : public ::testing::Test {
protected:
    OutputHandler *outputHandler{};

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Initialize FikeOutoutHandler object */
        outputHandler = new FileOutputHandler{"solution1.mat"};
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Free OutputHandler object to prevent memory leak */
        delete outputHandler;
    }
};

/**
 * Test case to check whether Matrix is sent to the OutputHandler
 */
TEST_F(FileOutputHandlerTests, matrix_write_test) {
    /* Initialize Matrix object with only one fixed value */
    Matrix matrix1{9, {{{1, 1}, Field{1}}}};

    /* Notify OutputHandler of execution start */
    outputHandler->notifyEvent(SudookuEvent::RUN_START, nullptr);

    /* Notify OutputHandler of solution found */
    outputHandler->notifyEvent(SudookuEvent::SOLUTION, &matrix1);

    /* Notify OutputHandler of execution end */
    outputHandler->notifyEvent(SudookuEvent::RUN_END, nullptr);
}

/**
 * Test case to check whether it's possible to write an undefined Matrix to the output
 */
TEST_F(FileOutputHandlerTests, matrix_write_invalid_test) {
    /* Try sending a solution notification with a nullpointer */
    try {
        outputHandler->notifyEvent(SudookuEvent::SOLUTION, nullptr);

        /* If the execution reaches this point, the test failed */
        FAIL() << "An exception of type NoMatrixProvidedException should have been thrown!";
    }

        /* A specific exception should be thrown in this case */
    catch (NoMatrixProvidedException &e) {
        EXPECT_EQ(std::string{"No matrix provided to notify function!"}, e.what());
    }

        /* If for some reason another exception is thrown, the test should fail */
    catch (...) {
        FAIL() << "expected NoMatrixProvidedException";
    }
}

/**
 * Test case to check whether it's possible to send a notification with an incorrect event type
 */
TEST_F(FileOutputHandlerTests, invalid_event_test) {
    /* Try sending a notification with the event type of '-1' */
    try {
        outputHandler->notifyEvent(static_cast<SudookuEvent>(-1), nullptr);

        /* If the execution reaches this point, the test failed */
        FAIL() << "An exception of type WrongEventTypeException should have been thrown!";
    }

        /* A specific exception should be thrown in this case */
    catch (WrongEventTypeException &e) {
        EXPECT_EQ(std::string{"Undefined SudookuEvent!"}, e.what());
    }

        /* If for some reason another exception is thrown, the test should fail */
    catch (...) {
        FAIL() << "expected WrongEventTypeException";
    }
}