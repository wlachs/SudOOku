//
// Created by Borbély László on 2018. 11. 08..
//

#ifndef SUDOOKU_FIELDDOESNTCONTAINVALUEEXCEPTION_H
#define SUDOOKU_FIELDDOESNTCONTAINVALUEEXCEPTION_H

#include <exception>

class FieldDoesntContainValueException : public std::exception {
public:
    const char *what() const noexcept override;
};


#endif //SUDOOKU_FIELDDOESNTCONTAINVALUEEXCEPTION_H
