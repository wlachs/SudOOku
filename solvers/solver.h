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
    unsigned short int dimension;
    std::vector<const SolvingStrategy *> strategies;
    std::vector<Matrix> solutions;

    void solve(Matrix &);

    bool isValid(Matrix const &) const;

    bool hasNoPotentialValues(Matrix const &) const;

    void optimize(Matrix &) const;

    bool optimizeField(Matrix &, std::pair<unsigned short int, unsigned short int> const &) const;

    bool isSolution(Matrix const &) const;

    std::pair<Matrix, Matrix> fork(Matrix &) const;
public:
    Solver() = default;

    void setInitialMatrix(Matrix &);

    void addRule(const SolvingStrategy *);

    void solve();

    std::vector<Matrix> const &getSolutions() const;
};


#endif //SUDOOKU_SOLVER_H
