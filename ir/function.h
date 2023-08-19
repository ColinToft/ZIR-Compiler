#ifndef __FUNCTION_H
#define __FUNCTION_H

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "basicblock.h"

/**
 * @brief
 * Function for the ZIR intermediate representation.
 */
class Function {
  public:
    Function(ZIRType returnType, std::string name)
        : returnType(returnType), name(name) {}

    void addBasicBlock(BasicBlock *basicBlock) {
        basicBlocks.push_back(basicBlock);
    }

    void print(std::ostream &out) {
        out << "define ";
        returnType.print(out);
        out << " @" << name << "() {" << std::endl;
        for (auto basicBlock : basicBlocks) {
            basicBlock->print(out);
        }
        out << "}" << std::endl;
    }
    std::string getName() { return name; }

    BasicBlock *getEntryBlock() { return basicBlocks[0]; }

  private:
    std::string name;
    std::vector<BasicBlock *> basicBlocks;
    ZIRType returnType;
};

#endif // __FUNCTION_H