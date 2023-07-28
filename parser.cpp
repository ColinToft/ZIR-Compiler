#include "parser.h"

#include <iostream>
#include <stdexcept>

#include "ast.h"

ProgramNode* Parser::parse() {
    std::vector<ASTNode*> nodes;

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

TypeNode* Parser::parseType() {
    Token type = tokens.at(index);
    index++;
    if (type.type != Token::Type::_Type) {
        throw std::runtime_error("Unexpected token " + type.text + " at line " +
                                 std::to_string(type.line) + ", column " +
                                 std::to_string(type.col));
    }

    if (type.text == "int") {
        return new TypeNode(TypeNode::Type::Int);
    } else if (type.text == "float") {
        return new TypeNode(TypeNode::Type::Float);
    } else if (type.text == "string") {
        return new TypeNode(TypeNode::Type::String);
    } else if (type.text == "bool") {
        return new TypeNode(TypeNode::Type::Bool);
    } else if (type.text == "void") {
        return new TypeNode(TypeNode::Type::Void);
    } else {
        throw std::runtime_error("Unexpected type " + type.text + " at line " +
                                 std::to_string(type.line) + ", column " +
                                 std::to_string(type.col));
    }
}

FunctionNode* Parser::parseFunction() {
    // Parse type
    Token type = tokens.at(index);
    TypeNode* typeNode;
    if (type.text == "int") {
        typeNode = new TypeNode(TypeNode::Type::Int);
    } else if (type.text == "float") {
        typeNode = new TypeNode(TypeNode::Type::Float);
    } else if (type.text == "string") {
        typeNode = new TypeNode(TypeNode::Type::String);
    } else if (type.text == "bool") {
        typeNode = new TypeNode(TypeNode::Type::Bool);
    } else if (type.text == "void") {
        typeNode = new TypeNode(TypeNode::Type::Void);
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
    std::vector<ParamNode*> params = parseParams();
    expect(Token::Type::RParen);

    expect(Token::Type::LBrace);
    std::vector<StatementNode*> body = parseStatements();
    expect(Token::Type::RBrace);

    return new FunctionNode(typeNode, identifier.text, params, body);
}

std::vector<ParamNode*> Parser::parseParams() {
    return parseList<ParamNode*>(parseParam, Token::Type::Comma,
                                 Token::Type::RParen);
}

ParamNode* Parser::parseParam() {
    // Parse type
    TypeNode* typeNode = parseType();

    // Parse identifier
    Token identifier = tokens.at(index);
    index++;

    return new ParamNode(typeNode, identifier.text);
}

std::vector<StatementNode*> Parser::parseStatements() {
    std::vector<StatementNode*> statements;
    while (tokens.at(index).type != Token::Type::RBrace) {
        statements.push_back(parseStatement());
    }

    return statements;
}

StatementNode* Parser::parseStatement() {
    while (tokens.at(index).type == Token::Type::Newline) {
        index++;
    }

    // Parse identifier
    Token identifier = tokens.at(index);
    index++;

    // Check for function call
    if (tokens.at(index).type == Token::Type::LParen) {
        index--;
        FunctionCallNode* functionCall = parseFunctionCall();
        expect(Token::Type::Newline);
        return functionCall;
    }

    throw std::runtime_error(
        "Unexpected token " + tokens.at(index).text + " at line " +
        std::to_string(tokens.at(index).line) + ", column " +
        std::to_string(tokens.at(index).col));
}

FunctionCallNode* Parser::parseFunctionCall() {
    // Parse identifier
    Token identifier = tokens.at(index);
    index++;

    expect(Token::Type::LParen);
    std::vector<ExpressionNode*> args = parseExpressionList();
    expect(Token::Type::RParen);

    return new FunctionCallNode(identifier.text, args);
}

std::vector<ExpressionNode*> Parser::parseExpressionList() {
    return parseList<ExpressionNode*>(parseExpression, Token::Type::Comma,
                                      Token::Type::RParen);
}

ExpressionNode* Parser::parseExpression() {
    // Is current token a number
    if (tokens.at(index).type == Token::Type::Number) {
        Token number = tokens.at(index);
        index++;

        return new ConstantNode(new TypeNode(TypeNode::Int), number.text);
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