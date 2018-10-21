//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_COLUMNSTRATEGY_H
#define SUDOOKU_COLUMNSTRATEGY_H

#include "solvingStrategy.h"

class ColumnStrategy : public SolvingStrategy {
private:
    bool isColumnValid(Matrix const &, unsigned short int, unsigned short int) const;

    bool simplifyColumn(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeSingular(Matrix &, unsigned short int, unsigned short int) const;

    bool optimizeUnique(Matrix &, unsigned short int, unsigned short int) const;

    bool recursiveRemove(Matrix &, unsigned short int, unsigned short int,
                         unsigned short int, short int, unsigned short int) const;

    bool isUniqueInColumn(Matrix const &, unsigned short int, unsigned short int, unsigned short int) const;

public:
    bool validate(Matrix const &) const override;

    bool simplify(Matrix &) const override;
};

#endif //SUDOOKU_COLUMNSTRATEGY_H
