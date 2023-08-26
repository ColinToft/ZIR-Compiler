#ifndef __SYMBOLTABLE_H
#define __SYMBOLTABLE_H

#include <iostream>
#include <string>
#include <unordered_map>

/**
 * Represents a symbol table.
 */
class SymbolTable {
  public:
    SymbolTable() {}

    void addSymbol(std::string name, uint16_t address) {
        symbols[name] = address;
    }

    uint16_t getSymbol(std::string name) const { return symbols.at(name); }

  private:
    std::unordered_map<std::string, uint16_t> symbols;
};

#endif // __SYMBOLTABLE_H