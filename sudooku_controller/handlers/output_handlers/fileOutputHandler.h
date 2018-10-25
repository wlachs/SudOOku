//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_FILEOUTPUTHANDLER_H
#define SUDOOKU_FILEOUTPUTHANDLER_H

#include "outputHandler.h"
#include <string>
#include <fstream>
#include <print_matrix_to_file/printMatrixToFile.h>

class FileOutputHandler : public OutputHandler {
private:
    std::string solutionsFileName{};
    std::ofstream solutionsFile{};
    PrintMatrixToFile *printMatrixToFile;

public:
    FileOutputHandler(std::string const &);

    virtual ~FileOutputHandler();

    virtual void notifyEvent(SudookuEvent, const Matrix *);
};

#endif //SUDOOKU_FILEOUTPUTHANDLER_H
