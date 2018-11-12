//
// Created by Borbély László on 2018. 10. 22..
//

#ifndef SUDOOKU_SUDOOKUPRINTER_H
#define SUDOOKU_SUDOOKUPRINTER_H

#include <sudooku_core/matrix/matrix.h>

/**
 * Abstract class for visualizing Sudoku puzzles
 */
class SudookuPrinter {
public:
    virtual ~SudookuPrinter() = default;

    virtual void printStart(unsigned int) = 0;

    virtual void printEnd() = 0;

    virtual void print(Matrix const &) = 0;
};

#endif //SUDOOKU_SUDOOKUPRINTER_H
