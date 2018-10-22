//
// Created by Borbély László on 2018. 09. 15..
//

#include "rowStrategy.h"
#include <algorithm>

bool RowStrategy::validate(Matrix const &m) {
    constMatrix = &m;
    dimension = constMatrix->getDimension();

    for (row = 1; row <= dimension; ++row) {
        if (!isRowValid()) {
            return false;
        }
    }

    return true;
}

bool RowStrategy::isRowValid() {
    std::vector<unsigned short int> fixValues = {};

    for (column = 1; column <= dimension; ++column) {
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

bool RowStrategy::simplify(Matrix &m) {
    this->matrix = &m;
    this->dimension = matrix->getDimension();
    bool simplified = false;

    for (row = 1; row <= dimension; ++row) {
        if (simplifyRow()) {
            simplified = true;
        }
    }

    return simplified;
}

bool RowStrategy::simplifyRow() {
    bool result = false;

    for (column = 1; column <= dimension; ++column) {
        auto const &possibleValues = (*matrix)[{row, column}].getPossibleValues();

        if (possibleValues.size() == 1) {
            result = optimizeSingular(possibleValues) || result;
        } else if (possibleValues.size() > 1) {
            result = optimizeUnique(possibleValues) || result;
        }
    }

    return result;
}

bool RowStrategy::optimizeSingular(std::vector<unsigned short int> const &value) const {
    bool topResult = recursiveRemove((unsigned short int) (column - 1), -1, value[0]);
    bool bottomResult = recursiveRemove((unsigned short int) (column + 1), 1, value[0]);

    return topResult || bottomResult;
}

bool RowStrategy::recursiveRemove(unsigned short const int column,
                                  short const int direction,
                                  unsigned short const int value) const {
    if (column < 1 || column > dimension) {
        return false;
    }

    bool simplified = (*matrix)[{row, column}].removeValue(value);

    return recursiveRemove(column + direction, direction, value) || simplified;
}

bool RowStrategy::optimizeUnique(std::vector<unsigned short int> const &values) const {
    for (auto value : values) {
        if (isUniqueInRow(value)) {
            (*matrix)[{row, column}].fixValue(value);
            return true;
        }
    }

    return false;
}

bool RowStrategy::isUniqueInRow(unsigned short const int value) const {
    unsigned short int count = 0;

    for (unsigned short int local_column = 1; local_column <= dimension; ++local_column) {
        if ((*matrix)[{row, local_column}].contains(value)) {
            ++count;
        }
    }

    return count == 1;
}