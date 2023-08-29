#ifndef __MACHINE_ANALYSIS_PASS_H
#define __MACHINE_ANALYSIS_PASS_H

#include <iostream>

#include "Analysis.h"
#include "backend/MachineFunction.h"
#include "backend/MachineModule.h"

/**
 * An analysis pass that operates on a Module.
 */
template <typename IRUnitT> class AnalysisPass {
  public:
    virtual Analysis *run(IRUnitT *IR) = 0;

    virtual AnalysisID getID() = 0;
};

typedef AnalysisPass<MachineModule> MachineModuleAnalysisPass;
typedef AnalysisPass<MachineFunction> MachineFunctionAnalysisPass;

#endif // __MACHINE_ANALYSIS_PASS_H