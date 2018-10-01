//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_MATRIX_H
#define SUDOOKU_MATRIX_H

#include <map>
#include <vector>
#include "field.h"

class Matrix {
private:
    unsigned short int dimension;

    std::map<std::pair<unsigned short int, unsigned short int>, Field> fields;

    void populateEmptyFields();
public:
    Matrix() = default;

    Matrix(unsigned short int, std::map<std::pair<unsigned short int, unsigned short int>, Field>);

    unsigned short int getDimension() const;

    Field &operator[](std::pair<unsigned short int, unsigned short int>);

    Field const &operator[](std::pair<unsigned short int, unsigned short int>) const;

    Matrix clone() const;
};

std::ostream &operator<<(std::ostream &os, Matrix const &);


#endif //SUDOOKU_MATRIX_H
