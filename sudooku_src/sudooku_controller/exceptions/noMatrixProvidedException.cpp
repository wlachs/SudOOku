//
// Created by Borbély László on 2018. 10. 25..
//

#include "noMatrixProvidedException.h"

/**
 * Exception description for the case when no *Matrix is passed to the OutputHandler
 * object on solution notification
 * @return exception description
 */
const char *NoMatrixProvidedException::what() const noexcept {
    return "No matrix provided to notify function!";
}
