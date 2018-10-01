#include <utility>

//
// Created by Borbély László on 2018. 09. 15..
//

#include "matrix.h"

void Matrix::populateEmptyFields() {
    for (unsigned short int row = 1; row <= dimension; ++row) {
        for (unsigned short int column = 1; column <= dimension; ++column) {
            if (fields.find(std::pair<unsigned short int, unsigned short int>(row, column)) == fields.end()) {
                fields[{row, column}] = Field(*this, dimension, {row, column});
            } else {
                fields[{row, column}].setMatrix(*this);
                fields[{row, column}].setCoordinates({row, column});
            }
        }
    }
}

Matrix::Matrix(unsigned short int dimension, std::map<std::pair<unsigned short int, unsigned short int>, Field> init) {
    this->dimension = dimension;
    fields = init;
    populateEmptyFields();
}

unsigned short int Matrix::getDimension() const {
    return dimension;
}

Field &Matrix::operator[](std::pair<unsigned short int, unsigned short int> coordinates) {
    return fields.at(coordinates);
}

Field const &Matrix::operator[](std::pair<unsigned short int, unsigned short int> coordinates) const {
    return fields.at(coordinates);
}

Matrix Matrix::clone() const {
    return Matrix(dimension, fields);
}

std::ostream &operator<<(std::ostream &os, Matrix const &matrix) {
    unsigned short const int dimension = matrix.getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            auto possibleValues = matrix[{x, y}].getPossibleValues();

            if (possibleValues.size() == 1) {
                os << possibleValues[0] << " ";
            } else {
                os << "  ";
            }
        }

        os << std::endl;
    }

    return os;
}