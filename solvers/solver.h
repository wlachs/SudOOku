//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVER_H
#define SUDOOKU_SOLVER_H


#include "../matrix/matrix.h"
#include "../strategies/solvingStrategy.h"

class Solver {
protected:
    Matrix initialMatrix;
    std::vector<SolvingStrategy *> strategies;
public:
    Solver(Matrix &);

    std::vector<Matrix> solve(Matrix);
};


#endif //SUDOOKU_SOLVER_H
