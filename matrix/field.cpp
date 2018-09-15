//
// Created by Borbély László on 2018. 09. 15..
//

#include "field.h"
#include "matrix.h"

Field::Field(Matrix &matrix, unsigned short int dimension) {
    this->matrix = &matrix;

    for (unsigned short int i = 1; i <= dimension; ++i) {
        possibleValues.insert(i);
    }
}

Field::Field(unsigned short int value) {
    possibleValues.insert(value);
}

Field::Field(Field const &other) {
    matrix = other.matrix;
    possibleValues = other.possibleValues;
}

Field &Field::operator=(Field const &other) = default;

std::set<unsigned short int> const &Field::getPossibleValues() {
    return possibleValues;
}

void Field::fixValue(unsigned short int value) {
    possibleValues.clear();
    possibleValues.insert(value);
    matrix->validateMatrix();
}

void Field::removeValue(unsigned short int value) {
    possibleValues.erase(value);
    matrix->validateMatrix();
}

bool Field::isFixed() const {
    return possibleValues.size() == 1;
}

void Field::setMatrix(Matrix &matrix) {
    this->matrix = &matrix;
}