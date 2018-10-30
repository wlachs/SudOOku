//
// Created by Borbély László on 2018. 10. 30..
//

#include "wrongEventTypeException.h"

/**
 * Exception description for the case when the SudookuEvent passed to the OutputHandler
 * object is incorrect
 * @return exception description
 */
const char *WrongEventTypeException::what() const noexcept {
    return "Undefined SudookuEvent!";
}
