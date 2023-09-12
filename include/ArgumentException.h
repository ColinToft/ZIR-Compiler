#ifndef __ARGUMENT_EXCEPTION_H
#define __ARGUMENT_EXCEPTION_H

#include <exception>
#include <string>

#include "Lexer.h"

/**
 * Represents a generic exception parsing argumejts.
 */
class ArgumentException : public std::exception {
  public:
    ArgumentException(std::string message) : message(message) {}

    virtual const char *what() const throw() { return message.c_str(); }

  private:
    std::string message;
};

#endif // __ARGUMENT_EXCEPTION_H
