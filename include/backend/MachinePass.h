#ifndef __MACHINE_PASS_H
#define __MACHINE_PASS_H

#include <iostream>
#include <string>

#include "backend/MachineModule.h"

/**
 * Represents a pass in the machine representation.
 */
class MachinePass {
  public:
    virtual void runOnModule(MachineModule *machineModule) = 0;
};

#endif // __MACHINE_PASS_H
