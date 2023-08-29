#ifndef __PASS_H
#define __PASS_H

#include <iostream>
#include <string>

#include "AnalysisManager.h"

#include "backend/MachineModule.h"

/**
 * Represents a pass in the machine representation.
 */
template <typename IRUnitT> class Pass {
  public:
    virtual void run(IRUnitT *IR, AnalysisManager<IRUnitT> &AM) = 0;
};

typedef Pass<MachineModule> MachineModulePass;
typedef Pass<MachineFunction> MachineFunctionPass;

#endif // __PASS_H
