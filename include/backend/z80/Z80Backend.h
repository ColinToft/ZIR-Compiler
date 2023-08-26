#ifndef __Z80BACKEND_H
#define __Z80BACKEND_H

#include <iostream>
#include <string>
#include <vector>

#include "backend/Backend.h"
#include "backend/z80/Z80Operand.h"
#include "backend/z80/Z80Register.h"
#include "ir/Value.h"

// A memory location can be either a register or a stack offset.
class Z80MemoryLocation {
  public:
    Z80MemoryLocation(Z80Register reg) : reg(reg) {}
    Z80MemoryLocation(int offset) : offset(offset) {}

    bool isRegister() { return isReg; }
    bool isOffset() { return !isReg; }

    Z80Register getRegister() { return reg; }
    int getOffset() { return offset; }

  private:
    bool isReg;
    union {
        Z80Register reg;
        int offset;
    };
};

class Z80Backend : public Backend {
  public:
    static std::vector<Z80MemoryLocation *>
    getMemoryLocationsForArguments(std::vector<Value *> values);
};

#endif // __Z80BACKEND_H