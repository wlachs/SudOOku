//
// Created by Borbély László on 2018. 10. 23..
//

#include "printMatrixToFile.h"

PrintMatrixToFile::PrintMatrixToFile(std::string const &fileName) {
    solutionsFile.open(fileName);
}

PrintMatrixToFile::~PrintMatrixToFile() {
    solutionsFile.close();
}

void PrintMatrixToFile::print(Matrix const &matrix) {
    unsigned short const int dimension = matrix.getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            auto possibleValues = matrix[{x, y}].getPossibleValues();

            if (possibleValues.size() == 1) {
                solutionsFile << possibleValues[0] << " ";
            } else {
                solutionsFile << "  ";
            }
        }

        solutionsFile << std::endl;
    }

    solutionsFile << std::endl;
}