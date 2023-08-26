#include "lexer.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

void Token::print() {
    std::cout << "Token(" << static_cast<int>(type) << ", " << text << ", "
              << line << ", " << col << ")" << std::endl;
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    while (pos < textSize) {
        char ch = text.at(pos);

        if (ch == ' ' || ch == '\t') {
        } else if (ch == '\n') {
            // Skip as much newlines and spaces as possible

            int startCol = col;
            int startLine = line;
            pos++;
            col = 1;
            line++;

            while (pos < textSize) {
                if (text.at(pos) == ' ' || text.at(pos) == '\t') {
                    pos++;
                    col++;
                } else if (text.at(pos) == '\n') {
                    pos++;
                    line++;
                    col = 1;
                } else {
                    break;
                }
            }

            tokens.push_back(
                Token(Token::Type::Newline, "\\n", startLine, startCol));
            pos--;
            col--;
        } else if (ch == '+') {
            tokens.push_back(Token(Token::Type::Plus, "+", line, col));
        } else if (ch == '-') {
            tokens.push_back(Token(Token::Type::Minus, "-", line, col));
        } else if (ch == '*') {
            tokens.push_back(Token(Token::Type::Mul, "*", line, col));
        } else if (ch == '/') {
            tokens.push_back(Token(Token::Type::Div, "/", line, col));
        } else if (ch == '(') {
            tokens.push_back(Token(Token::Type::LParen, "(", line, col));
        } else if (ch == ')') {
            tokens.push_back(Token(Token::Type::RParen, ")", line, col));
        } else if (ch == '{') {
            tokens.push_back(Token(Token::Type::LBrace, "{", line, col));
        } else if (ch == '}') {
            tokens.push_back(Token(Token::Type::RBrace, "}", line, col));
        } else if (ch == '[') {
            tokens.push_back(Token(Token::Type::LBracket, "[", line, col));
        } else if (ch == ']') {
            tokens.push_back(Token(Token::Type::RBracket, "]", line, col));
        } else if (ch == ',') {
            tokens.push_back(Token(Token::Type::Comma, ",", line, col));
        } else if (ch == '\0') {
            tokens.push_back(Token(Token::Type::Eof, "<EOF>", line, col));
        } else if (isalpha(ch)) {
            std::string id = "";
            id += ch;
            int startCol = col;
            pos++;
            col++;

            while (pos < textSize && isalnum(ch = text.at(pos))) {
                id += ch;
                pos++;
                col++;
            }

            if (std::find(typeKeywords.begin(), typeKeywords.end(), id) !=
                typeKeywords.end()) {
                tokens.push_back(Token(Token::Type::_Type, id, line, startCol));
            } else {
                // First, check if it is a keyword
                auto it = keywords.find(id);
                if (it != keywords.end()) {
                    tokens.push_back(Token(it->second, id, line, startCol));
                    continue;
                }

                // If not, it is an identifier
                tokens.push_back(
                    Token(Token::Type::Identifier, id, line, startCol));
            }

            pos--;
            col--;
        } else if (isdigit(ch)) {
            std::string num = "";
            num += ch;
            int startCol = col;
            pos++;
            col++;

            while (pos < textSize && isdigit(ch = text.at(pos))) {
                num += ch;
                pos++;
                col++;
            }
            tokens.push_back(Token(Token::Type::Number, num, line, startCol));

            pos--;
            col--;
        } else {
            std::string msg = "Invalid character: ";
            msg += ch;
            throw std::runtime_error(msg);
        }
        pos++;
        col++;
    }
    tokens.push_back(Token(Token::Type::Eof, "<EOF>", line, col));
    return tokens;
}