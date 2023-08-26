#ifndef __MACHINE_PASS_MANAGER_H
#define __MACHINE_PASS_MANAGER_H

#include <iostream>
#include <string>

#include "backend/MachineFunctionPass.h"
#include "backend/MachineModule.h"

/**
 * Pass manager for the machine representation.
 * Only function passes are supported.
 */
class MachinePassManager {
  public:
    MachinePassManager() {}

    void addPass(MachineFunctionPass *pass) { passes.push_back(pass); }

    void runOnMachineModule(MachineModule *machineModule) {
        for (auto pass : passes) {
            for (auto machineFunction : machineModule->getMachineFunctions()) {
                pass->runOnMachineFunction(machineFunction);
            }
        }
    }

  private:
    std::vector<MachineFunctionPass *> passes;
};

#endif // __MACHINE_PASS_MANAGER_H