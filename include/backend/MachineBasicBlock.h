#ifndef __MACHINE_BASIC_BLOCK_H
#define __MACHINE_BASIC_BLOCK_H

#include <iostream>
#include <string>
#include <vector>

#include "backend/MachineInstruction.h"
#include "backend/SymbolTable.h"

class AsmPrinter;
class MachineFunction;

/**
 * Represents a basic block in the machine representation.
 */
class MachineBasicBlock {
  public:
    MachineBasicBlock(std::string name, MachineFunction *parent)
        : name(name), parent(parent) {}

    void addInstruction(MachineInstruction *machineInstruction) {
        machineInstructions.push_back(machineInstruction);
    }

    std::vector<MachineInstruction *> getMachineInstructions() {
        return machineInstructions;
    }

    void print(AsmPrinter *printer);

    void emit(AsmPrinter *printer, const SymbolTable *symbolTable);

    std::string getName() { return name; }

    std::string getLabelName();

    MachineFunction *getParent() { return parent; }

  private:
    std::vector<MachineInstruction *> machineInstructions;
    std::string name;
    MachineFunction *parent;
};

#endif // __MACHINE_BASIC_BLOCK_H