#ifndef __AST_H
#define __AST_H

#include <iostream>
#include <string>
#include <vector>

/**
 * Abstract syntax tree for the Zen programming language compiler.
 */
class ASTNode {
  public:
    ASTNode() {}
    virtual ~ASTNode() {}
    virtual void print(int indent) = 0;
};

class ZenType : public ASTNode {
  public:
    enum Kind { Int16, Float, String, Bool, Void };
    ZenType(Kind kind) : kind(kind) {}

    void print(int indent) {
        std::cout << "ZenType(";
        switch (kind) {
        case Int16:
            std::cout << "Int16";
            break;
        case Float:
            std::cout << "Float";
            break;
        case String:
            std::cout << "String";
            break;
        case Bool:
            std::cout << "Bool";
            break;
        case Void:
            std::cout << "Void";
            break;
        }
        std::cout << ")" << std::endl;
    }

    Kind getKind() { return kind; }

  private:
    Kind kind;
};

class ParamNode : public ASTNode {
  public:
    ParamNode(ZenType *type, std::string name) : type(type), name(name) {}
    ~ParamNode() { delete type; }
    void print(int indent) {
        std::cout << "ParamNode(";
        type->print(0);
        std::cout << ", " << name;
        std::cout << ")" << std::endl;
    }

  private:
    ZenType *type;
    std::string name;
};

class StatementNode : public ASTNode {
  public:
    StatementNode() {}
    virtual ~StatementNode() {}
    virtual void print(int indent) = 0;
};

class FunctionNode : public ASTNode {
  public:
    FunctionNode(ZenType *returnType, std::string name,
                 std::vector<ParamNode *> params,
                 std::vector<StatementNode *> statements)
        : returnType(returnType), name(name), params(params),
          statements(statements) {}
    ~FunctionNode() {
        delete returnType;
        for (auto node : statements) {
            delete node;
        }
    }
    void print(int indent) {
        std::string indentStr(indent, ' ');
        std::cout << indentStr << "FunctionNode(" << name << ", [";
        for (int i = 0; i < params.size(); i++) {
            params[i]->print(0);
            if (i < params.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << "], [\n";
        for (int i = 0; i < statements.size(); i++) {
            statements[i]->print(indent + 1);
            if (i < statements.size() - 1) {
                std::cout << ",\n";
            }
        }

        std::cout << indentStr << "])" << std::endl;
    }

    std::string getName() { return name; }
    ZenType *getReturnType() { return returnType; }
    std::vector<ParamNode *> getParams() { return params; }
    std::vector<StatementNode *> getStatements() { return statements; }

  private:
    ZenType *returnType;
    std::string name;
    std::vector<ParamNode *> params;
    std::vector<StatementNode *> statements;
};

class ExpressionNode : public StatementNode {
  public:
    ExpressionNode() {}
    virtual ~ExpressionNode() {}
    virtual void print(int indent) = 0;
};

class FunctionCallNode : public ExpressionNode {
  public:
    FunctionCallNode(std::string name, std::vector<ExpressionNode *> args)
        : name(name), args(args) {}
    ~FunctionCallNode() {
        for (auto node : args) {
            delete node;
        }
    }
    void print(int indent) {
        std::string indentStr(indent, ' ');
        std::cout << indentStr << "FunctionCallNode(" << name << ", [\n";
        for (int i = 0; i < args.size(); i++) {
            args[i]->print(indent + 1);
            if (i < args.size() - 1) {
                std::cout << ",\n";
            }
        }
        std::cout << indentStr << "])" << std::endl;
    }

    std::string getName() { return name; }
    std::vector<ExpressionNode *> getArgs() { return args; }

  private:
    std::string name;
    std::vector<ExpressionNode *> args;
};

class VariableNode : public ExpressionNode {
  public:
    VariableNode(std::string name) : name(name) {}
    ~VariableNode() {}
    void print(int indent) {
        std::cout << "VariableNode(" << name << ")" << std::endl;
    }

  private:
    std::string name;
};

class ConstantNode : public ExpressionNode {
  public:
    ConstantNode(ZenType *type, std::string value) : type(type), value(value) {}
    ~ConstantNode() {}
    void print(int indent) {
        std::string indentStr(indent, ' ');
        std::cout << indentStr << "ConstantNode(" << value << ")" << std::endl;
    }

    ZenType *getType() { return type; }
    std::string getValue() { return value; }

  private:
    ZenType *type;
    std::string value;
};

class ReturnNode : public StatementNode {
  public:
    ReturnNode(ExpressionNode *expression) : expression(expression) {}
    ~ReturnNode() { delete expression; }
    void print(int indent) {
        std::string indentStr(indent, ' ');
        std::cout << indentStr << "ReturnNode(" << std::endl;
        expression->print(indent + 1);
        std::cout << indentStr << ")" << std::endl;
    }

    ExpressionNode *getExpression() { return expression; }

  private:
    ExpressionNode *expression;
};

class ProgramNode : public ASTNode {
  public:
    ProgramNode(std::vector<ASTNode *> nodes) : nodes(nodes) {}
    ~ProgramNode() {
        for (auto node : nodes) {
            delete node;
        }
    }
    void print(int indent) {
        for (auto node : nodes) {
            node->print(0);
        }
    }
    std::vector<FunctionNode *> getFunctions() {
        std::vector<FunctionNode *> functions;
        for (auto node : nodes) {
            FunctionNode *function = dynamic_cast<FunctionNode *>(node);
            if (function != nullptr) {
                functions.push_back(function);
            }
        }
        return functions;
    }

  private:
    std::vector<ASTNode *> nodes;
};

#endif // __AST_H
