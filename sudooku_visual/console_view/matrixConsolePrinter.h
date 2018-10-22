//
// Created by Borbély László on 2018. 10. 22..
//

#ifndef SUDOOKU_PRINTTOCONSOLE_H
#define SUDOOKU_PRINTTOCONSOLE_H

#include <sudookuPrinter.h>

class MatrixConsolePrinter : public SudookuPrinter {
public:
    virtual ~MatrixConsolePrinter() = default;

    virtual void print(Matrix const &);
};

#endif //SUDOOKU_PRINTTOCONSOLE_H
