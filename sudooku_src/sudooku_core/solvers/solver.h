//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVER_H
#define SUDOOKU_SOLVER_H

#include <sudooku_core/matrix/matrix.h>
#include <sudooku_core/strategies/solvingStrategy.h>

/**
 * Class for solving the puzzle
 * It is possible to register several SolvingStrategies thus making the class much more flexible to future changes
 */
class Solver {
private:
    Matrix initialMatrix;
    unsigned short int dimension{};
    std::vector<SolvingStrategy *> strategies;
    std::vector<Matrix> solutions;

    void solve(Matrix &);

    bool isValid(Matrix const &) const;

    bool hasNoPotentialValues(Matrix const &) const;

    void optimize(Matrix &) const;

    bool isSolution(Matrix const &) const;

public:
    Solver() = default;

    void setInitialMatrix(Matrix const &);

    void setRules(std::vector<SolvingStrategy *> const &);

    void addRule(SolvingStrategy *);

    void solve();

    std::vector<Matrix> const &getSolutions() const;
};


#endif //SUDOOKU_SOLVER_H
