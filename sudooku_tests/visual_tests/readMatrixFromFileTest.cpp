//
// Created by Borbély László on 2018. 11. 09..
//

#include <gtest/gtest.h>
#include <fstream>
#include <sudooku_visual/read_matrix_from_file/readMatrixFromFile.h>

/**
 * ReadMatrixFromFile test fixture class
 */
class ReadMatrixFromFileTests : public ::testing::Test {
protected:
    std::ifstream inputFile;

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Close input files */
        inputFile.close();
    }
};

/**
 * Test case for reading an invalid input file
 */
TEST_F(ReadMatrixFromFileTests, read_invalid_test) {
    /* Initialize input file */
    inputFile.open(".mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile{inputFile};

    /* Read all Matrices from input */
    auto const &vector = readMatrixFromFile.readAll();

    /* Expect input to have no Matrix */
    ASSERT_EQ(0, vector.size());
}

/**
 * Test case for reading one Matrix from a single input
 */
TEST_F(ReadMatrixFromFileTests, read_single_test) {
    /* Initialize single input file */
    inputFile.open("small1.mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile{inputFile};

    /* Read all Matrices from input */
    auto const &vector = readMatrixFromFile.readAll();

    /* Expect input to have exactly one Matrix */
    ASSERT_EQ(1, vector.size());
}

/**
 * Test case for reading multiple Matrices from a single input
 */
TEST_F(ReadMatrixFromFileTests, read_multiple_test) {
    /* Initialize multiple input file */
    inputFile.open("small5.mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile{inputFile};

    /* Read all Matrices from input */
    auto const &vector = readMatrixFromFile.readAll();

    /* Expect input to have exactly one Matrix */
    ASSERT_EQ(2, vector.size());
}