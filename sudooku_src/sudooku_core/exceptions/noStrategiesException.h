//
// Created by Borbély László on 2018. 10. 25..
//

#ifndef SUDOOKU_NOSTRATEGIESEXCEPTION_H
#define SUDOOKU_NOSTRATEGIESEXCEPTION_H

#include <exception>

class NoStrategiesException : public std::exception {
public:
    const char *what() const noexcept override;
};

#endif //SUDOOKU_NOSTRATEGIESEXCEPTION_H
