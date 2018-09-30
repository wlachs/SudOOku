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

bool Solver::isValid(Matrix const &matrix) const {
    for (unsigned int i = 0; i < strategies.size(); ++i) {
        if (!strategies[i]->validate(matrix)) {
            return false;
        }
    }

    return true;
}

bool Solver::isSolution(Matrix const &) const {
    return false;
}

std::pair<Matrix, Matrix> Solver::fork(Matrix const &) const {
    return {};
}

void Solver::solve(Matrix matrix) {
//  1. Is the matrix valid? If not, stop.
//    if (!isValid(matrix)) {
//        return;
//    }

//  2. Is the current matrix a valid solution? If yes, add to solutions list.
//    if (isSolution(matrix)) {
//        solutions.push_back(matrix);
//        return;
//    }

//  3. Fork the matrix somehow
//    auto forked = fork(matrix);

//  4. Repeat
//    solve(forked.first);
//    solve(forked.second);
}