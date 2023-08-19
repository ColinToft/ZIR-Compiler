#ifndef __VALUE_H
#define __VALUE_H

#include <iostream>
#include <string>

class ZIRType {
  public:
    enum Kind {
        Void,
        Int8,
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

  private:
    Kind kind;
};

/**
 * @brief
 * Value for the ZIR intermediate representation.
 */
class Value {
  public:
    virtual ~Value() {}

    virtual void print(std::ostream &out) = 0;
};

class Constant : public Value {
  public:
    Constant(ZIRType type, std::string value) : type(type), value(value) {}

    void print(std::ostream &out) {
        type.print(out);
        out << " " << value;
    }

  private:
    ZIRType type;
    std::string value;
};

#endif // __VALUE_H