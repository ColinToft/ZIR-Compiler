#include "parser.h"

#include <iostream>
#include <stdexcept>

#include "AST.h"
#include "ParserException.h"

ProgramNode *Parser::parse() {
    std::vector<ASTNode *> nodes;

    while (index < tokens.size()) {
        // Check for function (type, identifier, (, ), {, })
        if (tokens.at(index).type == Token::Type::_Type &&
            tokens.at(index + 1).type == Token::Type::Identifier &&
            tokens.at(index + 2).type == Token::Type::LParen) {
            nodes.push_back(parseFunction());
        } else if (tokens.at(index).type == Token::Type::Newline) {
            index++;
        } else if (tokens.at(index).type == Token::Type::Eof) {
            break;
        } else {
            throw UnexpectedTokenException(tokens.at(index));
        }
    }

    return new ProgramNode(nodes);
}

ZenType *Parser::parseType() {
    Token type = tokens.at(index);
    index++;
    if (type.type != Token::Type::_Type) {
        throw UnexpectedTokenException(tokens.at(index - 1), "type");
    }

    if (type.text == "int") {
        return new ZenType(ZenType::Kind::Int16);
    } else if (type.text == "float") {
        return new ZenType(ZenType::Kind::Float);
    } else if (type.text == "string") {
        return new ZenType(ZenType::Kind::String);
    } else if (type.text == "bool") {
        return new ZenType(ZenType::Kind::Bool);
    } else if (type.text == "void") {
        return new ZenType(ZenType::Kind::Void);
    } else {
        throw SyntaxException("Unexpected type " + type.text + " at line " +
                              std::to_string(type.line) + ", column " +
                              std::to_string(type.col));
    }
}

FunctionNode *Parser::parseFunction() {
    // Parse type
    Token type = tokens.at(index);
    ZenType *Type;
    if (type.text == "int") {
        Type = new ZenType(ZenType::Kind::Int16);
    } else if (type.text == "float") {
        Type = new ZenType(ZenType::Kind::Float);
    } else if (type.text == "string") {
        Type = new ZenType(ZenType::Kind::String);
    } else if (type.text == "bool") {
        Type = new ZenType(ZenType::Kind::Bool);
    } else if (type.text == "void") {
        Type = new ZenType(ZenType::Kind::Void);
    } else {
        throw SyntaxException("Unexpected type " + type.text + " at line " +
                              std::to_string(type.line) + ", column " +
                              std::to_string(type.col));
    }
    index++;

    // Parse identifier
    Token identifier = tokens.at(index);
    index++;

    expect(Token::Type::LParen);
    std::vector<ParamNode *> params = parseParams();
    expect(Token::Type::RParen);

    expect(Token::Type::LBrace);
    std::vector<StatementNode *> body = parseStatements();
    expect(Token::Type::RBrace);

    return new FunctionNode(Type, identifier.text, params, body);
}

std::vector<ParamNode *> Parser::parseParams() {
    std::vector<ParamNode *> nodes;

    while (tokens.at(index).type != Token::Type::RParen) {
        nodes.push_back(parseParam());
        if (tokens.at(index).type == Token::Type::Comma) {
            index++;
        } else if (tokens.at(index).type != Token::Type::RParen) {
            throw UnexpectedTokenException(tokens.at(index), "comma or )");
        }
    }

    return nodes;
}

ParamNode *Parser::parseParam() {
    // Parse type
    ZenType *ZenType = parseType();

    // Parse identifier
    Token identifier = tokens.at(index);
    index++;

    return new ParamNode(ZenType, identifier.text);
}

std::vector<StatementNode *> Parser::parseStatements() {
    std::vector<StatementNode *> statements;
    while (tokens.at(index).type != Token::Type::RBrace) {
        statements.push_back(parseStatement());
    }

    return statements;
}

StatementNode *Parser::parseStatement() {
    while (tokens.at(index).type == Token::Type::Newline) {
        index++;
    }

    // Check for return statement
    if (tokens.at(index).type == Token::Type::Return) {
        index++;

        // We either will have an expression or a newline
        if (tokens.at(index).type == Token::Type::Newline) {
            index++;
            return new ReturnNode(
                new ConstantNode(new ZenType(ZenType::Void), "void"));
        }

        ExpressionNode *expression = parseExpression();

        expect(Token::Type::Newline);
        return new ReturnNode(expression);
    } else if (tokens.at(index).type == Token::Type::Identifier &&
               tokens.at(index + 1).type == Token::Type::LParen) {
        // Function call
        FunctionCallNode *functionCall = parseFunctionCall();
        expect(Token::Type::Newline);
        return functionCall;
    }

    throw UnexpectedTokenException(tokens.at(index - 1), "statement");
}

FunctionCallNode *Parser::parseFunctionCall() {
    // Parse identifier
    Token identifier = tokens.at(index);
    index++;

    expect(Token::Type::LParen);
    std::vector<ExpressionNode *> args = parseExpressionList();
    expect(Token::Type::RParen);

    return new FunctionCallNode(identifier.text, args);
}

std::vector<ExpressionNode *> Parser::parseExpressionList() {
    std::vector<ExpressionNode *> nodes;

    while (tokens.at(index).type != Token::Type::RParen) {
        nodes.push_back(parseExpression());
        if (tokens.at(index).type == Token::Type::Comma) {
            index++;
        } else if (tokens.at(index).type != Token::Type::RParen) {
            throw UnexpectedTokenException(tokens.at(index), "comma or )");
        }
    }

    return nodes;
}

ExpressionNode *Parser::parseExpression() {
    // Is current token a number
    if (tokens.at(index).type == Token::Type::Number) {
        Token number = tokens.at(index);
        index++;

        return new ConstantNode(new ZenType(ZenType::Int16), number.text);
    }

    throw UnexpectedTokenException(tokens.at(index));
}

void Parser::expect(Token::Type type) {
    if (tokens.at(index).type != type) {
        throw UnexpectedTokenException(tokens.at(index));
    }
    index++;
}