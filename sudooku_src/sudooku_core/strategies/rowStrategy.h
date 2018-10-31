//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_ROWSTRATEGY_H
#define SUDOOKU_ROWSTRATEGY_H

#include "solvingStrategy.h"

/**
 * A SolvingStrategy to ensure there is exactly one instance of every possible value in each row of the Matrix
 */
class RowStrategy : public SolvingStrategy {
private:
    const Matrix *constMatrix{};
    Matrix *matrix{};
    unsigned short int row{};
    unsigned short int column{};
    unsigned short int dimension{};

    bool isRowValid();

    bool simplifyRow();

    bool optimizeSingular(std::vector<unsigned short int> const &) const;

    bool optimizeUnique(std::vector<unsigned short int> const &) const;

    bool recursiveRemove(unsigned short int, short int, unsigned short int) const;

    bool isUniqueInRow(unsigned short int) const;

public:
    RowStrategy() = default;

    bool validate(Matrix const &) override;

    bool simplify(Matrix &) override;

    ~RowStrategy() override = default;
};

#endif //SUDOOKU_ROWSTRATEGY_H