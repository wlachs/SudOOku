//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVER_H
#define SUDOOKU_SOLVER_H


#include "../matrix/matrix.h"
#include "../strategies/solvingStrategy.h"

class Solver {
protected:
    Matrix matrix;
    SolvingStrategy *solvingStrategy;
public:
    Solver(Matrix, SolvingStrategy *);

    virtual std::vector<Matrix> solve() = 0;
};


#endif //SUDOOKU_SOLVER_H
