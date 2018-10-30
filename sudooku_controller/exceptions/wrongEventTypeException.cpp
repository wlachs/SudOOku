//
// Created by Borbély László on 2018. 10. 30..
//

#include "wrongEventTypeException.h"

const char *WrongEventTypeException::what() const noexcept {
    return "Undefined SudookuEvent!";
}
