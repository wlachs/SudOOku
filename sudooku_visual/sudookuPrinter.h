//
// Created by Borbély László on 2018. 10. 22..
//

#ifndef SUDOOKU_SUDOOKUPRINTER_H
#define SUDOOKU_SUDOOKUPRINTER_H

#include <matrix/matrix.h>

class SudookuPrinter {
public:
    virtual ~SudookuPrinter() = default;

    virtual void print(Matrix const &) = 0;
};

#endif //SUDOOKU_SUDOOKUPRINTER_H
