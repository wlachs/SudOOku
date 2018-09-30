//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVINGSTRATEGY_H
#define SUDOOKU_SOLVINGSTRATEGY_H

#include "../matrix/field.h"

class SolvingStrategy {
public:
    SolvingStrategy();

    virtual bool validate(Matrix const &matrix) = 0;
};


#endif //SUDOOKU_SOLVINGSTRATEGY_H
