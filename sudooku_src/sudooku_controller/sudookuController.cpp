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
SudookuController::SudookuController(InputHandler *inputHandler_, OutputHandler *outputHandler_, Solver *solver_)
        : inputHandler(inputHandler_), outputHandler(outputHandler_), solver(solver_) {}

/**
 * Initialize solver and execute until all puzzles from the input are solved
 */
void SudookuController::run() {
    /* Get input from the input handler and pass it to the solver */
    initializeSolver();

    /* Notify output handler */
    outputHandler->notifyEvent(SudookuEvent::RUN_START, nullptr);

    /* Run for each input received */
    while (inputHandler->hasInput()) {
        runOne();
    }

    /* Notify output handler of the results */
    outputHandler->notifyEvent(SudookuEvent::RUN_END, nullptr);
}

/**
 * Solve next puzzle from the input
 */
void SudookuController::runOne() {
    /* Get next puzzle */
    Matrix input = inputHandler->readInput();

    /* Notify output handler of new puzzle */
    outputHandler->notifyEvent(SudookuEvent::PUZZLE_START, &input);

    /* Set Solver initial Matrix */
    solver->setInitialMatrix(input);

    /* Execute the solver function */
    solver->solve();

    /* Retrieve solutions */
    auto const &solutions = solver->getSolutions();

    /* Send solutions to output handler */
    for (auto const &solution : solutions) {
        outputHandler->notifyEvent(SudookuEvent::SOLUTION, &solution);
    }

    /* Notify output handler of the end of puzzle execution */
    outputHandler->notifyEvent(SudookuEvent::PUZZLE_END, nullptr);
}

/**
 * Set the matching solver rules
 */
void SudookuController::initializeSolver() {
    /* Get solver rules */
    rules = inputHandler->readRules();

    /* Initialize solver */
    solver->setRules(rules);
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
