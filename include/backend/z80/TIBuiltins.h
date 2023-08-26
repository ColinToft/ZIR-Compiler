#ifndef __TI_BUILTINS_H
#define __TI_BUILTINS_H

#include <iostream>
#include <string>
#include <unordered_map>

#include "backend/AsmPrinter.h"
#include "backend/ByteWriter.h"
#include "backend/SymbolTable.h"
#include "backend/z80/Z80AsmPrinter.h"
#include "backend/z80/Z80Backend.h"
#include "backend/z80/Z80Instruction.h"

/**
 * Maps TI calls to their corresponding address.
 */
static std::unordered_map<std::string, uint16_t> tiCallMap = {
    {"_DispHL", 0x4507},
};

static std::unordered_map<std::string, std::vector<Z80MemoryLocation *>>
    tiCallMemoryMap = {
        {"_DispHL", {new Z80MemoryLocation(Z80Register::HL)}},
};

class TIBuiltins {
  public:
    static bool isTIBuiltinFunc(std::string functionName) {
        return functionName ==
               "print"; // TODO this is temporary, eventually this
                        // should be named ti.print, in a ti module
    }

    static std::vector<Z80MemoryLocation *>
    getMemoryLocationsForBCall(std::string label) {
        return tiCallMemoryMap[label];
    }

    static std::string getBuiltinName(std::string functionName) {
        if (functionName == "print") {
            return "_DispHL"; // TODO temporary, see above
        }

        return functionName;
    }
};

/**
 * Represents a TI BCall instruction.
 */
class BCallInstruction : public Z80Instruction {
  public:
    BCallInstruction(std::string label) : label(label) {}

    void print(AsmPrinter *printer) override;

    void emit(AsmPrinter *printer, const SymbolTable &symbolTable) override;

    int size() override { return 3; }

  private:
    std::string label;
};

#endif // __TI_BUILTINS_H