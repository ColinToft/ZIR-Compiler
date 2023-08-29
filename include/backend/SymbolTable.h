#ifndef __SYMBOLTABLE_H
#define __SYMBOLTABLE_H

#include <iostream>
#include <stdint.h>
#include <string>
#include <unordered_map>

#include "Analysis.h"

/**
 * Represents a symbol table.
 */
class SymbolTable : public Analysis {
  public:
    SymbolTable() {}

    void addSymbol(std::string name, int address) { symbols[name] = address; }

    void setStartAddress(int address) { symbols["$start"] = address; }

    int getStartAddress() const { return symbols.at("$start"); }

    void setEndAddress(int address) { symbols["$end"] = address; }

    int getEndAddress() const { return symbols.at("$end"); }

    int getProgramSize() const { return getEndAddress() - getStartAddress(); }

    int getSymbol(std::string name) const { return symbols.at(name); }

    static AnalysisID ID;

  private:
    std::unordered_map<std::string, int> symbols;
};

#endif // __SYMBOLTABLE_H