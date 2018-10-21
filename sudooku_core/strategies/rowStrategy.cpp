//
// Created by Borbély László on 2018. 09. 15..
//

#include "rowStrategy.h"
#include <algorithm>

bool RowStrategy::validate(Matrix const &matrix) const {
    auto dimension = matrix.getDimension();

    for (unsigned short int row = 1; row <= dimension; ++row) {
        if (!isRowValid(matrix, row, dimension)) {
            return false;
        }
    }

    return true;
}

bool RowStrategy::isRowValid(Matrix const &matrix,
                             unsigned short const int row,
                             unsigned short const int dimension) const {
    std::vector<unsigned short int> fixValues = {};

    for (unsigned int column = 1; column <= dimension; ++column) {
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

bool RowStrategy::simplify(Matrix &matrix) const {
    auto dimension = matrix.getDimension();
    bool simplified = false;

    for (unsigned short int row = 1; row <= dimension; ++row) {
        if (simplifyRow(matrix, row, dimension)) {
            simplified = true;
        }
    }

    return simplified;
}

bool RowStrategy::simplifyRow(Matrix &matrix, unsigned short const int row,
                              unsigned short const int dimension) const {
    bool simplified = false;

    for (unsigned short int column = 1; column <= dimension; ++column) {
        auto possibleValues = matrix[{row, column}].getPossibleValues();

        if (possibleValues.size() == 1) {
            simplified = optimizeSingular(matrix, row, column, dimension, possibleValues) || simplified;
        } else if (possibleValues.size() > 1) {
            simplified = optimizeUnique(matrix, row, column, dimension, possibleValues) || simplified;
        }
    }

    return simplified;
}

bool RowStrategy::optimizeSingular(Matrix &matrix,
                                   unsigned short const int row,
                                   unsigned short const int column,
                                   unsigned short const int dimension,
                                   std::vector<unsigned short int> const &value) const {
    bool simplified = recursiveRemove(matrix, row, 1, dimension, 1, value[0]);
    matrix[{row, column}].setPossibleValues(value);

    return simplified;
}

bool RowStrategy::recursiveRemove(Matrix &matrix,
                                  unsigned short const int row,
                                  unsigned short const int column,
                                  unsigned short const int dimension,
                                  short const int direction,
                                  unsigned short const int value) const {
    if (column < 1 || column > dimension) {
        return false;
    }

    bool simplified = matrix[{row, column}].removeValue(value);

    return recursiveRemove(matrix, row, column + direction, dimension, direction, value) || simplified;
}

bool RowStrategy::optimizeUnique(Matrix &matrix,
                                 unsigned short const int row,
                                 unsigned short const int column,
                                 unsigned short const int dimension,
                                 std::vector<unsigned short int> const &values) const {
    for (auto value : values) {
        if (isUniqueInRow(matrix, row, dimension, value)) {
            matrix[{row, column}].fixValue(value);
            return true;
        }
    }

    return false;
}

bool RowStrategy::isUniqueInRow(Matrix const &matrix, unsigned short const int row, unsigned short const int dimension,
                                unsigned short const int value) const {
    unsigned short int count = 0;

    for (unsigned short int column = 1; column <= dimension; ++column) {
        if (matrix[{row, column}].contains(value)) {
            ++count;
        }
    }

    return count == 1;
}