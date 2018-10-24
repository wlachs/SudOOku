//
// Created by Borbély László on 2018. 10. 21..
//

#include "mockMatrix.h"

Field &MockMatrix::operator[](std::pair<unsigned short int, unsigned short int> const &arg) {
    return at(arg);
}

Field const &MockMatrix::operator[](std::pair<unsigned short int, unsigned short int> const &arg) const {
    return at_const(arg);
}