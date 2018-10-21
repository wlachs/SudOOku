//
// Created by Borbély László on 2018. 09. 15..
//

#include "rowStrategy.h"
#include <algorithm>

bool RowStrategy::validate(Matrix const &matrix) const {
    auto dimension = matrix.getDimension();

    for (unsigned short int row = 1; row <= dimension; ++row) {
        std::vector<unsigned short int> fixValues = {};
        for (unsigned short int column = 1; column <= dimension; ++column) {
            if (matrix[{row, column}].getPossibleValues().size() == 1) {
                auto fixValue = matrix[{row, column}].getPossibleValues()[0];
                auto result = std::find(std::begin(fixValues), std::end(fixValues), fixValue);

                if (result != std::end(fixValues)) {
                    return false;
                }

                fixValues.push_back(fixValue);
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
    bool result = false;

    for (unsigned short int column = 1; column <= dimension; ++column) {
        auto possibleValues = matrix[{row, column}].getPossibleValues();

        if (possibleValues.size() == 1) {
            result = optimizeSingular(matrix, row, column, dimension, possibleValues) || result;
        } else if (possibleValues.size() > 1) {
            result = optimizeUnique(matrix, row, column, dimension, possibleValues) || result;
        }
    }

    return result;
}

bool RowStrategy::optimizeSingular(Matrix &matrix,
                                   unsigned short const int row,
                                   unsigned short const int column,
                                   unsigned short const int dimension,
                                   std::vector<unsigned short int> const &value) const {
    bool topResult =
            recursiveRemove(matrix, row, column - 1, dimension, -1, value[0]);
    bool bottomResult =
            recursiveRemove(matrix, row, column + 1, dimension, 1, value[0]);

    return topResult || bottomResult;
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