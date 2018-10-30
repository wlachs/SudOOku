//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVINGSTRATEGY_H
#define SUDOOKU_SOLVINGSTRATEGY_H

#include <sudooku_core/matrix/field.h>
#include <sudooku_core/matrix/matrix.h>

/**
 * Abstract class to provide an interface for solving the puzzle
 * Each SolvingStrategy must be able to validate a Matrix according to its rules
 * Simplification function can be provided but it isn't mandatory, only strongly recommended for
 * performance purposes
 */
class SolvingStrategy {
public:
    SolvingStrategy() = default;

    virtual bool validate(Matrix const &) = 0;

    virtual bool simplify(Matrix &) { return false; };

    virtual ~SolvingStrategy() = default;
};


#endif //SUDOOKU_SOLVINGSTRATEGY_H
