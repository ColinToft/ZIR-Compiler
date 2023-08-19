#include "instruction.h"
#include "basicblock.h"

#include <iostream>
#include <ostream>
#include <string>
#include <vector>

void FunctionCall::print(std::ostream &out) {
    out << "call @" << name << "(";
    for (auto argument : arguments) {
        argument->print(out);
        if (argument != arguments.back()) {
            out << ", ";
        }
    }

    out << ")" << std::endl;
}

void Branch::print(std::ostream &out) {
    out << "Branch {" << std::endl;
    condition->print(out);
    out << std::string(1, '\t') << "True: ";
    trueBlock->print(out);
    out << std::string(1, '\t') << "False: ";
    falseBlock->print(out);
    out << "}" << std::endl;
}