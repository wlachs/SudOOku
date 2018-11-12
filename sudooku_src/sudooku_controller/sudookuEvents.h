//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_SUDOOKUEVENTS_H
#define SUDOOKU_SUDOOKUEVENTS_H

/**
 * Event types for OutputHandler to determine behavior
 */
enum SudookuEvent {
    /* Should be called when the execution is started */
            RUN_START,

    /* Should be called when the execution of a specific puzzle is started */
            PUZZLE_START,

    /* Should be called when a solution is found */
            SOLUTION,

    /* Should be called when the execution of a specific puzzle is over */
            PUZZLE_END,

    /* Should be called when the execution is finished */
            RUN_END
};

#endif //SUDOOKU_SUDOOKUEVENTS_H
