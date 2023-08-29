#ifndef __Z80OPERAND_H
#define __Z80OPERAND_H

#include <iostream>
#include <string>

#include "backend/AsmPrinter.h"
#include "backend/z80/Z80Register.h"

/**
 * Represents an operand in Z80 assembly.
 */
class Z80Operand {
  public:
    virtual void print(AsmPrinter *printer) = 0;

    virtual bool isRegisterPair() = 0;

    virtual bool isRegister() = 0;

    virtual bool isImmediate() = 0;
};

/**
 * Represents a register operand in Z80 assembly.
 */
class Z80RegisterOperand : public Z80Operand {
  public:
    Z80RegisterOperand(Z80Register reg) : reg(reg) {}

    bool isRegister() override { return true; }

    bool isRegisterPair() override {
      switch (reg) {
        case AF:
        case BC:
        case DE:
        case HL:
        case SP:
        case IX:
        case IY:
          return true;
        default:
          return false;
      }
    }

    bool isImmediate() override { return false; }

    uint8_t getRegisterCode() {
      switch (reg) {
        case A:
          return 0x07;
        case B:
          return 0x00;
        case C:
          return 0x01;
        case D:
          return 0x02;
        case E:
          return 0x03;
        case H:
          return 0x04;
        case L:
          return 0x05;
        case BC:
          return 0x00;
        case DE:
          return 0x01;
        case HL:
          return 0x02;
        case SP:
          return 0x03;
        default:
          throw std::runtime_error("Unsupported register");
      }
    }

    void print(AsmPrinter *printer) override {
        printer->print(getRegisterName(reg), false);
    }

  private:
    Z80Register reg;
};

class Z80ImmediateOperand : public Z80Operand {
  public:
    Z80ImmediateOperand(int value) : value(value) {}

    bool isRegister() override { return false; }

    bool isRegisterPair() override { return false; }

    bool isImmediate() override { return true; }

    void print(AsmPrinter *printer) override {
        printer->print(std::to_string(value), false);
    }

    int getValue() { return value; }

  private:
    int value;
};

#endif // __Z80OPERAND_H