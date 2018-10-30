//
// Created by Borbély László on 2018. 10. 25..
//

#ifndef SUDOOKU_NOMATRIXPROVIDEDEXCEPTION_H
#define SUDOOKU_NOMATRIXPROVIDEDEXCEPTION_H

#include <exception>

class NoMatrixProvidedException : public std::exception {
public:
    const char *what() const noexcept override;
};


#endif //SUDOOKU_NOMATRIXPROVIDEDEXCEPTION_H
