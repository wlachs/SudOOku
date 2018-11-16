//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_FILEINPUTHANDLER_H
#define SUDOOKU_FILEINPUTHANDLER_H

#include "inputHandler.h"
#include <sudooku_core/strategies/solvingStrategy.h>
#include <string>
#include <fstream>
#include <sudooku_visual/read_matrix_from_file/readMatrixFromFile.h>

/**
 * InputHandler implementation for File inputs
 */
class FileInputHandler : public InputHandler {
private:
    std::ifstream inputFile;
    ReadMatrixFromFile *readMatrixFromFile;
    std::vector<SolvingStrategy *> rules{};

public:
    explicit FileInputHandler(std::vector<SolvingStrategy *> const &, std::string const &);

    ~FileInputHandler() override;

    Matrix readInput() override;

    std::vector<SolvingStrategy *> const &readRules() override;

    bool hasInput() const override;
};

#endif //SUDOOKU_FILEINPUTHANDLER_H
