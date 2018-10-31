//
// Created by Borbély László on 2018. 10. 30..
//

#ifndef SUDOOKU_WRONGEVENTTYPEEXCEPTION_H
#define SUDOOKU_WRONGEVENTTYPEEXCEPTION_H

#include <exception>

/**
 * Exception class
 * Should be thrown when the OutputHandler::notifyEvent(...) function gets called with an incorrect event type
 */
class WrongEventTypeException : public std::exception {
public:
    const char *what() const noexcept override;
};


#endif //SUDOOKU_WRONGEVENTTYPEEXCEPTION_H
