//
// Created by Borbély László on 2018. 11. 01..
//

#ifndef SUDOOKU_READMATRIXFROMFILE_H
#define SUDOOKU_READMATRIXFROMFILE_H

#include <fstream>
#include <sudooku_visual/sudookuReader.h>

class ReadMatrixFromFile : public SudookuReader {
private:
    const char COMMENT = '#';
    const char SEPARATOR = ';';
    unsigned short int rowIndex = 1;
    std::ifstream &inputFile;
    std::vector<Matrix> inputs;
    Matrix input{0, {}};

    void readPuzzles();

    void readPuzzle();

    bool isWhiteSpace(std::string const &) const;

    bool isInputMatrixValid();

public:
    explicit ReadMatrixFromFile(std::ifstream &);

    ~ReadMatrixFromFile() override = default;

    std::vector<Matrix> readAll() override;

    bool hasInput() override;

    Matrix readOne() override;
};


#endif //SUDOOKU_READMATRIXFROMFILE_H
