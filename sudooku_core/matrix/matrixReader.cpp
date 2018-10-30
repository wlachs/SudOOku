//
// Created by Borbély László on 2018. 10. 02..
//

#include <sstream>
#include "matrixReader.h"

MatrixReader::MatrixReader(const char *fileName) {
    inputFile.open(fileName);
    parseMatrix();
    inputFile.close();
}

void MatrixReader::parseMatrix() {
    if (inputFile.is_open()) {
        std::map<std::pair<unsigned short int, unsigned short int>, Field> inputMap;
        std::string line;
        unsigned short int rowIndex = 1;

        while (getline(inputFile, line)) {
            std::istringstream iss{line};
            std::string segment;
            std::vector<std::string> values;

            while (std::getline(iss, segment, ';')) {
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
}

MatrixReader::operator Matrix() const {
    return matrix;
}