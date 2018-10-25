//
// Created by Borbély László on 2018. 10. 25..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <handlers/output_handlers/outputHandler.h>
#include <handlers/output_handlers/fileOutputHandler.h>
#include <handlers/input_handlers/fileInputHandler.h>

class FileOutputHandlerTests : public ::testing::Test {
protected:
    OutputHandler *outputHandler{};

    void SetUp() override {
        outputHandler = new FileOutputHandler{"solution1.mat"};
    }

    void TearDown() override {
        delete outputHandler;
    }
};

TEST_F(FileOutputHandlerTests, matrix_write_test) {
    Matrix matrix1{9, {{{1, 1}, Field{1}}}};

    outputHandler->notifyEvent(SudookuEvent::RUN_START, nullptr);
    outputHandler->notifyEvent(SudookuEvent::SOLUTION, &matrix1);
    outputHandler->notifyEvent(SudookuEvent::RUN_END, nullptr);
}