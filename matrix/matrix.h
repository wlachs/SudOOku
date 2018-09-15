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
    Matrix(unsigned short int, std::map<std::pair<unsigned short int, unsigned short int>, Field> &);

    Matrix clone() const;

    std::vector<Field> getListOfNontrivialFields() const;

    unsigned short int getDimension() const;

    void fixValue(Field &, unsigned short int);

    void removeValue(Field &, unsigned short int);

    void validateMatrix();
};


#endif //SUDOOKU_MATRIX_H
