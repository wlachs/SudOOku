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

        while (getline(inputFile, line)) {
            std::istringstream iss{line};
            std::string segment;
            std::vector<std::string> values;

            while (std::getline(iss, segment, SEPARATOR)) {
                values.push_back(segment);
            }

            dimension = static_cast<unsigned short int>(values.size());
            for (unsigned short int columnIndex = 1; columnIndex <= dimension; ++columnIndex) {
                if (!values[columnIndex - 1].empty()) {
                    inputMap.insert({{rowIndex, columnIndex},
                                     Field{static_cast<unsigned short int>(std::stoi(values[columnIndex - 1]))}});
                }
            }

            ++rowIndex;
        }

        matrix = Matrix{dimension, inputMap};
    }

    return matrix;
}

/**
 * Read solving rules
 * @return solving strategies
 */
std::vector<SolvingStrategy *> FileInputHandler::readRules() {
    std::vector<SolvingStrategy *> rules = {
            new RowStrategy{},
            new ColumnStrategy{},
            new GroupStrategy{}};

    if (flags[0]) {
        rules.push_back(new DiagonalStrategy{});
    }
    return rules;
}