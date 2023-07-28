#include "instruction.h"
#include "basicblock.h"

#include <iostream>
#include <string>
#include <vector>

void FunctionCall::print() {
    std::cout << "call " << name << "(";
    for (auto argument : arguments) {
        argument->print();
        if (argument != arguments.back()) std::cout << ", ";
    }

    std::cout << ")" << std::endl;
}

void Branch::print() {
    std::cout << "Branch {" << std::endl;
    condition->print();
    std::cout << std::string(1, '\t') << "True: ";
    trueBlock->print();
    std::cout << std::string(1, '\t') << "False: ";
    falseBlock->print();
    std::cout << "}" << std::endl;
}