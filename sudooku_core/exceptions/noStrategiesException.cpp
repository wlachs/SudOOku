//
// Created by Borbély László on 2018. 10. 25..
//

#include "noStrategiesException.h"

const char *NoStrategiesException::what() const noexcept {
    return "No strategies specified!";
}

