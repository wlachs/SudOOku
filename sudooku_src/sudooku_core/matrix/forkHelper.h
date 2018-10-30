//
// Created by Borbély László on 2018. 10. 02..
//

#ifndef SUDOOKU_FORKHELPER_H
#define SUDOOKU_FORKHELPER_H

#include "matrix.h"

class Matrix;

/**
 * Class to help deciding at which position the Matrix should be forked
 */
class ForkHelper {
private:
    Matrix *matrix;
    std::pair<unsigned short int, unsigned short int> forkCoordinates;
    unsigned short int forkLength;

    void init();

public:
    explicit ForkHelper(Matrix *);

    void notify(std::pair<unsigned short int, unsigned short int> const &);

    Matrix fork();
};

#endif //SUDOOKU_FORKHELPER_H
