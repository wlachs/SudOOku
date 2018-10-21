//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_ROWSTRATEGY_H
#define SUDOOKU_ROWSTRATEGY_H

#include "solvingStrategy.h"

class RowStrategy : public SolvingStrategy {
private:
    bool simplifyRow(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeSingular(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeUnique(Matrix &, unsigned short int, unsigned short int) const;

    bool recursiveRemove(Matrix &, unsigned short int, unsigned short int,
                         unsigned short int, short int, unsigned short int) const;

    bool isUniqueInRow(Matrix const &, unsigned short int, unsigned short int, unsigned short int) const;

public:
    bool validate(Matrix const &) const override;

    bool simplify(Matrix &) const override;
};

#endif //SUDOOKU_ROWSTRATEGY_H
