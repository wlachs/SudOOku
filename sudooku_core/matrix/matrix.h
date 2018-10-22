//
// Created by Borbély László on 2018. 09. 15..
//

#ifndef SUDOOKU_MATRIX_H
#define SUDOOKU_MATRIX_H

#include <map>
#include <iostream>
#include "field.h"
#include "forkHelper.h"

class ForkHelper;

class Matrix {
private:
    unsigned short int dimension;

    ForkHelper *forkHelper = nullptr;

    std::map<std::pair<unsigned short int, unsigned short int>, Field> fields;

    void populateEmptyFields();
public:
    Matrix() = default;

    Matrix(Matrix const &);

    Matrix(unsigned short int, std::map<std::pair<unsigned short int, unsigned short int>, Field> const &);

    Matrix &operator=(Matrix const &);

    virtual ~Matrix();

    virtual Field &operator[](std::pair<unsigned short int, unsigned short int> const &);

    virtual Field const &operator[](std::pair<unsigned short int, unsigned short int> const &) const;

    virtual unsigned short int getDimension() const;

    virtual Matrix forkFirstReturnSecond();

    virtual void notifyChangeAt(std::pair<unsigned short int, unsigned short int> const &);
};

std::ostream &operator<<(std::ostream &os, Matrix const &);


#endif //SUDOOKU_MATRIX_H
