//
// Created by Borbély László on 2018. 09. 15..
//

#include "solver.h"

Solver::Solver(Matrix matrix, SolvingStrategy *solvingStrategy) {
    this->matrix = matrix;
    this->solvingStrategy = solvingStrategy;
}