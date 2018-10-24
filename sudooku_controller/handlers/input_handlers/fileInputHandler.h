//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_FILEINPUTHANDLER_H
#define SUDOOKU_FILEINPUTHANDLER_H

#include "inputHandler.h"
#include <string>

class FileInputHandler : public InputHandler {
private:
    std::string fileName;

public:
    explicit FileInputHandler(std::string const &);

    virtual ~FileInputHandler();

    virtual Matrix readInput();
};

#endif //SUDOOKU_FILEINPUTHANDLER_H
