//
// Created by Borbély László on 2018. 10. 24..
//

#include <exceptions/noMatrixProvidedException.h>
#include <exceptions/wrongEventTypeException.h>
#include "fileOutputHandler.h"

/**
 * Save output file name
 * @param fileName
 */
FileOutputHandler::FileOutputHandler(std::string const &fileName) : solutionsFileName(fileName) {
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
        case RUN_START:
            solutionsFile.open(solutionsFileName);
            break;

        case SOLUTION:
            if (matrix != nullptr) {
                printMatrixToFile->print(*matrix);
            } else {
                throw NoMatrixProvidedException{};
            }
            break;

        case RUN_END:
            solutionsFile.close();
            break;

        default:
            throw WrongEventTypeException{};
    }
}

/**
 * Delete PrintMatrixToFile object
 */
FileOutputHandler::~FileOutputHandler() {
    delete printMatrixToFile;
}
