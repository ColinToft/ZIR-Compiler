#ifndef __INTERNAL_EXCEPTION_H
#define __INTERNAL_EXCEPTION_H

#include <exception>
#include <string>

/**
 * Represents a generic internal exception.
 * These exceptions should never be thrown, and indicate a bug or missing
 * feature in the compiler.
 */
class InternalException : public std::exception {
  public:
    InternalException(std::string message) : message(message) {}

    virtual const char *what() const throw() { return message.c_str(); }

  private:
    std::string message;
};

/**
 * Exception thrown when an unsupported feature is encountered.
 */
class UnsupportedFeatureException : public InternalException {
  public:
    UnsupportedFeatureException(std::string message)
        : InternalException(message) {}
};

#endif // __INTERNAL_EXCEPTION_H
