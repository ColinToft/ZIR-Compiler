#ifndef __MACHINE_INSTRUCTION_H
#define __MACHINE_INSTRUCTION_H

#include <iostream>
#include <string>

#include "backend/SymbolTable.h"

class AsmPrinter;

/**
 * Represents an assembly instruction.
 */
class MachineInstruction {
  public:
    virtual void print(AsmPrinter *printer) = 0;

    virtual void emit(AsmPrinter *printer, const SymbolTable &symbolTable) = 0;

    /**
     * Returns the size of the instruction in bytes.
     */
    virtual int size() = 0;

  private:
    std::string name;
};

#endif // __MACHINE_INSTRUCTION_H