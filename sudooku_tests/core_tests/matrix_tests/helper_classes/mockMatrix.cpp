//
// Created by Borbély László on 2018. 10. 21..
//

#include "mockMatrix.h"

/**
 * Operator[] of MockMatrix
 * Only needed because overloading operators in GoogleMock isn't possible otherwise
 * @param arg
 * @return
 */
Field &MockMatrix::operator[](std::pair<unsigned short int, unsigned short int> const &arg) {
    return at(arg);
}

/**
 * Const Operator[] of MockMatrix
 * Only needed because overloading operators in GoogleMock isn't possible otherwise
 * @param arg
 * @return
 */
Field const &MockMatrix::operator[](std::pair<unsigned short int, unsigned short int> const &arg) const {
    return at_const(arg);
}