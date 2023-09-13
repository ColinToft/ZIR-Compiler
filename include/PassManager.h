#ifndef __MACHINE_PASS_MANAGER_H
#define __MACHINE_PASS_MANAGER_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "Pass.h"
#include "backend/MachineModule.h"

/**
 * Pass manager class.
 * Responsible for running passes on some unit of IR.
 */
template <typename IRUnitT> class PassManager {

  public:
    ~PassManager() {
        for (auto pass : passes) {
            delete pass;
        }
    }

    void addPass(Pass<IRUnitT> *pass) { passes.push_back(pass); }

    void run(IRUnitT *IR, AnalysisManager<IRUnitT> &AM) {
        for (auto pass : passes) {
            pass->run(IR, AM);
        }
    }

  private:
    std::vector<Pass<IRUnitT> *> passes;
};

typedef PassManager<MachineModule> MachineModulePassManager;
typedef PassManager<MachineFunction> MachineFunctionPassManager;

#endif // __MACHINE_PASS_MANAGER_H