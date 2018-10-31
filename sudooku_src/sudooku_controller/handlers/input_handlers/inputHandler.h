//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_INPUTHANDLER_H
#define SUDOOKU_INPUTHANDLER_H

#include <sudooku_core/matrix/matrix.h>
#include <sudooku_core/strategies/solvingStrategy.h>
#include <vector>

/**
 * Abstract class interface responsible for handling the input of the application
 */
class InputHandler {
public:
    InputHandler() = default;

    virtual ~InputHandler() = default;

    virtual Matrix readInput() = 0;

    virtual std::vector<SolvingStrategy *> readRules() = 0;
};

#endif //SUDOOKU_INPUTHANDLER_H
