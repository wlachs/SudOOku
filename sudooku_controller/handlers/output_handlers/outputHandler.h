//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_OUTPUTHANDLER_H
#define SUDOOKU_OUTPUTHANDLER_H

#include <matrix/matrix.h>
#include <sudookuEvents.h>

class OutputHandler {
public:
    OutputHandler() = default;

    virtual ~OutputHandler() = default;

    virtual void notifyEvent(SudookuEvent, const Matrix *) = 0;
};

#endif //SUDOOKU_OUTPUTHANDLER_H
