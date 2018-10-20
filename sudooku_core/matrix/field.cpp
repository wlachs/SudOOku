//
// Created by Borbély László on 2018. 09. 15..
//

#include "field.h"
#include "matrix.h"
#include <algorithm>

Field::Field(std::vector<unsigned short int> const &possibleValues) {
    this->possibleValues = possibleValues;
}

Field::Field(unsigned short int value) {
    possibleValues.push_back(value);
}

Field::Field(Field const &other) {
    possibleValues = other.possibleValues;
}

Field &Field::operator=(Field const &other) = default;

void Field::setPossibleValues(std::vector<unsigned short int> &possibleValues) {
    this->possibleValues = possibleValues;
}

std::vector<unsigned short int> const &Field::getPossibleValues() const {
    return possibleValues;
}

void Field::fixValue() {
    auto value = possibleValues[0];
    possibleValues.clear();
    possibleValues.push_back(value);
}

void Field::fixValue(unsigned short int value) {
    possibleValues.clear();
    possibleValues.push_back(value);
}

void Field::removeValue() {
    possibleValues.erase(std::begin(possibleValues));
}

bool Field::removeValue(unsigned short int value) {
    auto it = std::find(std::begin(possibleValues), std::end(possibleValues), value);

    if (it != std::end(possibleValues)) {
        possibleValues.erase(it);
        return true;
    }

    return false;
}

bool Field::contains(unsigned short const int value) const {
    auto begin = std::begin(possibleValues);
    auto end = std::end(possibleValues);
    return std::find(begin, end, value) != end;
}