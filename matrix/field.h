//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_FIELD_H
#define SUDOOKU_FIELD_H


#include <set>
#include <iostream>

class Matrix;

class Field {
public:
    Matrix *matrix = nullptr;
    std::set<unsigned short int> possibleValues = {};

public:
    Field(Matrix &, unsigned short int);

    Field(unsigned short int);

    Field() = default;

    Field(Field const &);

    Field &operator=(Field const &);

    std::set<unsigned short int> const &getPossibleValues();

    void fixValue(unsigned short int);

    void removeValue(unsigned short int);

    bool isFixed() const;

    void setMatrix(Matrix &);
};


#endif //SUDOOKU_FIELD_H
