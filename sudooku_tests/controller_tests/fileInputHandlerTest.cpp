//
// Created by Borbély László on 2018. 10. 25..
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <handlers/input_handlers/fileInputHandler.h>

class FileInputHandlerTests : public ::testing::Test {
protected:
    InputHandler *inputHandler{};

    void SetUp() override {
        inputHandler = new FileInputHandler{{false}, "test1.mat"};
    }

    void TearDown() override {
        delete inputHandler;
    }
};

TEST_F(FileInputHandlerTests, matrix_read_test) {
    auto matrix = inputHandler->readInput();
    ASSERT_EQ(9, matrix.getDimension());
}