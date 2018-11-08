//
// Created by Borbély László on 2018. 11. 01..
//

#include <string>
#include <sstream>
#include "readMatrixFromFile.h"

/**
 * Init input file stream reference
 * @param inputFile_
 */
ReadMatrixFromFile::ReadMatrixFromFile(std::ifstream &inputFile_) : inputFile(inputFile_) {
    /* Read all inputs from file */
    readPuzzles();
}

/**
 * Read the next puzzle from input
 */
void ReadMatrixFromFile::readPuzzles() {
    if (inputFile.is_open()) {
        /* Init temporary variable for constructing a Matrix */
        std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap;

        /* The row being read */
        std::string line{};

        /* Store matrix dimension */
        unsigned short int dimension{};

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

            /* If there were no values read, loop */
            if (values.empty()) {
                continue;
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

            if (rowIndex == dimension) {
                /* Initialize puzzle in vector */
                inputs.emplace_back(Matrix{dimension, inputMap});

                /* Reset row counter */
                rowIndex = 1;
            } else {
                /* Otherwise, increment row index */
                ++rowIndex;
            }
        }
    }
}

/**
 * Read every input from file and return a puzzle vector
 * @return
 */
std::vector<Matrix> ReadMatrixFromFile::readAll() {
    return inputs;
}