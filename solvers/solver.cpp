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

void Solver::solve(Matrix matrix) {
    // 1. Is the matrix valid? If not, stop.
    // 2. Is the current matrix a valid solution? If yes, add to solutions list.
    // 3. Fork the matrix somehow
    // 4. Repeat
}