//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_DIAGONALSTRATEGY_H
#define SUDOOKU_DIAGONALSTRATEGY_H

#include "solvingStrategy.h"

/**
 * A SolvingStrategy to ensure there is exactly one instance of every possible value in the diagonal of the Matrix
 */
class DiagonalStrategy : public SolvingStrategy {
private:
    const Matrix *constMatrix{};
    unsigned short int dimension{};

    bool validateInDirection(bool) const;

public:
    DiagonalStrategy() = default;

    bool validate(Matrix const &) override;

    ~DiagonalStrategy() override = default;
};

#endif //SUDOOKU_DIAGONALSTRATEGY_H
