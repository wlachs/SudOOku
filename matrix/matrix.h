//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_MATRIX_H
#define SUDOOKU_MATRIX_H

#include <map>
#include "field.h"

class Matrix {
private:
    std::map<std::pair<unsigned short int, unsigned short int>, Field> fields;
public:
    Matrix(unsigned short int, std::map<std::pair<unsigned short int, unsigned short int>, Field> &);

    Matrix clone();

    std::vector<Field const &> getListOfNontrivialFields();

    unsigned short int getDimension();

    void fixValue(Field const &, unsigned short int);

    void removeValue(Field const &, unsigned short int);

    void validateMatrix();
};


#endif //SUDOOKU_MATRIX_H
