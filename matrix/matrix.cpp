//
// Created by Borbély László on 2018. 09. 15..
//

#include "matrix.h"

void Matrix::populateEmptyFields() {
    for (unsigned short int row = 1; row <= dimension; ++row) {
        for (unsigned short int column = 1; column <= dimension; ++column) {
            if (fields.find(std::pair<unsigned short int, unsigned short int>(row, column)) == fields.end()) {
                fields.at(std::pair<unsigned short int, unsigned short int>(row, column)) = Field(*this, dimension);
            }
        }
    }
}

Matrix::Matrix(unsigned short int dimension, std::map<std::pair<unsigned short int, unsigned short int>, Field> &init) {
    this->dimension = dimension;
    fields = init;
    populateEmptyFields();
}

Matrix Matrix::clone() const {
    // TODO implement matrix cloning
    return *this;
}

std::vector<Field> Matrix::getListOfNontrivialFields() const {
    std::vector<Field> returns;

    std::for_each(fields.begin(), fields.end(),
                  [&returns](std::pair<std::pair<unsigned short int, unsigned short int>, Field> field) {
                      if (field.second.isFixed()) {
                          returns.push_back(field.second);
                      }
                  }
    );

    return returns;
}

unsigned short int Matrix::getDimension() const {
    return dimension;
}

void Matrix::fixValue(Field &field, unsigned short int value) {
    field.fixValue(value);
}

void Matrix::removeValue(Field &field, unsigned short int value) {
    field.removeValue(value);
}

void Matrix::validateMatrix() {
    // TODO implement matrix validation
}