#ifndef __FUNCTION_H
#define __FUNCTION_H

#include <iostream>
#include <string>
#include <vector>

#include "basicblock.h"

/**
 * @brief
 * Function for the ZIR intermediate representation.
 */
class Function {
   public:
    Function(std::string name) : name(name) {}

    void addBasicBlock(BasicBlock* basicBlock) {
        basicBlocks.push_back(basicBlock);
    }

    void print(int indent) {
        std::cout << "Function(" << name << ") {" << std::endl;
        for (auto basicBlock : basicBlocks) {
            basicBlock->print();
        }
        std::cout << "}" << std::endl;
    }

    std::string getName() { return name; }

   private:
    std::string name;
    std::vector<BasicBlock*> basicBlocks;
};

#endif  // __FUNCTION_H