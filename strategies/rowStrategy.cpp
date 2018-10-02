//
// Created by Borbély László on 2018. 09. 15..
//

#include "strategies.h"

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

bool RowStrategy::simplifyRow(Matrix &matrix, unsigned short const int row, unsigned short const int dimension) const {
    bool singularResult = optimizeSingular(matrix, row, dimension);
    bool uniqueResult = optimizeUnique(matrix, row, dimension);

    return singularResult || uniqueResult;
}

bool RowStrategy::optimizeSingular(Matrix &matrix, unsigned short const int row,
                                   unsigned short const int dimension) const {
    bool simplified = false;

    for (unsigned short int column = 1; column <= dimension; ++column) {
        auto possibleValues = matrix[{row, column}].getPossibleValues();
        if (possibleValues.size() == 1) {
            bool leftResult =
                    recursiveRemove(matrix, row, (unsigned short int) (column - 1), dimension, -1, possibleValues[0]);
            bool rightResult =
                    recursiveRemove(matrix, row, (unsigned short int) (column + 1), dimension, 1, possibleValues[0]);
            simplified = leftResult || rightResult;
        }
    }

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

    auto possibleValues = matrix[{row, column}].getPossibleValues();
    auto it = std::find(std::begin(possibleValues), std::end(possibleValues), value);
    bool simplified = false;

    if (it != std::end(possibleValues)) {
        possibleValues.erase(it);
        matrix[{row, column}].setPossibleValues(possibleValues);
        simplified = true;
    }

    return recursiveRemove(matrix, row, column + direction, dimension, direction, value) || simplified;
}

bool
RowStrategy::optimizeUnique(Matrix &matrix, unsigned short const int row, unsigned short const int dimension) const {
    for (unsigned short int column = 1; column <= dimension; ++column) {
        auto possibleValues = matrix[{row, column}].getPossibleValues();
        if (possibleValues.size() > 1) {
            for (auto value : matrix[{row, column}].getPossibleValues()) {
                if (isUniqueInRow(matrix, row, dimension, value)) {
                    std::vector<unsigned short int> newPossibleValue = {value};
                    matrix[{row, column}].setPossibleValues(newPossibleValue);
                    return true;
                }
            }
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