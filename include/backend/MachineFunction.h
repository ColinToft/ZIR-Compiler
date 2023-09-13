#ifndef __MACHINE_FUNCTION_H
#define __MACHINE_FUNCTION_H

#include <iostream>
#include <string>

#include "backend/MachineBasicBlock.h"
#include "backend/MachineInstruction.h"
#include "ir/Function.h"

/**
 * Represents a function in the machine representation.
 */
class MachineFunction {
  public:
    MachineFunction(Function *function) : function(function) {}

    ~MachineFunction() {
        for (auto machineBasicBlock : machineBasicBlocks) {
            delete machineBasicBlock;
        }
    }

    void addMachineBasicBlock(MachineBasicBlock *machineBasicBlock) {
        machineBasicBlocks.push_back(machineBasicBlock);
    }

    void print(AsmPrinter *printer) {
        for (auto machineBasicBlock : machineBasicBlocks) {
            machineBasicBlock->print(printer);
        }
    }

    Function *getFunction() { return function; }

    MachineBasicBlock *getEntryBlock() { return machineBasicBlocks[0]; }

    std::vector<MachineBasicBlock *> &getMachineBasicBlocks() {
        return machineBasicBlocks;
    }

    std::string getName() { return function->getName(); }

  private:
    Function *function;
    std::vector<MachineBasicBlock *> machineBasicBlocks;
};

#endif // __MACHINE_FUNCTION_H