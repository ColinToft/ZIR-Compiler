#ifndef __VALUE_H
#define __VALUE_H

#include <iostream>
#include <string>

class ZIRType {
  public:
    enum Kind {
        Void,
        Int8,
        Int16,
        Float,
        Bool,
        String,
    };

    ZIRType(Kind kind) : kind(kind) {}

    void print(std::ostream &out) {
        switch (kind) {
        case Void:
            out << "void";
            break;
        case Int8:
            out << "int8";
            break;
        case Int16:
            out << "int16";
            break;
        case Float:
            out << "float";
            break;
        case Bool:
            out << "bool";
            break;
        case String:
            out << "string";
            break;
        }
    }

    bool operator==(const ZIRType &other) const { return kind == other.kind; }

    bool operator!=(const ZIRType &other) const { return kind != other.kind; }

  private:
    Kind kind;
};

/**
 * Value for the ZIR intermediate representation.
 */
class Value {
  public:
    Value(ZIRType type) : type(type) {}
    virtual ~Value() {}

    virtual void print(std::ostream &out) = 0;

    virtual bool isConstant() { return false; }

    ZIRType getType() { return type; }

  protected:
    ZIRType type;
};

class Constant : public Value {
  public:
    Constant(ZIRType type, std::string value) : Value(type), value(value) {}

    void print(std::ostream &out) override {
        type.print(out);
        if (type != ZIRType::Void) {
            out << " " << value;
        }
    }

    bool isConstant() override { return true; }

    int getIntValue() { return std::stoi(value); }

  private:
    std::string value;
};

#endif // __VALUE_H