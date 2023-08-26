#include "backend/MachineBasicBlock.h"
#include "backend/MachineFunction.h"

void MachineBasicBlock::print(AsmPrinter *printer) {
    printer->printLine(parent->getName() + "!" + name + ":", false);
    for (auto machineInstruction : machineInstructions) {
        machineInstruction->print(printer);
    }
}