//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_SUDOOKUCONTROLLER_H
#define SUDOOKU_SUDOOKUCONTROLLER_H

#include <handlers/input_handlers/inputHandler.h>
#include <handlers/output_handlers/outputHandler.h>

class SudookuController {
public:
    SudookuController(InputHandler *, OutputHandler *);
    void run();
};

#endif //SUDOOKU_SUDOOKUCONTROLLER_H
