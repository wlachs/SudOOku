//
// Created by Borbély László on 2018. 09. 15..
//

#include <exceptions/noStrategiesException.h>
#include <exceptions/noMatrixException.h>
#include "solver.h"

/**
 * Set the initial Matrix of the puzzle
 * Normally it is a partially solved puzzle given as an input
 * Must be specified otherwise the execution will fail
 * @param matrix
 */
void Solver::setInitialMatrix(Matrix const &matrix) {
    initialMatrix = matrix;
    dimension = matrix.getDimension();

    /* It is possible to use a Solver object multiple times,
     * that's why the rules must be cleared every time a new Matrix is given */
    solutions.clear();
}

/**
 * Set solving strategies vector
 * @param strategies
 */
void Solver::setRules(std::vector<SolvingStrategy *> const &strategies_) {
    strategies = strategies_;
}

/**
 * It is also possible to set the SolvingStrategies one by one
 * @param solvingStrategy
 */
void Solver::addRule(SolvingStrategy *solvingStrategy) {
    strategies.push_back(solvingStrategy);
}

/**
 * Start solver
 * Should throw exception if no rules are set
 */
void Solver::solve() {
    /* Check whether an input Matrix is given, if not: throw an exception */
    if (initialMatrix == Matrix{}) {
        throw NoMatrixException{};
    }

    /* Check rules, throw exception if it's not specified */
    if (strategies.empty()) {
        throw NoStrategiesException{};
    }

    /* Start execution */
    solve(initialMatrix);
}

/**
 * Get the const reference of the vector of solutions for the given input Matrix
 * @return
 */
std::vector<Matrix> const &Solver::getSolutions() const {
    return solutions;
}

/**
 * Check whether the Matrix has a Field on any coordinate where the vector of possible values is empty
 * If this is the case, the Matrix has no solution and the execution should stop
 * @param matrix
 * @return
 */
bool Solver::hasNoPotentialValues(Matrix const &matrix) const {
    /* Iterate through all possible coordiates to check emptiness */
    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            /* Empty vector means no possible solution */
            if (matrix[{x, y}].getPossibleValues().empty()) {
                return true;
            }
        }
    }

    return false;
}

/**
 * Check whether the given Matrix is valid
 * If not, the execution should stop as there is no solution
 * @param matrix
 * @return
 */
bool Solver::isValid(Matrix const &matrix) const {
    /* Check whether all coordinates have potential values */
    if (hasNoPotentialValues(matrix)) {
        return false;
    }

    /* If on all coordinates there is at least one possible value, use the validation function of the
     * given SolvingStrategies */
    for (auto *strategy : strategies) {
        if (!strategy->validate(matrix)) {
            return false;
        }
    }

    return true;
}

/**
 * Optimize Matrix
 * Using the SolvingStrategies, optimize the Matrix to reduce the search field of solutions
 * @param matrix
 */
void Solver::optimize(Matrix &matrix) const {
    /* Might be that one optimization makes another one possible, therefore the function should only stop
     * when non of the SolvingStrategies were successful */
    bool shouldReRun = false;

    /* Run the optimization function of every SolvingStrategy */
    for (auto *strategy : strategies) {
        if (strategy->simplify(matrix)) {
            shouldReRun = true;
        }
    }

    /* Call self recursively if further simplification is potentially possible */
    if (shouldReRun) {
        optimize(matrix);
    }
}

/**
 * Check whether the given Matrix is a valid solution
 * A Matrix is considered as a solution if at every position it has exactly one possible value
 * and it is valid according to all of the SolvingStrategies
 * @param matrix
 * @return
 */
bool Solver::isSolution(Matrix const &matrix) const {
    /* Solution if valid and in every cell there's only one value */
    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            if (matrix[{x, y}].getPossibleValues().size() != 1) {
                return false;
            }
        }
    }

    return true;
}

/**
 * Solver function
 * Recursively finds all possible solutions of a given input Matrix in 5 steps
 * 1. Simplification
 * 2. Validity check
 * 3. Solution check
 * 4. Make a guess
 * 5. Recursively call both branches to ensure finding every possible solution
 * @param matrix
 */
void Solver::solve(Matrix &matrix) {
    /* 1. Simplify the matrix according to the known strategies */
    optimize(matrix);

    /* 2. Is it still valid? */
    if (!isValid(matrix)) {
        return;
    }

    /* 3. Is the current matrix a valid solution? If yes, add to solutions list. */
    if (isSolution(matrix)) {
        solutions.push_back(matrix);
        return;
    }

    /* 4. Fork the matrix somehow */
    auto matrix_second = matrix.forkFirstReturnSecond();

    /* 5. Repeat */
    solve(matrix);
    solve(matrix_second);
}