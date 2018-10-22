//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_ROWSTRATEGY_H
#define SUDOOKU_ROWSTRATEGY_H

#include "solvingStrategy.h"

class RowStrategy : public SolvingStrategy {
private:
    const Matrix *constMatrix;
    Matrix *matrix;
    unsigned short int row, column, dimension;

    bool isRowValid();

    bool simplifyRow();

    bool optimizeSingular(std::vector<unsigned short int> const &) const;

    bool optimizeUnique(std::vector<unsigned short int> const &) const;

    bool recursiveRemove(unsigned short int, short int, unsigned short int) const;

    bool isUniqueInRow(unsigned short int) const;

public:
    bool validate(Matrix const &) override;

    bool simplify(Matrix &) override;
};

#endif //SUDOOKU_ROWSTRATEGY_H