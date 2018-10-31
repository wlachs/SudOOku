//
// Created by Borbély László on 2018. 10. 23..
//

#include "printMatrixToFile.h"

/**
 * Initialize class variable containing a reference to the output file stream
 * @param solutionsFile_
 */
PrintMatrixToFile::PrintMatrixToFile(std::ofstream &solutionsFile_) : solutionsFile(solutionsFile_) {}

/**
 * Prints the Matrix to the specified file
 * @param matrix
 */
void PrintMatrixToFile::print(Matrix const &matrix) {
    /* Get dimension of the Matrix */
    unsigned short const int dimension = matrix.getDimension();

    /* Iterate over each pair of coordinates */
    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {

            /* Retrieve possible values of the Field */
            auto possibleValues = matrix[{x, y}].getPossibleValues();

            if (possibleValues.size() == 1) {
                /* If the Field has a fixed value, print it */
                solutionsFile << possibleValues[0] << " ";
            } else {
                /* Otherwise, leave it blank */
                solutionsFile << "  ";
            }
        }

        /* Line break after each row */
        solutionsFile << std::endl;
    }

    /* Empty line after each solution */
    solutionsFile << std::endl;
}