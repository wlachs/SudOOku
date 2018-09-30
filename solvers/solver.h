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
    std::vector<Matrix> solutions;

    void solve(Matrix);
public:
    Solver(Matrix &);

    void addRule(SolvingStrategy *);

    void solve();

    std::vector<Matrix> const &getSolutions();
};


#endif //SUDOOKU_SOLVER_H
