//
// Created by Borbély László on 2018. 10. 23..
//

#ifndef SUDOOKU_PRINTMATRIXTOFILE_H
#define SUDOOKU_PRINTMATRIXTOFILE_H

#include <sudookuPrinter.h>
#include <fstream>

class PrintMatrixToFile : public SudookuPrinter {
private:
    std::ofstream solutionsFile;

public:
    explicit PrintMatrixToFile(std::string const &);

    virtual ~PrintMatrixToFile();

    virtual void print(Matrix const &);
};

#endif //SUDOOKU_PRINTMATRIXTOFILE_H
