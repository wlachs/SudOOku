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
 * Version 2
 */
TEST_F(ReadMatrixFromFileTests, read_invalid_test_v2) {
    /* Initialize input file */
    inputFile.open(".mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile{inputFile};

    /* Expect the hasInput function to return false as there is no valid input */
    ASSERT_EQ(false, readMatrixFromFile.hasInput());
}

/**
 * Test case for reading one Matrix from a single input
 * Version 2
 */
TEST_F(ReadMatrixFromFileTests, read_single_test_v2) {
    /* Initialize single input file */
    inputFile.open("small1.mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile{inputFile};

    /* Initialize input Matrix vector */
    std::vector<Matrix> vector{};

    /* Read all Matrices from input */
    while (readMatrixFromFile.hasInput()) {
        /* Read input */
        Matrix inputMatrix = readMatrixFromFile.readOne();

        /* Add Matrix read to vector */
        vector.push_back(inputMatrix);
    }

    /* Expect input to have exactly one Matrix */
    ASSERT_EQ(1, vector.size());

    /* Locally initialize Matrix */
    Matrix m1{4, {
            {{1, 1}, Field{1}},
            {{2, 1}, Field{2}},
            {{3, 1}, Field{3}}
    }};

    /* Check whether the Matrices are correct */
    EXPECT_EQ(m1, vector[0]);
}

/**
 * Test case for reading multiple Matrices from a single input
 * Version 2
 */
TEST_F(ReadMatrixFromFileTests, read_multiple_test_v2) {
    /* Initialize multiple input file */
    inputFile.open("small5.mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile{inputFile};

    /* Initialize input Matrix vector */
    std::vector<Matrix> vector{};

    /* Read all Matrices from input */
    while (readMatrixFromFile.hasInput()) {
        /* Read input */
        Matrix inputMatrix = readMatrixFromFile.readOne();

        /* Add Matrix read to vector */
        vector.push_back(inputMatrix);
    }

    /* Expect input to have exactly two Matrices */
    ASSERT_EQ(2, vector.size());

    /* Locally initialize Matrices */
    Matrix m1{4, {
            {{1, 1}, Field{1}},
            {{2, 1}, Field{2}},
            {{3, 1}, Field{3}}
    }};
    Matrix m2{4, {
            {{1, 1}, Field{1}},
            {{1, 2}, Field{2}},
            {{1, 3}, Field{3}}
    }};

    /* Check whether the Matrices are correct */
    EXPECT_EQ(m1, vector[0]);
    EXPECT_EQ(m2, vector[1]);
}

/**
 * Test case for reading multiple Matrices from a single commented input
 * Version 2
 */
TEST_F(ReadMatrixFromFileTests, read_commented_puzzles_test_v2) {
    /* Initialize input file */
    inputFile.open("small6.mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile{inputFile};

    /* Initialize input Matrix vector */
    std::vector<Matrix> vector{};

    /* Read all Matrices from input */
    while (readMatrixFromFile.hasInput()) {
        /* Read input */
        Matrix inputMatrix = readMatrixFromFile.readOne();

        /* Add Matrix read to vector */
        vector.push_back(inputMatrix);
    }

    /* Expect input to have exactly two Matrices */
    ASSERT_EQ(2, vector.size());

    /* The two Matrices read must equal to the Matrices in the small5.mat file */
    /* Initialize multiple input file */
    std::ifstream inputFile_;
    inputFile_.open("small5.mat");

    /* Initialize ReadMatrixFromFile object */
    ReadMatrixFromFile readMatrixFromFile_{inputFile_};

    /* Initialize input Matrix vector */
    std::vector<Matrix> vector_{};

    /* Read all Matrices from input */
    while (readMatrixFromFile_.hasInput()) {
        /* Read input */
        Matrix inputMatrix_ = readMatrixFromFile_.readOne();

        /* Add Matrix read to vector */
        vector_.push_back(inputMatrix_);
    }

    /* Expect input to have exactly two Matrices */
    ASSERT_EQ(2, vector_.size());

    /* Compare the two Matrices */
    EXPECT_EQ(vector[0], vector_[0]);
    EXPECT_EQ(vector[1], vector_[1]);
}