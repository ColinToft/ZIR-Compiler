#ifndef __LEXER_H
#define __LEXER_H

#include <string>
#include <unordered_map>
#include <vector>

struct Token {
    enum Type {
        Number,
        Identifier,
        Plus,
        Minus,
        Mul,
        Div,
        LParen,   // (
        RParen,   // )
        LBrace,   // {
        RBrace,   // }
        LBracket, // [
        RBracket, // ]
        Comma,
        Newline,
        Eof,
        _Type,
        If,
        Else,
        While,
        For,
        Return,
    };

    Token(Type type, std::string text, int line, int col)
        : type(type), text(text), line(line), col(col) {}

    Type type;
    std::string text;
    int line;
    int col;

    void print();
};

/**
 * Lexer for the Zen programming language.
 */
class Lexer {
  public:
    Lexer(std::string text) : text(text), textSize(text.length()) {}

    std::vector<Token> tokenize();

  private:
    std::string text;
    int textSize;
    int pos = 0;
    int line = 1;
    int col = 1;

    std::vector<std::string> typeKeywords = {"int", "float", "string", "bool",
                                             "void"};

    // Keywords that are not types
    std::unordered_map<std::string, Token::Type> keywords = {
        {"if", Token::Type::If},
        {"else", Token::Type::Else},
        {"while", Token::Type::While},
        {"for", Token::Type::For},
        {"return", Token::Type::Return}};
};

#endif // __LEXER_H