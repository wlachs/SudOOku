//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_FIELD_H
#define SUDOOKU_FIELD_H


#include <set>
#include <iostream>
#include "matrix.h"

class Field {
private:
    Matrix const &matrix;
    std::set<unsigned short int> possibleValues;

public:
    Field(Matrix const &, unsigned short int);

    std::set<unsigned short int> &getPossibleValues();

    void fixValue(unsigned short int);

    void removeValue(unsigned short int);
};


#endif //SUDOOKU_FIELD_H
