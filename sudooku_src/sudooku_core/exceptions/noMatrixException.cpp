//
// Created by Borbély László on 2018. 11. 08..
//

#include "noMatrixException.h"

const char *NoMatrixException::what() const noexcept {
    return "No initial Matrix provided!";
}