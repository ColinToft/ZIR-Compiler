#ifndef __MACHINE_BASIC_BLOCK_H
#define __MACHINE_BASIC_BLOCK_H

#include <iostream>
#include <string>

#include "backend/AsmPrinter.h"
#include "backend/MachineInstruction.h"

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

    std::string getName() { return name; }

    MachineFunction *getParent() { return parent; }

  private:
    std::vector<MachineInstruction *> machineInstructions;
    std::string name;
    MachineFunction *parent;
};

#endif // __MACHINE_BASIC_BLOCK_H