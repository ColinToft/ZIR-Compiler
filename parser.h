#ifndef __PARSER_H
#define __PARSER_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "ast.h"
#include "lexer.h"

/**
 * @brief
 * Parser for the Zen programming language compiler.
 * Uses recursive descent to generate an AST.
 */
class Parser {
   public:
    Parser(std::vector<Token> tokens) : tokens(tokens), index(0) {}

    ProgramNode* parse();

   private:
    std::vector<Token> tokens;
    int index;

    ZenType* parseType();
    FunctionCallNode* parseFunctionCall();
    FunctionNode* parseFunction();
    std::vector<ParamNode*> parseParams();
    ParamNode* parseParam();
    std::vector<StatementNode*> parseStatements();
    StatementNode* parseStatement();
    std::vector<ExpressionNode*> parseExpressionList();
    ExpressionNode* parseExpression();

    void expect(Token::Type type);
};

#endif  // __PARSER_H