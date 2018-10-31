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
 * In case of SudOOku::SOLUTION
 *  print solution to file
 * In case of SudOOku::RUN_END
 *  close output file
 */
void FileOutputHandler::notifyEvent(SudookuEvent event, const Matrix *matrix) {
    switch (event) {
        /* Always gets called as the execution starts in the Solver object.
         * Opens the output file */
        case RUN_START:
            solutionsFile.open(solutionsFileName);
            break;

            /* Should be called every time a solution is found.
             * The given Matrix object will be serialized */
        case SOLUTION:
            if (matrix != nullptr) {
                printMatrixToFile->print(*matrix);
            } else {
                throw NoMatrixProvidedException{};
            }
            break;

            /* Must be called as soon as the Solver finished the execution.
             * Closes the output file */
        case RUN_END:
            solutionsFile.close();
            break;

            /* All the other cases should result in an exception */
        default:
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
