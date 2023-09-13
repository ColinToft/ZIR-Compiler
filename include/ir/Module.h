#ifndef __MODULE_H
#define __MODULE_H

#include <iostream>
#include <string>
#include <vector>

#include "ir/Function.h"

/**
 * Module for the ZIR intermediate representation.
 */
class Module {
  public:
    Module(std::string name) : name(name) {}

    ~Module() {
        for (auto function : functions) {
            delete function;
        }
    }

    void addFunction(Function *function) { functions.push_back(function); }

    void print(std::ostream &out) {
        for (auto function : functions) {
            function->print(out);
        }
    }

    std::string getName() { return name; }

    std::vector<Function *> getFunctions() { return functions; }

  private:
    std::string name;
    std::vector<Function *> functions;
};

#endif // __MODULE_H