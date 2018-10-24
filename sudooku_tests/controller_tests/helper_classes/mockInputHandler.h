//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_MOCKMATRIX_H
#define SUDOOKU_MOCKMATRIX_H

#include <handlers/input_handlers/inputHandler.h>
#include "gmock/gmock.h"

class MockInputHandler : public InputHandler {
public:
    MOCK_METHOD0(readInput, Matrix());
};

#endif //SUDOOKU_MOCKMATRIX_H