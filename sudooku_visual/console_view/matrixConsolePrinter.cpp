//
// Created by Borbély László on 2018. 10. 22..
//

#include "matrixConsolePrinter.h"
#include <iostream>

void MatrixConsolePrinter::print(Matrix const &matrix) {
    unsigned short const int dimension = matrix.getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            auto possibleValues = matrix[{x, y}].getPossibleValues();

            if (possibleValues.size() == 1) {
                std::cout << possibleValues[0] << " ";
            } else {
                std::cout << "  ";
            }
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}