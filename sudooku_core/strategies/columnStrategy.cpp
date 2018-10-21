//
// Created by Borbély László on 2018. 09. 30..
//

#include "columnStrategy.h"
#include <algorithm>

bool ColumnStrategy::validate(Matrix const &matrix) const {
    auto dimension = matrix.getDimension();

    for (unsigned short int column = 1; column <= dimension; ++column) {
        if (!isColumnValid(matrix, column, dimension)) {
            return false;
        }
    }

    return true;
}

bool ColumnStrategy::isColumnValid(Matrix const &matrix,
                                   unsigned short const int column,
                                   unsigned short const int dimension) const {
    std::vector<unsigned short int> fixValues = {};

    for (unsigned int row = 1; row <= dimension; ++row) {
        auto possibleValues = matrix[{row, column}].getPossibleValues();

        if (possibleValues.size() == 1) {
            auto result = std::find(std::begin(fixValues), std::end(fixValues), possibleValues[0]);

            if (result != std::end(fixValues)) {
                return false;
            } else {
                fixValues.push_back(possibleValues[0]);
            }
        }
    }

    return true;
}

bool ColumnStrategy::simplify(Matrix &matrix) const {
    auto dimension = matrix.getDimension();
    bool simplified = false;

    for (unsigned short int column = 1; column <= dimension; ++column) {
        if (simplifyColumn(matrix, column, dimension)) {
            simplified = true;
        }
    }

    return simplified;
}

bool ColumnStrategy::simplifyColumn(Matrix &matrix, unsigned short const int column,
                                    unsigned short const int dimension) const {
    bool singularResult = optimizeSingular(matrix, column, dimension);
    bool uniqueResult = optimizeUnique(matrix, column, dimension);

    return singularResult || uniqueResult;
}

bool ColumnStrategy::optimizeSingular(Matrix &matrix, unsigned short const int column,
                                      unsigned short const int dimension) const {
    bool simplified = false;

    for (unsigned short int row = 1; row <= dimension; ++row) {
        auto possibleValues = matrix[{row, column}].getPossibleValues();
        if (possibleValues.size() == 1) {
            bool topResult =
                    recursiveRemove(matrix, (unsigned short int) (row - 1), column, dimension, -1, possibleValues[0]);
            bool bottomResult =
                    recursiveRemove(matrix, (unsigned short int) (row + 1), column, dimension, 1, possibleValues[0]);
            simplified = topResult || bottomResult;
        }
    }

    return simplified;
}

bool ColumnStrategy::recursiveRemove(Matrix &matrix,
                                     unsigned short const int row,
                                     unsigned short const int column,
                                     unsigned short const int dimension,
                                     short const int direction,
                                     unsigned short const int value) const {
    if (row < 1 || row > dimension) {
        return false;
    }

    bool simplified = matrix[{row, column}].removeValue(value);

    return recursiveRemove(matrix, row + direction, column, dimension, direction, value) || simplified;
}

bool
ColumnStrategy::optimizeUnique(Matrix &matrix, unsigned short const int column,
                               unsigned short const int dimension) const {
    for (unsigned short int row = 1; row <= dimension; ++row) {
        auto possibleValues = matrix[{row, column}].getPossibleValues();
        if (possibleValues.size() > 1) {
            for (auto value : matrix[{row, column}].getPossibleValues()) {
                if (isUniqueInColumn(matrix, column, dimension, value)) {
                    matrix[{row, column}].fixValue(value);
                    return true;
                }
            }
        }
    }

    return false;
}

bool ColumnStrategy::isUniqueInColumn(Matrix const &matrix, unsigned short const int column,
                                      unsigned short const int dimension,
                                      unsigned short const int value) const {
    unsigned short int count = 0;

    for (unsigned short int row = 1; row <= dimension; ++row) {
        if (matrix[{row, column}].contains(value)) {
            ++count;
        }
    }

    return count == 1;
}