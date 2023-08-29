#ifndef __Z80ISEL_H
#define __Z80ISEL_H

#include <iostream>
#include <string>

#include "Pass.h"
#include "backend/MachineFunction.h"
#include "backend/z80/Z80MemoryLocation.h"

/**
 * Instruction selection for the Z80 assembly language.
 */
class Z80ISel : public MachineFunctionPass {
  public:
    /**
     * Converts an IR module to Z80 assembly by selecting Z80 instructions.
     */
    void run(MachineFunction *function,
             MachineFunctionAnalysisManager &MFAM) override;

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
