#ifndef __PARSER_EXCEPTION_H
#define __PARSER_EXCEPTION_H

#include <exception>
#include <string>

#include "Lexer.h"

/**
 * Represents a generic parser exception.
 */
class ParserException : public std::exception {
  public:
    ParserException(std::string message) : message(message) {}

    virtual const char *what() const throw() { return message.c_str(); }

  private:
    std::string message;
};

/**
 * Exception thrown when a syntax error is encountered.
 */
class SyntaxException : public ParserException {
  public:
    SyntaxException(std::string message) : ParserException(message) {}
};

/**
 * Exception thrown when an unexpected token is encountered.
 */
class UnexpectedTokenException : public SyntaxException {
  public:
    UnexpectedTokenException(Token token, std::string expected = "")
        : SyntaxException("Line " + std::to_string(token.line) +
                          ": unexpected token '" + token.text + "'" +
                          (expected == "" ? "" : ", expected " + expected)) {}
};

#endif // __PARSER_EXCEPTION_H
