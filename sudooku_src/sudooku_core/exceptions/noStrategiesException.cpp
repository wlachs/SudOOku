//
// Created by Borbély László on 2018. 10. 25..
//

#include "noStrategiesException.h"

/**
 * Should be thrown when the user wants to start the solver function before
 * specifying the SolvingStrategies
 * @return exception description
 */
const char *NoStrategiesException::what() const noexcept {
    return "No strategies specified!";
}

