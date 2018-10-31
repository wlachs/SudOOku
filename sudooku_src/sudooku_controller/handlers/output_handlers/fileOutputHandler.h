//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_FILEOUTPUTHANDLER_H
#define SUDOOKU_FILEOUTPUTHANDLER_H

#include "outputHandler.h"
#include <string>
#include <fstream>
#include <sudooku_visual/print_matrix_to_file/printMatrixToFile.h>

/**
 * OutputHandler implementation for File outputs
 */
class FileOutputHandler : public OutputHandler {
private:
    std::string solutionsFileName{};
    std::ofstream solutionsFile{};
    PrintMatrixToFile *printMatrixToFile;

public:
    explicit FileOutputHandler(std::string const &);

    ~FileOutputHandler() override;

    void notifyEvent(SudookuEvent, const Matrix *) override;
};

#endif //SUDOOKU_FILEOUTPUTHANDLER_H
