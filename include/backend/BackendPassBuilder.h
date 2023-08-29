#ifndef __BACKEND_PASS_BUILDER_H
#define __BACKEND_PASS_BUILDER_H

#include <iostream>
#include <memory>
#include <string>

#include "Analysis.h"
#include "backend/AsmPrinter.h"
#include "backend/Backend.h"
#include "backend/SymbolTableAnalysis.h"

#include "Pass.h"
#include "PassAdaptor.h"
#include "PassManager.h"
/**
 * Builds a backend pass pipeline and creates a MachineModulePassManager.
 */
class BackendPassBuilder {
  public:
    /**
     * Builds a backend pass pipeline and creates a MachineModulePassManager.
     */
    MachineModulePassManager *buildBackendPassPipeline(std::ostream &out,
                                                       AsmPrinterMode mode,
                                                       Backend *backend) {
        MachineModulePassManager *machineModulePassManager =
            new MachineModulePassManager();

        // Add passes to the pass manager.
        MachineFunctionPass *ISelPass = backend->createISelPass();
        machineModulePassManager->addPass(
            new MachineFunctionToMachineModulePassAdaptor(ISelPass));

        // AsmPrinter pass
        AsmPrinter *asmPrinter = backend->createAsmPrinter(out, mode);
        machineModulePassManager->addPass(asmPrinter);

        return machineModulePassManager;
    }

    void registerModuleAnalyses(MachineModuleAnalysisManager &MMAM) {
        MMAM.registerAnalysisPass(new SymbolTableAnalysisPass());
    }

    void registerFunctionAnalyses(MachineFunctionAnalysisManager &MFAM) {}

    void crossRegisterManagers(MachineModuleAnalysisManager &MMAM,
                               MachineFunctionAnalysisManager &MFAM) {
        MMAM.registerAnalysisManagerProxy(
            AnalysisManagerProxyID::
                MachineModuleAnalysisManagerMachineFunctionProxyID,
            new MachineModuleAnalysisManagerMachineFunctionProxy(MFAM));
    }
};

#endif // __BACKEND_PASS_BUILDER_H
