#ifndef __Z80INSTRUCTION_H
#define __Z80INSTRUCTION_H

#include <iostream>
#include <string>

#include "backend/AsmPrinter.h"
#include "backend/MachineInstruction.h"
#include "backend/z80/Z80Operand.h"

typedef uint8_t byte;

class Z80Instruction : public MachineInstruction {};

/**
 * Represents a Z80 call instruction.
 */
class Z80CallInstruction : public Z80Instruction {
  public:
    Z80CallInstruction(std::string label) : label(label) {}

    void print(AsmPrinter *printer) override;

    void emit(AsmPrinter *printer, const SymbolTable &symbolTable) override;

    int size() override { return 3; }

  private:
    std::string label;
};

/**
 * Represents a Z80 ret instruction.
 */
class Z80RetInstruction : public Z80Instruction {
  public:
    void print(AsmPrinter *printer) override;

    void emit(AsmPrinter *printer, const SymbolTable &symbolTable) override;

    int size() override { return 1; }
};

/**
 * Represents a Z80 ld instruction.
 */
class Z80LdInstruction : public Z80Instruction {
  public:
    Z80LdInstruction(Z80Operand *dest, Z80Operand *src)
        : dest(dest), src(src) {}

    void print(AsmPrinter *printer) override;

    void emit(AsmPrinter *printer, const SymbolTable &symbolTable) override;

    int size() override { return 1; }

  private:
    Z80Operand *dest;
    Z80Operand *src;
};

class Z80DBInstruction : public Z80Instruction {
  public:
    Z80DBInstruction(byte value) : value(value) {}

    void print(AsmPrinter *printer) override;

    void emit(AsmPrinter *printer, const SymbolTable &symbolTable) override;

    int size() override { return 1; }

  private:
    byte value;
};

#endif // __Z80INSTRUCTION_H