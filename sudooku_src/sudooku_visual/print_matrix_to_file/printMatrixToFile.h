//
// Created by Borbély László on 2018. 10. 23..
//

#ifndef SUDOOKU_PRINTMATRIXTOFILE_H
#define SUDOOKU_PRINTMATRIXTOFILE_H

#include <sudooku_visual/sudookuPrinter.h>
#include <fstream>

/**
 * Implementation of SudookuPrinter
 * Writes the puzzle to an output file stream passed as a constructor parameter
 */
class PrintMatrixToFile : public SudookuPrinter {
private:
    std::ofstream &solutionsFile;

public:
    explicit PrintMatrixToFile(std::ofstream &);

    void print(Matrix const &) override;

    ~PrintMatrixToFile() override = default;
};

#endif //SUDOOKU_PRINTMATRIXTOFILE_H
