//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_INPUTHANDLER_H
#define SUDOOKU_INPUTHANDLER_H

#include <matrix/matrix.h>
#include <strategies/solvingStrategy.h>
#include <vector>

class InputHandler {
public:
    InputHandler() = default;

    virtual ~InputHandler() = default;

    virtual Matrix readInput() = 0;

    virtual std::vector<SolvingStrategy *> readRules() = 0;
};

#endif //SUDOOKU_INPUTHANDLER_H
