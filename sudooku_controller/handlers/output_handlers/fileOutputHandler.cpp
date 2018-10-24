//
// Created by Borbély László on 2018. 10. 24..
//

#include "fileOutputHandler.h"

FileOutputHandler::FileOutputHandler(std::string const &) {
    //TODO open output file
}

FileOutputHandler::~FileOutputHandler() {
    //TODO close output file
}

void FileOutputHandler::notifyEvent(SudookuEvent, const Matrix *) {
    //TODO print to output file
}
