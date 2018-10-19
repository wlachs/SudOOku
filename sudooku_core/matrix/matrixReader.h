//
// Created by Borbély László on 2018. 10. 02..
//

#ifndef SUDOOKU_MATRIXREADER_H
#define SUDOOKU_MATRIXREADER_H

#include <fstream>
#include "matrix.h"

class MatrixReader {
private:
    std::ifstream inputFile;
    Matrix matrix;
    unsigned short int dimension;

    void parseMatrix();

public:
    MatrixReader(const char *fileName);

    explicit operator Matrix() const;
};

#endif //SUDOOKU_MATRIXREADER_H
