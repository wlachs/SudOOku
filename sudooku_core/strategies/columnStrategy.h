//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_COLUMNSTRATEGY_H
#define SUDOOKU_COLUMNSTRATEGY_H

#include "solvingStrategy.h"

class ColumnStrategy : public SolvingStrategy {
private:
    const Matrix *constMatrix;
    Matrix *matrix;
    unsigned short int row;
    unsigned short int column;
    unsigned short int dimension;

    bool isColumnValid();

    bool simplifyColumn();

    bool optimizeSingular(std::vector<unsigned short int> const &);

    bool optimizeUnique(std::vector<unsigned short int> const &);

    bool recursiveRemove(unsigned short int, short int, unsigned short int);

    bool isUniqueInColumn(unsigned short int) const;

public:
    bool validate(Matrix const &) override;

    bool simplify(Matrix &) override;

    virtual ~ColumnStrategy() = default;
};

#endif //SUDOOKU_COLUMNSTRATEGY_H