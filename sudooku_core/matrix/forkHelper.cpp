//
// Created by Borbély László on 2018. 10. 02..
//

#include "forkHelper.h"

ForkHelper::ForkHelper(Matrix *matrix) : matrix(matrix) {
    this->forkLength = (unsigned short int) (matrix->getDimension() + 1);
    this->forkCoordinates = {1, 1};

    init();
}

void ForkHelper::notify(std::pair<unsigned short int, unsigned short int> const &coordinates) {
    auto potentialValuesSize = (unsigned short int) (*matrix)[coordinates].getPossibleValues().size();

    if (potentialValuesSize <= 1) {
        forkLength = (unsigned short int) (matrix->getDimension() + 1);
        init();
    } else if (potentialValuesSize < forkLength) {
        forkLength = potentialValuesSize;
        forkCoordinates = coordinates;
    }
}

void ForkHelper::init() {
    auto dimension = matrix->getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {
            if ((*matrix)[{x, y}].getPossibleValues().size() > 1) {
                notify({x, y});
            }
        }
    }
}

Matrix ForkHelper::fork() {
    Matrix matrix_second = Matrix{(*this->matrix)};

    (*this->matrix)[forkCoordinates].fixValue();
    matrix_second[forkCoordinates].removeValue();

    this->matrix->notifyChangeAt(forkCoordinates);
    matrix_second.notifyChangeAt(forkCoordinates);

    return matrix_second;
}