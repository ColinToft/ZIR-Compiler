#include "backend/z80/Z80ISel.h"

#include <iostream>
#include <string>

#include "backend/MachineFunction.h"
#include "backend/z80/TIBuiltins.h"
#include "backend/z80/Z80Backend.h"

#include "ir/Function.h"
#include "ir/Instruction.h"

void Z80ISel::processCallInstruction(CallInstruction *callInstruction,
                                     MachineBasicBlock *machineBB) {
    // Get the memory locations for the arguments.
    std::vector<Z80MemoryLocation *> memoryLocations;

    if (TIBuiltins::isTIBuiltinFunc(callInstruction->getName())) {
        std::string bcallName =
            TIBuiltins::getBuiltinName(callInstruction->getName());

        // We have a TI builtin function call
        memoryLocations = TIBuiltins::getMemoryLocationsForBCall(bcallName);

        storeValues(callInstruction->getArguments(), memoryLocations,
                    machineBB);
        machineBB->addInstruction(new BCallInstruction(bcallName));

    } else {
        // We have a normal function call
        // TODO
    }
}

void Z80ISel::processReturnInstruction(ReturnInstruction *returnInstruction,
                                       MachineBasicBlock *machineBB) {
    // If we are returning void, just return.
    if (returnInstruction->getReturnType() == ZIRType(ZIRType::Void)) {
        machineBB->addInstruction(new Z80RetInstruction());
        return;
    } else {
        throw std::runtime_error(
            "Z80ISel::processReturnInstruction: Currently only void return "
            "types are supported.");
    }
}

void Z80ISel::run(MachineFunction *machineFunction,
                  MachineFunctionAnalysisManager &MFAM) {
    Function *function = machineFunction->getFunction();

    for (auto BB : function->getBasicBlocks()) {
        MachineBasicBlock *machineBB =
            new MachineBasicBlock(BB->getName(), machineFunction);
        machineFunction->addMachineBasicBlock(machineBB);

        for (auto instruction : BB->getInstructions()) {
            switch (instruction->getType()) {
            case Instruction::Type::CALL:
                processCallInstruction(
                    static_cast<CallInstruction *>(instruction), machineBB);
                break;

            case Instruction::Type::RETURN:
                processReturnInstruction(
                    static_cast<ReturnInstruction *>(instruction), machineBB);

            case Instruction::Type::BRANCH:
                // TODO
                break;

            case Instruction::Type::JUMP:
                // TODO
                break;
            }
        }
    }
}

void Z80ISel::storeValues(std::vector<Value *> values,
                          std::vector<Z80MemoryLocation *> memoryLocations,
                          MachineBasicBlock *machineBB) {
    for (int i = 0; i < memoryLocations.size(); i++) {
        Z80MemoryLocation *memoryLocation = memoryLocations[i];
        Value *value = values[i];

        if (value->isConstant() &&
            value->getType() == ZIRType(ZIRType::Int16) &&
            memoryLocation->isRegister()) {
            Constant *constant = static_cast<Constant *>(value);
            machineBB->addInstruction(new Z80LdInstruction(
                new Z80RegisterOperand(memoryLocation->getRegister()),
                new Z80ImmediateOperand(constant->getIntValue())));
        } else {
            throw std::runtime_error(
                "Z80ISel::storeValues: Currently only constant values are "
                "supported.");
        }
    }
}
