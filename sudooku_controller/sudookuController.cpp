//
// Created by Borbély László on 2018. 10. 24..
//

#include "sudookuController.h"

/**
 * Initialize handlers and solver
 * @param inputHandler
 * @param outputHandler
 * @param solver
 */
SudookuController::SudookuController(InputHandler *inputHandler, OutputHandler *outputHandler, Solver *solver)
        : inputHandler(inputHandler), outputHandler(outputHandler), solver(solver) {}

/**
 * Should first receive input from any input handler
 * Then process the given input using a solver core function
 * Finally as the run terminates, notify the output handler
 *
 */
void SudookuController::run() {
    // Get input from the input handler and pass it to the solver
    initializeSolver();

    // Execute the solver function
    solver->solve();

    // Retrieve solutions
    auto const &solutions = solver->getSolutions();

    // Send solutions to output handler
    for (auto const &solution : solutions) {
        outputHandler->notifyEvent(SudookuEvent::SOLUTION, &solution);
    }

    // Notify output handler of the results
    outputHandler->notifyEvent(SudookuEvent::RUN_END, nullptr);
}

/**
 * Get an input matrix from the input handler
 * Set the matching solver rules
 */
void SudookuController::initializeSolver() {
    // Get the initial matrix
    Matrix const &inputMatrix = inputHandler->readInput();

    // Get solver rules
    rules = inputHandler->readRules();

    // Initialize solver
    solver->setInitialMatrix(inputMatrix);
    solver->setRules(rules);

    // Notify output handler
    outputHandler->notifyEvent(SudookuEvent::RUN_START, &inputMatrix);
}

/**
 * Delete manually allocated solving strategies
 */
SudookuController::~SudookuController() {
    for (auto &rule : rules) {
        delete rule;
        rule = nullptr;
    }
}
