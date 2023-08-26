#ifndef __BASICBLOCK_H
#define __BASICBLOCK_H

#include <iostream>
#include <string>
#include <vector>

#include "ir/Instruction.h"

/**
 * Basic block for the ZIR intermediate representation.
 */
class BasicBlock {
  public:
    BasicBlock(std::string name) : name(name) {}

    void addInstruction(Instruction *instruction) {
        instructions.push_back(instruction);
    }

    void print(std::ostream &out) {
        out << name << ":" << std::endl;
        for (auto instruction : instructions) {
            out << "    ";
            instruction->print(out);
        }
    }

    std::string getName() { return name; }

    std::vector<Instruction *> &getInstructions() { return instructions; }

  private:
    std::string name;
    std::vector<Instruction *> instructions;
};

#endif // __BASICBLOCK_H