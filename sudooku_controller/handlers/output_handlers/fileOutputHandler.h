//
// Created by Borbély László on 2018. 10. 24..
//

#ifndef SUDOOKU_FILEOUTPUTHANDLER_H
#define SUDOOKU_FILEOUTPUTHANDLER_H

#include "outputHandler.h"
#include <string>

class FileOutputHandler : public OutputHandler {
public:
    FileOutputHandler(std::string const &);

    virtual ~FileOutputHandler();

    virtual void notifyEvent(SudookuEvent, const Matrix *);
};

#endif //SUDOOKU_FILEOUTPUTHANDLER_H
