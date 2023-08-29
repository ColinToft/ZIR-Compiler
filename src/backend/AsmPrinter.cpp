#include "backend/AsmPrinter.h"

#include "backend/MachineFunction.h"
#include "backend/MachineModule.h"
#include "backend/SymbolTableAnalysis.h"

void AsmPrinter::run(MachineModule *module,
                     MachineModuleAnalysisManager &MMAM) {
    SymbolTable *table = MMAM.getAnalysis<SymbolTable>(module);

    // Program prologue
    emitProgramPrologue(module, table);

    for (auto machineFunction : module->getMachineFunctions()) {
        for (MachineBasicBlock *machineBasicBlock :
             machineFunction->getMachineBasicBlocks()) {
            if (mode == AsmPrinterMode::TEXT) {
                machineBasicBlock->print(this);
                printLine();
            } else {
                machineBasicBlock->emit(this, table);
            }
        }
    }

    // Program epilogue
    emitProgramEpilogue(module, table);
}