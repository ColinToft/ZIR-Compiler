#ifndef __VALUE_H
#define __VALUE_H

#include <iostream>
#include <string>

class ZIRType {
   public:
    enum Kind {
        Void,
        Int,
        Float,
        Bool,
        String,
    };

    void print() {
        switch (kind) {
            case Void:
                std::cout << "void";
                break;
            case Int:
                std::cout << "int";
                break;
            case Float:
                std::cout << "float";
                break;
            case Bool:
                std::cout << "bool";
                break;
            case String:
                std::cout << "string";
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

    virtual void print() = 0;
};

class Constant : public Value {
   public:
    Constant(ZIRType type, std::string value) : type(type), value(value) {}

    void print() {
        std::cout << "Constant(";
        type.print();
        std::cout << ")" << std::endl;
    }

   private:
    ZIRType type;
    std::string value;
};

#endif  // __VALUE_H