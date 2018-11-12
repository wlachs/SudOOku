//
// Created by Borbély László on 2018. 10. 24..
//

#include <exceptions/noMatrixProvidedException.h>
#include <exceptions/wrongEventTypeException.h>
#include "fileOutputHandler.h"

/**
 * Save output file name and create serializer object
 * @param fileName
 */
FileOutputHandler::FileOutputHandler(std::string const &fileName) : solutionsFileName(fileName) {
    /* Allocate memory for Matrix printer */
    printMatrixToFile = new PrintMatrixToFile{solutionsFile};
}

/**
 * Handle events
 * In case of SudOOku::RUN_START
 *  open output file
 * In case of SudOOku::PUZZLE_START
 *  print header comment to file
 * In case of SudOOku::SOLUTION
 *  print solution to file
 * In case of SudOOku::PUZZLE_END
 *  print trailing comment to file
 * In case of SudOOku::RUN_END
 *  close output file
 */
void FileOutputHandler::notifyEvent(SudookuEvent event, const Matrix *matrix) {
    switch (event) {
        case RUN_START:
            /* Always gets called as the execution starts in the Solver object.
             * Opens the output file */
            solutionsFile.open(solutionsFileName);

            /* Reset puzzle counter */
            puzzleId = 1;

            break;

        case PUZZLE_START:
            /* Should be called when the Solver starts solving a puzzle */
            printMatrixToFile->printStart(puzzleId);

            /* Increment local puzzle counter */
            ++puzzleId;

            break;

        case SOLUTION:
            /* Should be called every time a solution is found.
             * The given Matrix object will be serialized */
            if (matrix != nullptr) {
                printMatrixToFile->print(*matrix);
            } else {
                throw NoMatrixProvidedException{};
            }

            break;

        case PUZZLE_END:
            /* Should be called when the Solver finishes solving a puzzle */
            printMatrixToFile->printEnd();

            break;

        case RUN_END:
            /* Must be called as soon as the Solver finished the execution.
             * Closes the output file */
            solutionsFile.close();

            break;

        default:
            /* All the other cases should result in an exception */
            throw WrongEventTypeException{};
    }
}

/**
 * Delete PrintMatrixToFile object
 */
FileOutputHandler::~FileOutputHandler() {
    /* Deallocation */
    delete printMatrixToFile;
}
