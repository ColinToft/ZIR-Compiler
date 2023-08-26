#ifndef __MACHINE_FUNCTION_PASS_H
#define __MACHINE_FUNCTION_PASS_H

#include <iostream>
#include <string>

#include "backend/MachineFunction.h"
#include "ir/Module.h"

/**
 * A MachineFunctionPass is a pass that operates on a MachineFunction.
 */
class MachineFunctionPass {
  public:
    /**
     * Runs the pass on a MachineFunction.
     */
    virtual void runOnMachineFunction(MachineFunction *module) = 0;
};

#endif // __MACHINE_FUNCTION_PASS_H