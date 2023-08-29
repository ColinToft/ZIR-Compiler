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
    virtual void print(std::ostream &out, int indent) = 0;
};

class ZenType : public ASTNode {
  public:
    enum Kind { Int16, Float, String, Bool, Void };
    ZenType(Kind kind) : kind(kind) {}

    void print(std::ostream &out, int indent) {
        out << "ZenType(";
        switch (kind) {
        case Int16:
            out << "Int16";
            break;
        case Float:
            out << "Float";
            break;
        case String:
            out << "String";
            break;
        case Bool:
            out << "Bool";
            break;
        case Void:
            out << "Void";
            break;
        }
        out << ")" << std::endl;
    }

    Kind getKind() { return kind; }

  private:
    Kind kind;
};

class ParamNode : public ASTNode {
  public:
    ParamNode(ZenType *type, std::string name) : type(type), name(name) {}
    ~ParamNode() { delete type; }
    void print(std::ostream &out, int indent) {
        out << "ParamNode(";
        type->print(out, 0);
        out << ", " << name;
        out << ")" << std::endl;
    }

  private:
    ZenType *type;
    std::string name;
};

class StatementNode : public ASTNode {
  public:
    StatementNode() {}
    virtual ~StatementNode() {}
    virtual void print(std::ostream &out, int indent) = 0;
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
    void print(std::ostream &out, int indent) {
        std::string indentStr(indent, ' ');
        out << indentStr << "FunctionNode(" << name << ", [";
        for (int i = 0; i < params.size(); i++) {
            params[i]->print(out, 0);
            if (i < params.size() - 1) {
                out << ", ";
            }
        }
        out << "], [\n";
        for (int i = 0; i < statements.size(); i++) {
            statements[i]->print(out, indent + 1);
            if (i < statements.size() - 1) {
                out << ",\n";
            }
        }

        out << indentStr << "])" << std::endl;
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
    virtual void print(std::ostream &out, int indent) = 0;
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
    void print(std::ostream &out, int indent) {
        std::string indentStr(indent, ' ');
        out << indentStr << "FunctionCallNode(" << name << ", [\n";
        for (int i = 0; i < args.size(); i++) {
            args[i]->print(out, indent + 1);
            if (i < args.size() - 1) {
                out << ",\n";
            }
        }
        out << indentStr << "])" << std::endl;
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
    void print(std::ostream &out, int indent) {
        out << "VariableNode(" << name << ")" << std::endl;
    }

  private:
    std::string name;
};

class ConstantNode : public ExpressionNode {
  public:
    ConstantNode(ZenType *type, std::string value) : type(type), value(value) {}
    ~ConstantNode() {}
    void print(std::ostream &out, int indent) {
        std::string indentStr(indent, ' ');
        out << indentStr << "ConstantNode(" << value << ")" << std::endl;
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
    void print(std::ostream &out, int indent) {
        std::string indentStr(indent, ' ');
        out << indentStr << "ReturnNode(" << std::endl;
        expression->print(out, indent + 1);
        out << indentStr << ")" << std::endl;
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
    void print(std::ostream &out, int indent) {
        for (auto node : nodes) {
            node->print(out, 0);
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
