#include "parser.h"

#include <iostream>
#include <stdexcept>

#include "ast.h"

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
            throw std::runtime_error(
                "Unexpected token " + tokens.at(index).text + " at line " +
                std::to_string(tokens.at(index).line) + ", column " +
                std::to_string(tokens.at(index).col));
        }
    }

    return new ProgramNode(nodes);
}

ZenType *Parser::parseType() {
    Token type = tokens.at(index);
    index++;
    if (type.type != Token::Type::_Type) {
        throw std::runtime_error("Unexpected token " + type.text + " at line " +
                                 std::to_string(type.line) + ", column " +
                                 std::to_string(type.col));
    }

    if (type.text == "int") {
        return new ZenType(ZenType::Kind::Int);
    } else if (type.text == "float") {
        return new ZenType(ZenType::Kind::Float);
    } else if (type.text == "string") {
        return new ZenType(ZenType::Kind::String);
    } else if (type.text == "bool") {
        return new ZenType(ZenType::Kind::Bool);
    } else if (type.text == "void") {
        return new ZenType(ZenType::Kind::Void);
    } else {
        throw std::runtime_error("Unexpected type " + type.text + " at line " +
                                 std::to_string(type.line) + ", column " +
                                 std::to_string(type.col));
    }
}

FunctionNode *Parser::parseFunction() {
    // Parse type
    Token type = tokens.at(index);
    ZenType *Type;
    if (type.text == "int") {
        Type = new ZenType(ZenType::Kind::Int);
    } else if (type.text == "float") {
        Type = new ZenType(ZenType::Kind::Float);
    } else if (type.text == "string") {
        Type = new ZenType(ZenType::Kind::String);
    } else if (type.text == "bool") {
        Type = new ZenType(ZenType::Kind::Bool);
    } else if (type.text == "void") {
        Type = new ZenType(ZenType::Kind::Void);
    } else {
        throw std::runtime_error("Unexpected type " + type.text + " at line " +
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
            throw std::runtime_error(
                "Unexpected token " + tokens.at(index).text + " at line " +
                std::to_string(tokens.at(index).line) + ", column " +
                std::to_string(tokens.at(index).col));
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

    // Parse identifier
    Token identifier = tokens.at(index);
    index++;

    // Check for function call
    if (tokens.at(index).type == Token::Type::LParen) {
        index--;
        FunctionCallNode *functionCall = parseFunctionCall();
        expect(Token::Type::Newline);
        return functionCall;
    }

    throw std::runtime_error(
        "Unexpected token " + tokens.at(index).text + " at line " +
        std::to_string(tokens.at(index).line) + ", column " +
        std::to_string(tokens.at(index).col));
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
            throw std::runtime_error(
                "Unexpected token " + tokens.at(index).text + " at line " +
                std::to_string(tokens.at(index).line) + ", column " +
                std::to_string(tokens.at(index).col));
        }
    }

    return nodes;
}

ExpressionNode *Parser::parseExpression() {
    // Is current token a number
    if (tokens.at(index).type == Token::Type::Number) {
        Token number = tokens.at(index);
        index++;

        return new ConstantNode(new ZenType(ZenType::Int), number.text);
    }

    throw std::runtime_error(
        "Unexpected token " + tokens.at(index).text + " at line " +
        std::to_string(tokens.at(index).line) + ", column " +
        std::to_string(tokens.at(index).col));
}

void Parser::expect(Token::Type type) {
    if (tokens.at(index).type != type) {
        throw std::runtime_error(
            "Unexpected token " + tokens.at(index).text + " at line " +
            std::to_string(tokens.at(index).line) + ", column " +
            std::to_string(tokens.at(index).col));
    }
    index++;
}