//
// Created by Borbély László on 2018. 09. 30..
//

#include "columnStrategy.h"
#include <algorithm>

bool ColumnStrategy::validate(Matrix const &m) {
    constMatrix = &m;
    dimension = constMatrix->getDimension();

    for (column = 1; column <= dimension; ++column) {
        if (!isColumnValid()) {
            return false;
        }
    }

    return true;
}

bool ColumnStrategy::isColumnValid() {
    std::vector<unsigned short int> fixValues = {};

    for (row = 1; row <= dimension; ++row) {
        auto possibleValues = (*constMatrix)[{row, column}].getPossibleValues();

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

bool ColumnStrategy::simplify(Matrix &m) {
    matrix = &m;
    dimension = matrix->getDimension();
    bool simplified = false;

    for (column = 1; column <= dimension; ++column) {
        if (simplifyColumn()) {
            simplified = true;
        }
    }

    return simplified;
}

bool ColumnStrategy::simplifyColumn() {
    bool result = false;

    for (row = 1; row <= dimension; ++row) {
        auto possibleValues = (*matrix)[{row, column}].getPossibleValues();

        if (possibleValues.size() == 1) {
            result = optimizeSingular(possibleValues) || result;
        } else if (possibleValues.size() > 1) {
            result = optimizeUnique(possibleValues) || result;
        }
    }

    return result;
}

bool ColumnStrategy::optimizeSingular(std::vector<unsigned short int> const &value) {
    bool topResult = recursiveRemove((unsigned short int) (row - 1), -1, value[0]);
    bool bottomResult = recursiveRemove((unsigned short int) (row + 1), 1, value[0]);

    return topResult || bottomResult;
}

bool ColumnStrategy::recursiveRemove(unsigned short const int row,
                                     short const int direction,
                                     unsigned short const int value) {
    if (row < 1 || row > dimension) {
        return false;
    }

    bool simplified = (*matrix)[{row, column}].removeValue(value);

    return recursiveRemove(row + direction, direction, value) || simplified;
}

bool ColumnStrategy::optimizeUnique(std::vector<unsigned short int> const &values) {
    for (auto value : values) {
        if (isUniqueInColumn(value)) {
            (*matrix)[{row, column}].fixValue(value);
            return true;
        }
    }

    return false;
}

bool ColumnStrategy::isUniqueInColumn(unsigned short const int value) const {
    unsigned short int count = 0;

    for (unsigned short int row = 1; row <= dimension; ++row) {
        if ((*matrix)[{row, column}].contains(value)) {
            ++count;
        }
    }

    return count == 1;
}