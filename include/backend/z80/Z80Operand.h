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
};

/**
 * Represents a register operand in Z80 assembly.
 */
class Z80RegisterOperand : public Z80Operand {
  public:
    Z80RegisterOperand(Z80Register reg) : reg(reg) {}

    void print(AsmPrinter *printer) {
        printer->print(getRegisterName(reg), false);
    }

  private:
    Z80Register reg;
};

class Z80ImmediateOperand : public Z80Operand {
  public:
    Z80ImmediateOperand(int value) : value(value) {}

    void print(AsmPrinter *printer) {
        printer->print(std::to_string(value), false);
    }

  private:
    int value;
};

#endif // __Z80OPERAND_H