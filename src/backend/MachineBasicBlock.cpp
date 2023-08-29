#include "backend/MachineBasicBlock.h"

#include "backend/AsmPrinter.h"
#include "backend/MachineFunction.h"
#include "backend/MachineInstruction.h"

void MachineBasicBlock::print(AsmPrinter *printer) {
    printer->printLine(getLabelName() + ":", false);
    for (MachineInstruction *machineInstruction : machineInstructions) {
        machineInstruction->print(printer);
    }
}

void MachineBasicBlock::emit(AsmPrinter *printer, const SymbolTable *table) {
    for (MachineInstruction *machineInstruction : machineInstructions) {
        machineInstruction->emit(printer, table);
    }
}

std::string MachineBasicBlock::getLabelName() {
    return parent->getName() + "!" + name;
}