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
    fields = std::move(init);
    populateEmptyFields();
}

std::vector<Field *> Matrix::getListOfNontrivialFields() {
    std::vector<Field *> returns = {};

    for (auto it = std::begin(fields); it != std::end(fields); ++it) {
        if (!it->second.isFixed()) {
            returns.push_back(&it->second);
        }
    }

    return returns;
}

unsigned short int Matrix::getDimension() const {
    return dimension;
}

void Matrix::validateMatrix(std::pair<unsigned short int, unsigned short int> const &) {
    // TODO implement matrix validation
    std::cout << "validate";
}