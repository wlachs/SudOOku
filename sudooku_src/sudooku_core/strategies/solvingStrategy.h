//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_SOLVINGSTRATEGY_H
#define SUDOOKU_SOLVINGSTRATEGY_H

#include <sudooku_core/matrix/field.h>
#include <sudooku_core/matrix/matrix.h>

class SolvingStrategy {
public:
    SolvingStrategy() = default;

    virtual bool validate(Matrix const &) = 0;

    virtual bool simplify(Matrix &) { return false; };

    virtual ~SolvingStrategy() {}
};


#endif //SUDOOKU_SOLVINGSTRATEGY_H
