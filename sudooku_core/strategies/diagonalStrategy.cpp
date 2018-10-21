//
// Created by Borbély László on 2018. 10. 21..
//

#include "diagonalStrategy.h"
#include <algorithm>

bool DiagonalStrategy::validate(Matrix const &matrix) const {
    auto dimension = matrix.getDimension();
    return validateDirection1(matrix, dimension) && validateDirection2(matrix, dimension);
}

bool DiagonalStrategy::validateDirection1(Matrix const &matrix, unsigned short const int dimension) const {
    std::vector<unsigned short int> fixValues = {};

    for (unsigned short int row_column = 1; row_column <= dimension; ++row_column) {
        auto values = matrix[{row_column, row_column}].getPossibleValues();

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

bool DiagonalStrategy::validateDirection2(Matrix const &matrix, unsigned short const int dimension) const {
    std::vector<unsigned short int> fixValues = {};

    for (unsigned short int row_column = 1; row_column <= dimension; ++row_column) {
        auto values = matrix[{row_column, dimension - row_column + 1}].getPossibleValues();

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