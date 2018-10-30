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
    inputFile.open(fileName);
}

/**
 * Close input file
 */
FileInputHandler::~FileInputHandler() {
    inputFile.close();
}

/**
 * Read unsolved matrix from input and return a Matrix object
 * @return parsed Matrix object
 */
Matrix FileInputHandler::readInput() {
    if (inputFile.is_open()) {
        std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap;
        std::string line;
        unsigned short int rowIndex = 1;

        /* Read input file line-by-line */
        while (getline(inputFile, line)) {
            std::istringstream iss{line};
            std::string segment;
            std::vector<std::string> values;

            /* Split the line read by the predefined separator character.
             * Initially it's a ';' character */
            while (std::getline(iss, segment, SEPARATOR)) {
                values.push_back(segment);
            }

            /* The separators must be present even if there aren't any numbers in the file.
             * This means the dimension of the Matrix must be equal to the number of
             * separators in one row (or column) */
            dimension = static_cast<unsigned short int>(values.size());

            /* We can add the fixed values to the Matrix object.
             * If a value isn't fixed, we will handle it later */
            for (unsigned short int columnIndex = 1; columnIndex <= dimension; ++columnIndex) {
                if (!values[columnIndex - 1].empty()) {
                    inputMap.insert({{rowIndex, columnIndex},
                                     Field{static_cast<unsigned short int>(std::stoi(values[columnIndex - 1]))}});
                }
            }

            ++rowIndex;
        }

        /* Initialize return value */
        matrix = Matrix{dimension, inputMap};
    }

    return matrix;
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