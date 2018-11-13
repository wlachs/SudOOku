//
// Created by Borbély László on 2018. 09. 15..
//

#include "rowStrategy.h"
#include <algorithm>

/**
 * Validate Matrix
 * Checks whether each row only contains a single value once
 * If it contains a value more than once, the Matrix isn't valid
 * @param m
 * @return
 */
bool RowStrategy::validate(Matrix const &m) {
    /* Save Matrix and dimension as class variables */
    constMatrix = &m;
    dimension = constMatrix->getDimension();

    /* Perform check for each row */
    for (row = 1; row <= dimension; ++row) {
        if (!isRowValid()) {
            return false;
        }
    }

    return true;
}

/**
 * Check whether each row is valid according to the specified rules
 * @return
 */
bool RowStrategy::isRowValid() {
    /* Store each single value seen */
    std::vector<unsigned short int> fixValues = {};

    /* Iterate through every column */
    for (column = 1; column <= dimension; ++column) {
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
 * Go through each row and try to simplify them according to the specified rules
 * @param m
 * @return
 */
bool RowStrategy::simplify(Matrix &m) {
    /* Save Matrix and dimension as class variables */
    this->matrix = &m;
    this->dimension = matrix->getDimension();

    /* Store whether the Matrix has been successfully simplified */
    bool simplified = false;

    /* Simplify each row */
    for (row = 1; row <= dimension; ++row) {
        if (simplifyRow()) {
            simplified = true;
        }
    }

    return simplified;
}

/**
 * Simplify row
 * The simplification uses two different strategies
 * 1. Find singular values
 * 2. Find unique values
 * @return
 */
bool RowStrategy::simplifyRow() {
    /* Store whether the row has been successfully simplified */
    bool result = false;

    /* Go through each column and execute optimization */
    for (column = 1; column <= dimension; ++column) {
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
 * Optimize singular row values
 * If the value in a row is fixed, remove it from the value vectors of all other Fields in the same row
 * @param value
 * @return
 */
bool RowStrategy::optimizeSingular(std::vector<unsigned short int> const &value) const {
    /* Remove all instances of the passed value left to the current coordinate */
    bool topResult = recursiveRemove(static_cast<unsigned short int>(column - 1), -1, value[0]);

    /* Remove all instances of the passed value right to the current coordinate */
    bool bottomResult = recursiveRemove(static_cast<unsigned short int>(column + 1), 1, value[0]);

    /* Optimization was successful if at least one value was removed */
    return topResult || bottomResult;
}

/**
 * Execute recursive removal
 * Removes a passed value from each Field in the specified direction until it reaches the end of the Matrix
 * @param column_
 * @param direction
 * @param value
 * @return
 */
bool RowStrategy::recursiveRemove(unsigned short const int column_,
                                  short const int direction,
                                  unsigned short const int value) const {
    /* Stop execution if an edge was reached */
    if (column_ < 1 || column_ > dimension) {
        return false;
    }

    /* Simplification was successful if a value was removed */
    bool simplified = (*matrix)[{row, column_}].removeValue(value);

    /* Recursive call */
    return recursiveRemove(column_ + direction, direction, value) || simplified;
}

/**
 * Optimize unique row values
 * It might happen that there are no singular values in a row but in the value vectors there is an element at a certain
 * coordinate of the row where it can be written and nowhere else
 * If this is the case, replace the vector of the matching Field with the mentioned value
 * @param values
 * @return
 */
bool RowStrategy::optimizeUnique(std::vector<unsigned short int> const &values) const {
    /* Check unique criteria for each value in the row */
    for (auto const value : values) {
        if (isUniqueInRow(value)) {
            /* If it is unique, fix it */
            (*matrix)[{row, column}].fixValue(value);
            return true;
        }
    }

    return false;
}

/**
 * Check whether the unique value criteria is fulfilled in the row
 * Unique criteria is fulfilled if a value can only be written at one certain point of the row
 * @param value
 * @return
 */
bool RowStrategy::isUniqueInRow(unsigned short const int value) const {
    /* Check hit count */
    unsigned short int count = 0;

    /* Calculate for each value how many different positions it can be written in row */
    for (unsigned short int local_column = 1; local_column <= dimension; ++local_column) {
        if ((*matrix)[{row, local_column}].contains(value)) {
            ++count;
        }
    }

    /* Value is unique if the hit count equals 1 */
    return count == 1;
}