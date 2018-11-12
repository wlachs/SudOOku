//
// Created by Borbély László on 2018. 11. 12..
//

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <sudooku_visual/print_matrix_to_file/printMatrixToFile.h>

/**
 * Checks whether the content a certain line in the specified file matches the one provided as a parameter
 * @param fileName
 * @param lineId
 * @param value
 * @return
 */
bool lineEquals(std::string const &fileName, unsigned const int lineId, std::string const &value) {
    /* Initialize input file */
    std::ifstream inputFile;

    /* Open input file */
    inputFile.open(fileName);

    /* Initialize line id counter */
    unsigned int lineCounter = 1;

    /* Initialize line string */
    std::string line{};

    /* Initialize return value */
    bool returnValue = false;

    /* Start reading input */
    while (getline(inputFile, line)) {
        /* Check whether the current line needs to be checked */
        if (lineCounter == lineId) {
            /* Compare values and set return value */
            returnValue = line == value;
        }

        /* Increment line counter */
        ++lineCounter;
    }

    /* Close input file */
    inputFile.close();

    /* Return result */
    return returnValue;
}

/**
 * PrintMatrixToFile test fixture class
 */
class PrintMatrixToFileTests : public ::testing::Test {
protected:
    const std::string FILE_NAME = "solution2.mat";
    std::ofstream outputFile;
    SudookuPrinter *printMatrixToFile;
    Matrix matrix;

    /**
     * Setup method running before the execution of each test case
     */
    void SetUp() override {
        /* Open output file */
        outputFile.open(FILE_NAME);

        /* Initialize PrintMatrixToFile object */
        printMatrixToFile = new PrintMatrixToFile{outputFile};

        /* Initialize sample Matrix object */
        matrix = Matrix{4, {{{1, 1}, Field{1}}}};
    }

    /**
     * Teardown method running after the execution of each test case
     */
    void TearDown() override {
        /* Delete SudookuReader object */
        delete printMatrixToFile;
    }
};

/**
 * Test case to check whether the output commnet format of a single matrix is correct
 */
TEST_F(PrintMatrixToFileTests, print_single_comment_test) {
    /* Print solution header */
    printMatrixToFile->printStart(1);

    /* Print Matrix */
    printMatrixToFile->print(matrix);

    /* Print trailing comment */
    printMatrixToFile->printEnd();

    /* Close output file */
    outputFile.close();

    /* Check header line comment */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 1, "## Solutions for puzzle 1"));

    /* Check trailing line comment */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 7, "#########"));
}

/**
 * Test case to check whether the output comment format of multiple matrices are correct
 */
TEST_F(PrintMatrixToFileTests, print_multiple_comment_test) {
    for (unsigned int i = 1; i <= 2; ++i) {
        /* Print solution header */
        printMatrixToFile->printStart(i);

        /* Print Matrix */
        printMatrixToFile->print(matrix);

        /* Print trailing comment */
        printMatrixToFile->printEnd();
    }

    /* Close output file */
    outputFile.close();

    /* Check header line comment */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 1, "## Solutions for puzzle 1"));

    /* Check trailing line comment */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 7, "#########"));

    /* Check header line comment */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 9, "## Solutions for puzzle 2"));

    /* Check trailing line comment */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 15, "#########"));
}

/**
 * Check whether the output format of a single matrix is correct
 */
TEST_F(PrintMatrixToFileTests, print_single_test) {
    /* Print Matrix */
    printMatrixToFile->print(matrix);

    /* Close output file */
    outputFile.close();

    /* Check every line */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 1, "1;;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 2, ";;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 3, ";;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 4, ";;;;"));
}

/**
 * Check whether the output format of multiple matrices are correct
 */
TEST_F(PrintMatrixToFileTests, print_multiple_test) {
    /* Print Matrix */
    printMatrixToFile->print(matrix);

    /* Print Matrix again */
    printMatrixToFile->print(matrix);

    /* Close output file */
    outputFile.close();

    /* Check every line */
    EXPECT_EQ(true, lineEquals(FILE_NAME, 1, "1;;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 2, ";;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 3, ";;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 4, ";;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 5, ""));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 6, "1;;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 7, ";;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 8, ";;;;"));
    EXPECT_EQ(true, lineEquals(FILE_NAME, 9, ";;;;"));
}