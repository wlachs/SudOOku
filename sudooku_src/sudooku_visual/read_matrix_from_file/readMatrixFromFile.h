//
// Created by Borbély László on 2018. 11. 01..
//

#ifndef SUDOOKU_READMATRIXFROMFILE_H
#define SUDOOKU_READMATRIXFROMFILE_H

#include <fstream>
#include <sudooku_visual/sudookuReader.h>

class ReadMatrixFromFile : public SudookuReader {
private:
    const char SEPARATOR = ';';
    unsigned short int rowIndex = 1;
    std::ifstream &inputFile;
    std::vector<Matrix> inputs;

    void readPuzzles();

public:
    explicit ReadMatrixFromFile(std::ifstream &);

    ~ReadMatrixFromFile() override = default;

    std::vector<Matrix> readAll() override;
};


#endif //SUDOOKU_READMATRIXFROMFILE_H
