#ifndef __Z80ISEL_H
#define __Z80ISEL_H

#include <iostream>
#include <string>

#include "backend/MachineFunction.h"
#include "backend/MachineFunctionPass.h"
#include "backend/z80/Z80Backend.h"

/**
 * Instruction selection for the Z80 assembly language.
 */
class Z80ISel : public MachineFunctionPass {
  public:
    /**
     * Converts an IR module to Z80 assembly by selecting Z80 instructions.
     */
    void runOnMachineFunction(MachineFunction *function) override;

  private:
    void processCallInstruction(CallInstruction *callInstruction,
                                MachineBasicBlock *machineBB);

    void processReturnInstruction(ReturnInstruction *returnInstruction,
                                  MachineBasicBlock *machineBB);

    void storeValues(std::vector<Value *> values,
                     std::vector<Z80MemoryLocation *> memoryLocations,
                     MachineBasicBlock *machineBB);
};

#endif // __Z80ISEL_H
