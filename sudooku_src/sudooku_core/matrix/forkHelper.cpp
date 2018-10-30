//
// Created by Borbély László on 2018. 10. 02..
//

#include "forkHelper.h"

/**
 * Initialize class
 * The fork length is set to a value greater than the greatest number of possible values in the field
 * This is necessary to ensure 100% functionality
 * @param matrix_
 */
ForkHelper::ForkHelper(Matrix *matrix_) : matrix(matrix_) {
    this->forkLength = static_cast<unsigned short int>(matrix->getDimension() + 1);

    /* Find the best position for forking the matrix */
    init();
}

/**
 * Every time an element is changed in the Matrix, this function must be called
 * The function calculates the best forking position based on the new state of the Matrix
 * Note that luckily the whole Matrix doesn't have to be recalculated every time, it's enough if we only check
 * the latest change
 * @param coordinates
 */
void ForkHelper::notify(std::pair<unsigned short int, unsigned short int> const &coordinates) {
    /* Getting the size of possible values vector at the changed position */
    auto potentialValuesSize = static_cast<unsigned short int>((*matrix)[coordinates].getPossibleValues().size());

    /* If the number of elements equals 1, unfortunately we have to look for another place to fork
     * This involves rescanning the whole Matrix */
    if (potentialValuesSize <= 1) {
        forkLength = static_cast<unsigned short int>(matrix->getDimension() + 1);
        init();
    } else if (potentialValuesSize < forkLength) {
        /* Otherwise we just check one coordinate */
        forkLength = potentialValuesSize;
        forkCoordinates = coordinates;
    }
}

/**
 * Initializing class
 * Iterates through all the elements and imitates changes
 */
void ForkHelper::init() {
    auto dimension = matrix->getDimension();

    for (unsigned short int x = 1; x <= dimension; ++x) {
        for (unsigned short int y = 1; y <= dimension; ++y) {

            /* We have to make sure that the length of vector isn't one, otherwise we get stuck in an
             * infinite loop */
            if ((*matrix)[{x, y}].getPossibleValues().size() > 1) {
                notify({x, y});
            }
        }
    }
}

/**
 * The most important function of the class
 * This is responsible for executing the fork operation. It involves two Matrices, the one for it holds a pointer
 * and another one which is returned.
 * @return
 */
Matrix ForkHelper::fork() {
    /* Make a copy of the pointed Matrix */
    Matrix matrix_second = Matrix{(*this->matrix)};

    /* Fix the value on the first one and remove it on the second one */
    (*this->matrix)[forkCoordinates].fixValue();
    matrix_second[forkCoordinates].removeValue();

    /* Notify changes on both Matrix's ForkHelper */
    this->matrix->notifyChangeAt(forkCoordinates);
    matrix_second.notifyChangeAt(forkCoordinates);

    return matrix_second;
}