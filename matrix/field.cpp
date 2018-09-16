//
// Created by Borbély László on 2018. 09. 15..
//

#include "field.h"
#include "matrix.h"

Field::Field(Matrix &matrix, unsigned short int dimension,
             std::pair<unsigned short int, unsigned short int> coordinates) {
    this->matrix = &matrix;
    this->coordinates = coordinates;

    for (unsigned short int i = 1; i <= dimension; ++i) {
        possibleValues.push_back(i);
    }
}

Field::Field(unsigned short int value) {
    possibleValues.push_back(value);
}

Field::Field(Field const &other) {
    matrix = other.matrix;
    possibleValues = other.possibleValues;
}

Field &Field::operator=(Field const &other) = default;

std::vector<unsigned short int> &Field::getPossibleValues() {
    return possibleValues;
}

void Field::fixValue(unsigned short int value) {
    possibleValues.clear();
    possibleValues.push_back(value);
}

void Field::removeValue(unsigned short int value) {
    auto it = std::find(std::begin(possibleValues), std::end(possibleValues), value);

    if (it != std::end(possibleValues)) {
        possibleValues.erase(it);
    }
}

bool Field::isFixed() const {
    return possibleValues.size() == 1;
}

void Field::setMatrix(Matrix &matrix) {
    this->matrix = &matrix;
}

void Field::setCoordinates(std::pair<unsigned short int, unsigned short int> coordinates) {
    this->coordinates = coordinates;
}