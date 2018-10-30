//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_FILEINPUTHANDLER_H
#define SUDOOKU_FILEINPUTHANDLER_H

#include "inputHandler.h"
#include <sudooku_core/strategies/solvingStrategy.h>
#include <string>
#include <fstream>

/**
 * InputHandler implementation for File inputs
 */
class FileInputHandler : public InputHandler {
private:
    std::ifstream inputFile;
    Matrix matrix;
    unsigned short int dimension;
    const char SEPARATOR = ';';
    std::vector<bool> flags{};

public:
    explicit FileInputHandler(std::vector<bool> const &, std::string const &);

    ~FileInputHandler() override;

    Matrix readInput() override;

    std::vector<SolvingStrategy *> readRules() override;
};

#endif //SUDOOKU_FILEINPUTHANDLER_H
