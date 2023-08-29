#ifndef __SYMBOL_TABLE_ANALYSIS_H
#define __SYMBOL_TABLE_ANALYSIS_H

#include "AnalysisPass.h"
#include "backend/SymbolTable.h"

/**
 * Constructs a symbol table for the MachineModule.
 * Similar to the first pass of an assembler.
 */
class SymbolTableAnalysisPass : public MachineModuleAnalysisPass {
  public:
    SymbolTableAnalysisPass() {}

    Analysis *run(MachineModule *module) override {
        SymbolTable *table = new SymbolTable();

        uint16_t address = module->getBackend()->getStartAddress();

        table->setStartAddress(address);

        for (auto machineFunction : module->getMachineFunctions()) {
            for (MachineBasicBlock *machineBasicBlock :
                 machineFunction->getMachineBasicBlocks()) {
                table->addSymbol(machineBasicBlock->getLabelName(), address);

                for (MachineInstruction *machineInstruction :
                     machineBasicBlock->getMachineInstructions()) {
                    address += machineInstruction->size();
                }
            }
        }

        table->setEndAddress(address);

        return table;
    }

    AnalysisID getID() override { return AnalysisID::SYMBOL_TABLE; }
};

#endif // __SYMBOL_TABLE_ANALYSIS_H