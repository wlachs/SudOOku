#include <utility>

//
// Created by Borbély László on 2018. 09. 15..
//

#include "matrix.h"
#include <vector>

Matrix::Matrix(Matrix const &matrix) {
    dimension = matrix.dimension;
    fields = matrix.fields;
    forkHelper = new ForkHelper{this};
}

void Matrix::populateEmptyFields() {
    std::vector<unsigned short int> allValues = {};

    for (unsigned short int i = 1; i <= dimension; ++i) {
        allValues.push_back(i);
    }

    for (unsigned short int row = 1; row <= dimension; ++row) {
        for (unsigned short int column = 1; column <= dimension; ++column) {
            if (fields.find(std::pair<unsigned short int, unsigned short int>(row, column)) == fields.end()) {
                fields[{row, column}] = Field(allValues);
            }
        }
    }
}

Matrix::Matrix(unsigned short const int dimension,
               std::map<std::pair<unsigned short int, unsigned short int>, Field> const &fields) {
    this->dimension = dimension;
    this->fields = fields;
    populateEmptyFields();
    this->forkHelper = new ForkHelper{this};
}

Matrix &Matrix::operator=(Matrix const &matrix) {
    delete forkHelper;
    dimension = matrix.dimension;
    fields = matrix.fields;
    forkHelper = new ForkHelper{this};

    return *this;
}

Matrix::~Matrix() {
    delete forkHelper;
}

unsigned short int Matrix::getDimension() const {
    return dimension;
}

Field &Matrix::operator[](std::pair<unsigned short int, unsigned short int> const &coordinates) {
    return fields.at(coordinates);
}

Field const &Matrix::operator[](std::pair<unsigned short int, unsigned short int> const &coordinates) const {
    return fields.at(coordinates);
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

Matrix Matrix::forkFirstReturnSecond() {
    return forkHelper->fork();
}

void Matrix::notifyChangeAt(std::pair<unsigned short int, unsigned short int> const &coordinates) {
    forkHelper->notify(coordinates);
}