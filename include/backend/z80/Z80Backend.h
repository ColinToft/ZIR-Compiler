#ifndef __Z80BACKEND_H
#define __Z80BACKEND_H

#include <iostream>
#include <string>
#include <vector>

#include "backend/Backend.h"
#include "backend/z80/Z80AsmPrinter.h"
#include "backend/z80/Z80ISel.h"
#include "backend/z80/Z80MemoryLocation.h"
#include "ir/Value.h"

class Z80Backend : public Backend {
  public:
    int getStartAddress() override { return 0x9d95; }

    MachineFunctionPass *createISelPass() override { return new Z80ISel(); }

    AsmPrinter *createAsmPrinter(std::ostream &out,
                                 AsmPrinterMode mode) override {
        return new Z80AsmPrinter(out, mode);
    }

    static std::vector<Z80MemoryLocation *>
    getMemoryLocationsForArguments(std::vector<Value *> values);
};

#endif // __Z80BACKEND_H