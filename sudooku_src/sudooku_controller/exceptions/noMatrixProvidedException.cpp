//
// Created by Borbély László on 2018. 10. 25..
//

#include "noMatrixProvidedException.h"

const char *NoMatrixProvidedException::what() const noexcept {
    return "No matrix provided to notify function!";
}
