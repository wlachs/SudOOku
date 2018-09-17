//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVINGSTRATEGY_H
#define SUDOOKU_SOLVINGSTRATEGY_H

#include "../matrix/field.h"

class SolvingStrategy {
public:
    SolvingStrategy();

    virtual Field const &selectField(Matrix const &) = 0;

    virtual unsigned short int selectValue(Field const &) = 0;
};


#endif //SUDOOKU_SOLVINGSTRATEGY_H
