//
// Created by Borbély László on 2018. 09. 30..
//

#include "columnStrategy.h"
#include <algorithm>

/**
 * Validate Matrix
 * Checks whether each column only contains a single value once
 * If it contains a value more than once, the Matrix isn't valid
 * @param m
 * @return
 */
bool ColumnStrategy::validate(Matrix const &m) {
    /* Save Matrix and dimension as class variables */
    constMatrix = &m;
    dimension = constMatrix->getDimension();

    /* Perform check for each column */
    for (column = 1; column <= dimension; ++column) {
        if (!isColumnValid()) {
            return false;
        }
    }

    return true;
}

/**
 * Check whether each column is valid according to the specified rules
 * @return
 */
bool ColumnStrategy::isColumnValid() {
    /* Store each single value seen */
    std::vector<unsigned short int> fixValues = {};

    /* Iterate over each row */
    for (row = 1; row <= dimension; ++row) {
        auto const &possibleValues = (*constMatrix)[{row, column}].getPossibleValues();

        /* Add single values to vector */
        if (possibleValues.size() == 1) {
            auto const result = std::find(std::begin(fixValues), std::end(fixValues), possibleValues[0]);

            /* Check whether the value has already been seen */
            if (result != std::end(fixValues)) {
                return false;
            } else {
                fixValues.push_back(possibleValues[0]);
            }
        }
    }

    return true;
}

/**
 * Simplify Matrix
 * Go through each column and try to simplify them according to the specified rules
 * @param m
 * @return
 */
bool ColumnStrategy::simplify(Matrix &m) {
    /* Save Matrix and dimension as class variables */
    matrix = &m;
    dimension = matrix->getDimension();

    /* Store whether the Matrix has been successfully simplified */
    bool simplified = false;

    /* Simplify each column */
    for (column = 1; column <= dimension; ++column) {
        if (simplifyColumn()) {
            simplified = true;
        }
    }

    return simplified;
}

/**
 * Simplify column
 * The simplification uses two different strategies
 * 1. Find singular values
 * 2. Find unique values
 * @return
 */
bool ColumnStrategy::simplifyColumn() {
    /* Store whether the column has been successfully simplified */
    bool result = false;

    /* Go over each row and execute optimization */
    for (row = 1; row <= dimension; ++row) {
        auto const &possibleValues = (*matrix)[{row, column}].getPossibleValues();

        if (possibleValues.size() == 1) {
            /* If there is only one value on the coordinate, choose singular optimization */
            result = optimizeSingular(possibleValues) || result;
        } else if (possibleValues.size() > 1) {
            /* If there are multiple values, use unique */
            result = optimizeUnique(possibleValues) || result;
        }
    }

    return result;
}

/**
 * Optimize singular column values
 * If the value in a column is fixed, remove it from the value vectors of all other Fields in the same column
 * @param value
 * @return
 */
bool ColumnStrategy::optimizeSingular(std::vector<unsigned short int> const &value) {
    /* Remove all instances of the passed value below the current coordinate */
    bool topResult = recursiveRemove(static_cast<unsigned short int>(row - 1), -1, value[0]);

    /* Remove all instances of the passed value above the current coordinate */
    bool bottomResult = recursiveRemove(static_cast<unsigned short int>(row + 1), 1, value[0]);

    /* Optimization was successful if at least one value was removed */
    return topResult || bottomResult;
}

/**
 * Execute recursive removal
 * Removes a passed value from each Field in the specified direction until it reaches the end of the Matrix
 * @param row_
 * @param direction
 * @param value
 * @return
 */
bool ColumnStrategy::recursiveRemove(unsigned short const int row_,
                                     short const int direction,

                                     unsigned short const int value) {
    /* Stop execution if an edge was reached */
    if (row_ < 1 || row_ > dimension) {
        return false;
    }

    /* Simplification was successful if a value was removed */
    bool simplified = (*matrix)[{row_, column}].removeValue(value);

    /* Recursive call */
    return recursiveRemove(row_ + direction, direction, value) || simplified;
}

/**
 * Optimize unique column values
 * It might happen that there are no singular values in a column but in the value vectors there is an element at a
 * certain coordinate of the column where it can be written and nowhere else
 * If this is the case, replace the vector of the matching Field with the mentioned value
 * @param values
 * @return
 */
bool ColumnStrategy::optimizeUnique(std::vector<unsigned short int> const &values) {
    /* Check unique criteria for each value in the column */
    for (auto const value : values) {
        if (isUniqueInColumn(value)) {
            /* If it is unique, fix it */
            (*matrix)[{row, column}].fixValue(value);
            return true;
        }
    }

    return false;
}

/**
 * Check whether the unique value criteria is fulfilled in the column
 * Unique criteria is fulfilled if a value can only be written at one certain point of the column
 * @param value
 * @return
 */
bool ColumnStrategy::isUniqueInColumn(unsigned short const int value) const {
    /* Check hit count */
    unsigned short int count = 0;

    /* Calculate for each value how many different positions it can be written in column */
    for (unsigned short int local_row = 1; local_row <= dimension; ++local_row) {
        if ((*matrix)[{local_row, column}].contains(value)) {
            ++count;
        }
    }

    /* Value is unique if the hit count equals 1 */
    return count == 1;
}