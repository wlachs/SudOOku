//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_DIAGONALSTRATEGY_H
#define SUDOOKU_DIAGONALSTRATEGY_H

#include "solvingStrategy.h"

class DiagonalStrategy : public SolvingStrategy {
private:
    bool validateDirection1(Matrix const &, unsigned short int) const;

    bool validateDirection2(Matrix const &, unsigned short int) const;

public:
    bool validate(Matrix const &) const override;
};

#endif //SUDOOKU_DIAGONALSTRATEGY_H
