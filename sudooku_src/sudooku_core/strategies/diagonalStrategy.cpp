//
// Created by Borbély László on 2018. 10. 21..
//

#include "diagonalStrategy.h"
#include <algorithm>

/**
 * Validate Matrix
 * Checks whether both diagonals only contain a single value once
 * If they contain a value more than once, the Matrix isn't valid
 * @param m
 * @return
 */
bool DiagonalStrategy::validate(Matrix const &m) {
    /* Save Matrix and dimension as class variables */
    constMatrix = &m;
    dimension = constMatrix->getDimension();

    /* Validate both diagonals of the Matrix */
    return validateInDirection(true) && validateInDirection(false);
}

/**
 * Validate the elements of the Matrix in the diagonals
 * Depending on the boolean parameter passed, either the top-left -> bottom-right or the top-right -> bottom-left
 * diagonal is validated
 * @param forward
 * @return
 */
bool DiagonalStrategy::validateInDirection(const bool forward) const {
    /* Store singular values of the diagonal in a vector */
    std::vector<unsigned short int> fixValues = {};

    /* The row and column indexes are either equal or the complement of each other */
    for (unsigned short int row_column = 1; row_column <= dimension; ++row_column) {
        unsigned short int specifier = row_column;

        /* Swap specifier if the other diagonal is checked */
        if (!forward) {
            specifier = static_cast<unsigned short int>(dimension - specifier + 1);
        }

        /* Get possible values of a certain Field of the diagonal */
        auto values = (*constMatrix)[{row_column, specifier}].getPossibleValues();

        /* Check element count of Field values */
        if (values.size() == 1) {
            auto result = std::find(std::begin(fixValues), std::end(fixValues), values[0]);

            if (result != std::end(fixValues)) {
                /* If the vector of fixed values already contains the checked value, the Matrix isn't valid */
                return false;
            } else {
                /* Otherwise, add it to the vector of fixed values */
                fixValues.push_back(values[0]);
            }
        }
    }

    return true;
}