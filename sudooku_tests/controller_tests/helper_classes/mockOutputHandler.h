//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_MOCKOUTPUTHANDLER_H
#define SUDOOKU_MOCKOUTPUTHANDLER_H

#include <handlers/output_handlers/outputHandler.h>
#include "gmock/gmock.h"

class MockOutputHandler : public OutputHandler {
public:
    MOCK_METHOD2(notifyEvent, void(SudookuEvent,
            const Matrix *));
};

#endif //SUDOOKU_MOCKOUTPUTHANDLER_H
