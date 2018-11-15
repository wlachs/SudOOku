//
// Created by Borbély László on 2018. 10. 24..
//

#include <sstream>
#include <strategies/rowStrategy.h>
#include <strategies/diagonalStrategy.h>
#include <strategies/columnStrategy.h>
#include <strategies/groupStrategy.h>
#include "fileInputHandler.h"

/**
 * Open input file with the given name
 * @param fileName
 */
FileInputHandler::FileInputHandler(std::vector<bool> const &flags_, std::string const &fileName) : flags(flags_) {
    /* Open input */
    inputFile.open(fileName);

    /* Allocate Matrix reader object */
    readMatrixFromFile = new ReadMatrixFromFile{inputFile};
}

/**
 * Close input file
 */
FileInputHandler::~FileInputHandler() {
    /* Deallocate Matrix reader object */
    delete readMatrixFromFile;

    /* Close input */
    inputFile.close();
}

/**
 * Return the next unsolved puzzle from the input
 * @return parsed Matrix object
 */
Matrix FileInputHandler::readInput() {
    /* Read one input */
    return readMatrixFromFile->readOne();
}

/**
 * Read solving rules.
 * The pointers allocated must be freed by the caller
 * @return solving strategies
 */
std::vector<SolvingStrategy *> FileInputHandler::readRules() {
    /* Allocate SolvingStrategy pointers */
    std::vector<SolvingStrategy *> rules = {
            new RowStrategy{},
            new ColumnStrategy{},
            new GroupStrategy{}};

    /* The allocation of DiagonalStrategy is optional */
    if (flags[0]) {
        rules.push_back(new DiagonalStrategy{});
    }

    return rules;
}

/**
 * Check whether there are any unsolved inputs available
 * @return
 */
bool FileInputHandler::hasInput() const {
    /* Call the matching function */
    return readMatrixFromFile->hasInput();
}
