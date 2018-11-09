//
// Created by Borbély László on 2018. 11. 08..
//

#include "fieldDoesntContainValueException.h"

const char *FieldDoesntContainValueException::what() const noexcept {
    return "Field doesn't contain passed value!";
}
