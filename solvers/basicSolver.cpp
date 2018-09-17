//
// Created by Borbély László on 2018. 09. 15..
//

#include "../matrix/matrix.h"
#include "basicSolver.h"

BasicSolver::BasicSolver(Matrix matrix, SolvingStrategy *solvingStrategy) : Solver(matrix, solvingStrategy) {}

std::vector<Matrix> BasicSolver::solve() {
    return {};
}