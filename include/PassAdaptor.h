#ifndef __PASS_ADAPTOR_H
#define __PASS_ADAPTOR_H

#include "Pass.h"

/**
 * Adapts a MachineFunctionPass to a MachineModulePass.
 */
class MachineFunctionToMachineModulePassAdaptor : public MachineModulePass {
  public:
    MachineFunctionToMachineModulePassAdaptor(MachineFunctionPass *pass)
        : pass(pass) {}

    ~MachineFunctionToMachineModulePassAdaptor() { delete pass; }

    void run(MachineModule *module,
             MachineModuleAnalysisManager &MMAM) override {
        for (auto &machineFunction : module->getMachineFunctions()) {
            pass->run(machineFunction,
                      MMAM.getAnalysisManager<MachineFunction>());
        }
    }

  private:
    MachineFunctionPass *pass;
};

#endif // __PASS_ADAPTOR_H