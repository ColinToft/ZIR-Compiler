#ifndef __ANALYSIS_MANAGER_PROXY_H
#define __ANALYSIS_MANAGER_PROXY_H

#include <iostream>

#include "Analysis.h"
#include "backend/MachineFunction.h"
#include "backend/MachineModule.h"

template <typename IRUnitT> class AnalysisManager;

enum AnalysisManagerProxyID {
    MachineFunctionAnalysisManagerMachineModuleProxyID,
    MachineModuleAnalysisManagerMachineFunctionProxyID
};

/**
 * An analysis pass that operates on a Module.
 */
template <typename IRUnitT, typename TargetManagerIRUnitT>
class AnalysisManagerProxy : public Analysis {
  public:
    AnalysisManagerProxy(AnalysisManager<TargetManagerIRUnitT> &manager)
        : manager(manager) {}

    virtual ~AnalysisManagerProxy() {}

    virtual AnalysisManager<TargetManagerIRUnitT> &getManager() {
        return manager;
    }

  private:
    AnalysisManager<TargetManagerIRUnitT> &manager;
};

typedef AnalysisManagerProxy<MachineFunction, MachineModule>
    MachineFunctionAnalysisManagerMachineModuleProxy;

typedef AnalysisManagerProxy<MachineModule, MachineFunction>
    MachineModuleAnalysisManagerMachineFunctionProxy;

#endif // __ANALYSIS_MANAGER_PROXY_H