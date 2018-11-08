//
// Created by Borbély László on 2018. 11. 08..
//

#ifndef SUDOOKU_NOMATRIXEXCEPTION_H
#define SUDOOKU_NOMATRIXEXCEPTION_H

#include <exception>

/**
 * Exception class
 * Should be thrown when the Solver::solver(...) function gets called before an initial Matrix is added
 */
class NoMatrixException : public std::exception {
public:
    const char *what() const noexcept override;
};


#endif //SUDOOKU_NOMATRIXEXCEPTION_H
