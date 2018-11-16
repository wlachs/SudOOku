//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_SUDOOKUCONTROLLER_H
#define SUDOOKU_SUDOOKUCONTROLLER_H

#include <sudooku_controller/handlers/input_handlers/inputHandler.h>
#include <sudooku_controller/handlers/output_handlers/outputHandler.h>
#include <sudooku_core/solvers/solver.h>

/**
 * Controller class to implement MVC architecture.
 * Operates with Model (Core) functions and forwards the results to the View
 */
class SudookuController {
private:
    InputHandler *inputHandler = nullptr;
    OutputHandler *outputHandler = nullptr;
    Solver *solver = nullptr;
    std::vector<SolvingStrategy *> rules = {};

    void initializeSolver();

    void runOne();

public:
    SudookuController(InputHandler *, OutputHandler *, Solver *);

    ~SudookuController() = default;

    void run();
};

#endif //SUDOOKU_SUDOOKUCONTROLLER_H
