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

    /* Reset row index */
    rowIndex = 1;

    /* Prefetch one input */
    readPuzzle();
}

/**
 * Read all puzzles from input
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
            /* If there were no useful values read, loop */
            if (isWhiteSpace(line)) {
                continue;
            }

            /* Initialize local variables */
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

            if (rowIndex == dimension) {
                /* Initialize puzzle in vector */
                inputs.emplace_back(Matrix{dimension, inputMap});

                /* Reset row counter */
                rowIndex = 1;

                /* Clear input map */
                inputMap.clear();
            } else {
                /* Otherwise, increment row index */
                ++rowIndex;
            }
        }
    }
}

/**
 * Read the next puzzle from input
 */
void ReadMatrixFromFile::readPuzzle() {
    if (inputFile.is_open()) {
        /* Init temporary variable for constructing a Matrix */
        std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap;

        /* The row being read */
        std::string line{};

        /* Store matrix dimension */
        unsigned short int dimension{};

        /* Read input file line-by-line */
        while (getline(inputFile, line) && !isInputMatrixValid()) {
            /* If there were no useful values read, loop */
            if (isWhiteSpace(line)) {
                continue;
            }

            /* Initialize local variables */
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

            if (rowIndex == dimension) {
                /* Initialize puzzle in vector */
                input = Matrix{dimension, inputMap};

                /* Reset row counter */
                rowIndex = 1;

                /* Clear input map */
                inputMap.clear();
            } else {
                /* Otherwise, increment row index */
                ++rowIndex;
            }
        }
    }
}

/**
 * Decide whether a line being read is relevant or not
 * @param line
 * @return
 */
bool ReadMatrixFromFile::isWhiteSpace(std::string const &line) const {
    /* Empty string is always whitespace */
    if (line.empty()) {
        return true;
    }

    /* Otherwise search for leading comment char in string */
    return line[0] == COMMENT;

}

/**
 * Read every input from file and return a puzzle vector
 * @deprecated Will be removed, use readOne instead
 * @return
 */
std::vector<Matrix> ReadMatrixFromFile::readAll() {
    return inputs;
}

/**
 * Checks whether there are any unsolved puzzles to be read from the input file
 */
bool ReadMatrixFromFile::hasInput() {
    /* If there is no valid input, the dimension will equal 0 */
    return input.getDimension() != 0;
}

/**
 * Returns one unsolved Matrix from the input
 * If called when there are no more inputs available, an exception is thrown of type NoInputMatrixException
 * @return
 */
Matrix ReadMatrixFromFile::readOne() {
    /* Save return value */
    Matrix returnValue = std::move(input);

    /* Read next Matrix from the input */
    readPuzzle();

    /* Return Matrix */
    return returnValue;
}

/**
 * Checks whether the input Matrix is valid
 * The matrix is valid if the dimension is greater than 0
 * This function is basically identical to the hasInput function, just creating this for code readability
 * @return
 */
bool ReadMatrixFromFile::isInputMatrixValid() {
    return hasInput();
}
