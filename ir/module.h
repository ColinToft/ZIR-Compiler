#ifndef __MODULE_H
#define __MODULE_H

#include <iostream>
#include <string>
#include <vector>

#include "function.h"

/**
 * @brief
 * Module for the ZIR intermediate representation.
 */
class Module {
  public:
    Module(std::string name) : name(name) {}

    void addFunction(Function *function) { functions.push_back(function); }

    void print(std::ostream &out) {
        for (auto function : functions) {
            function->print(out);
        }
    }

  private:
    std::string name;
    std::vector<Function *> functions;
};

#endif // __MODULE_H