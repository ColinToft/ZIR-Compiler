#ifndef __MACHINE_MODULE_H
#define __MACHINE_MODULE_H

#include <iostream>
#include <string>

#include "backend/Backend.h"
#include "backend/MachineFunction.h"
#include "ir/Module.h"

/**
 * Module for the machine IR backend representation.
 */
class MachineModule {
  public:
    MachineModule(Module *module, Backend *backend)
        : module(module), backend(backend) {
        for (auto function : module->getFunctions()) {
            machineFunctions.push_back(new MachineFunction(function));
        }
    }

    void addMachineFunction(MachineFunction *machineFunction) {
        machineFunctions.push_back(machineFunction);
    }

    void print(AsmPrinter *printer) {
        for (auto machineFunction : machineFunctions) {
            machineFunction->print(printer);
        }
    }

    Module *getModule() { return module; }

    Backend *getBackend() { return backend; }

    std::string getName() { return module->getName(); }

    std::vector<MachineFunction *> getMachineFunctions() {
        return machineFunctions;
    }

  private:
    Module *module;
    Backend *backend;
    std::vector<MachineFunction *> machineFunctions;
};

#endif // __MACHINE_MODULE_H