//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_TRIVIALSTRATEGY_H
#define SUDOOKU_TRIVIALSTRATEGY_H


#include "solvingStrategy.h"

class RowStrategy : public SolvingStrategy {
public:
    RowStrategy() = default;

    virtual bool validate(Matrix const &matrix) const;
};


#endif //SUDOOKU_TRIVIALSTRATEGY_H
