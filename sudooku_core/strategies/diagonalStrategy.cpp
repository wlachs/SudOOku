//
// Created by Borbély László on 2018. 10. 21..
//

#include "diagonalStrategy.h"
#include <algorithm>

bool DiagonalStrategy::validate(Matrix const &m) {
    constMatrix = &m;
    dimension = constMatrix->getDimension();

    return validateInDirection(true) && validateInDirection(false);
}

bool DiagonalStrategy::validateInDirection(const bool forward) const {
    std::vector<unsigned short int> fixValues = {};

    for (unsigned short int row_column = 1; row_column <= dimension; ++row_column) {
        unsigned short int specifier = row_column;
        if (!forward) {
            specifier = (unsigned short int) (dimension - specifier + 1);
        }

        auto values = (*constMatrix)[{row_column, specifier}].getPossibleValues();

        if (values.size() == 1) {
            auto result = std::find(std::begin(fixValues), std::end(fixValues), values[0]);

            if (result != std::end(fixValues)) {
                return false;
            } else {
                fixValues.push_back(values[0]);
            }
        }
    }

    return true;
}