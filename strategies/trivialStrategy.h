//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_TRIVIALSTRATEGY_H
#define SUDOOKU_TRIVIALSTRATEGY_H


#include "solvingStrategy.h"

class TrivialStrategy : public SolvingStrategy {
public:
    TrivialStrategy() = default;

    virtual Field const &selectField(Matrix const &);

    virtual unsigned short int selectValue(Field const &);
};


#endif //SUDOOKU_TRIVIALSTRATEGY_H
