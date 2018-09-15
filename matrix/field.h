//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_FIELD_H
#define SUDOOKU_FIELD_H


#include <set>
#include <iostream>

class Matrix;

class Field {
private:
    Matrix *matrix = nullptr;
    std::set<unsigned short int> possibleValues;

public:
    Field(Matrix &, unsigned short int);

    explicit Field(unsigned short int);

    std::set<unsigned short int> const &getPossibleValues();

    void fixValue(unsigned short int);

    void removeValue(unsigned short int);

    bool isFixed();
};


#endif //SUDOOKU_FIELD_H
