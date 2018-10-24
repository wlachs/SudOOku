//
// Created by Borbély László on 2018. 10. 24..
//

#include "fileInputHandler.h"

FileInputHandler::FileInputHandler(std::string const &fileName) : fileName(fileName) {
    // TODO open input file
}

FileInputHandler::~FileInputHandler() {
    // TODO close input file
}

Matrix FileInputHandler::readInput() {
    // TODO read matrix from file
    return Matrix();
}
