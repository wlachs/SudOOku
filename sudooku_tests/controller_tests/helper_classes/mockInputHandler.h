//
// Created by Borbély László on 2018. 10. 21..
//

#ifndef SUDOOKU_MOCKINPUTHANDLER_H
#define SUDOOKU_MOCKINPUTHANDLER_H

#include <sudooku_controller/handlers/input_handlers/inputHandler.h>
#include "gmock/gmock.h"

/**
 * Mock class of InputHandler
 */
class MockInputHandler : public InputHandler {
public:
    MOCK_CONST_METHOD0(hasInput, bool());

    MOCK_METHOD0(readInput, Matrix());

    MOCK_METHOD0(readRules, std::vector<SolvingStrategy *>());
};

#endif //SUDOOKU_MOCKINPUTHANDLER_H