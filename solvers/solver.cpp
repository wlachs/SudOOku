//
// Created by Borbély László on 2018. 09. 15..
//

#include "solver.h"

void Solver::setInitialMatrix(Matrix &matrix) {
    initialMatrix = matrix;
}

void Solver::addRule(const SolvingStrategy *solvingStrategy) {
    strategies.push_back(solvingStrategy);
}

void Solver::solve() {
    solve(initialMatrix);
}

std::vector<Matrix> const &Solver::getSolutions() const {
    return solutions;
}

// TODO: make it constref
bool Solver::hasNoPotentialValues(Matrix &matrix) const {
    auto dimension = matrix.getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            if (matrix[{x, y}].getPossibleValues().size() == 0) {
                return true;
            }
        }
    }

    return false;
}

// TODO: make it constref
bool Solver::isValid(Matrix &matrix) const {
    if (hasNoPotentialValues(matrix)) {
        return false;
    }

    for (auto strategy : strategies) {
        if (!strategy->validate(matrix)) {
            return false;
        }
    }

    return true;
}

void Solver::optimize(Matrix &matrix) const {
    bool shouldReRun = false;

    auto dimension = matrix.getDimension();
    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            if (optimizeField(matrix, {x, y})) {
                shouldReRun = true;
            }
        }
    }

    if (shouldReRun) {
        optimize(matrix);
    }
}

bool Solver::optimizeField(Matrix &matrix, std::pair<unsigned short int, unsigned short int> const &coords) const {
    std::vector<unsigned short int> possibleValues = matrix[coords].getPossibleValues();
    bool result = false;

    if (possibleValues.size() <= 1) {
        return result;
    }

    for (auto value : matrix[coords].getPossibleValues()) {
        matrix[coords].fixValue(value);
        if (!isValid(matrix)) {
            auto it = std::find(std::begin(possibleValues), std::end(possibleValues), value);
            possibleValues.erase(it);
            result = true;
        }
    }

    matrix[coords].getPossibleValues() = possibleValues;

    return result;
}

// TODO: make it constref
bool Solver::isSolution(Matrix &matrix) const {
//  Solution if valid and in every cell there's only one number
    auto dimension = matrix.getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            if (matrix[{x, y}].getPossibleValues().size() != 1) {
                return false;
            }
        }
    }

    return true;
}

// TODO: doesn't have to be constref, can be used as first or second
std::pair<Matrix, Matrix> Solver::fork(Matrix &matrix_first) const {
    auto matrix_second = matrix_first.clone();

//  Where to fork?
//  At the field where the number of possible values is the lowest but not less than 2
    std::pair<unsigned short int, unsigned short int> minCoordinates = {1, 1};
    unsigned long minSize = matrix_first.getDimension() + 1;

    for (unsigned short int x = 1; x <= matrix_first.getDimension(); ++x) {
        for (unsigned short int y = 1; y <= matrix_first.getDimension(); ++y) {
            auto currentSize = matrix_first[{x, y}].getPossibleValues().size();
            if (currentSize < minSize && currentSize > 1) {
                minSize = currentSize;
                minCoordinates = {x, y};
            }
        }
    }

    matrix_first[minCoordinates].fixValue();
    matrix_second[minCoordinates].removeValue();

    return {matrix_first, matrix_second};
}

void Solver::solve(Matrix &matrix) {
//  1. Simplify the matrix according to the known strategies
    optimize(matrix);

//  2. Is it still valid?
    if (!isValid(matrix)) {
        return;
    }

//  3. Is the current matrix a valid solution? If yes, add to solutions list.
    if (isSolution(matrix)) {
        solutions.push_back(matrix);
        return;
    }

//  4. Fork the matrix somehow
    auto forked = fork(matrix);

//  5. Repeat
    solve(forked.first);
    solve(forked.second);
}