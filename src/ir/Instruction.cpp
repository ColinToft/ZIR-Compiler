#include "ir/Instruction.h"
#include "ir/BasicBlock.h"

#include <iostream>
#include <string>
#include <vector>

void CallInstruction::print(std::ostream &out) {
    out << "call @" << name << "(";
    for (auto argument : arguments) {
        argument->print(out);
        if (argument != arguments.back()) {
            out << ", ";
        }
    }

    out << ")" << std::endl;
}

void BranchInstruction::print(std::ostream &out) {
    out << "Branch {" << std::endl;
    condition->print(out);
    out << std::string(1, '\t') << "True: ";
    trueBlock->print(out);
    out << std::string(1, '\t') << "False: ";
    falseBlock->print(out);
    out << "}" << std::endl;
}

void ReturnInstruction::print(std::ostream &out) {
    out << "return ";
    value->print(out);
    out << std::endl;
}
