//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_OUTPUTHANDLER_H
#define SUDOOKU_OUTPUTHANDLER_H

#include <sudooku_core/matrix/matrix.h>
#include <sudooku_controller/sudookuEvents.h>

/**
 * Abstract class interface responsible for handling the output of the application
 */
class OutputHandler {
public:
    OutputHandler() = default;

    virtual ~OutputHandler() = default;

    virtual void notifyEvent(SudookuEvent, const Matrix *) = 0;
};

#endif //SUDOOKU_OUTPUTHANDLER_H
