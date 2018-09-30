//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVINGSTRATEGY_H
#define SUDOOKU_SOLVINGSTRATEGY_H

#include "../matrix/field.h"

class SolvingStrategy {
public:
    SolvingStrategy() = default;

    virtual bool validate(Matrix const &) const = 0;
};


#endif //SUDOOKU_SOLVINGSTRATEGY_H
