#include "backend/AsmPrinter.h"

#include "backend/MachineFunction.h"
#include "backend/MachineModule.h"

void AsmPrinter::emit(MachineModule *module) {
    // Program prologue
    emitProgramPrologue();

    for (auto machineFunction : module->getMachineFunctions()) {
        for (auto machineBasicBlock :
             machineFunction->getMachineBasicBlocks()) {
            machineBasicBlock->print(this);
            printLine();
        }
    }
}