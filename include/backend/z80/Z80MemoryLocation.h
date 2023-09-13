#ifndef __Z80_MEMORY_LOCATION_H
#define __Z80_MEMORY_LOCATION_H

#include "backend/z80/Z80Operand.h"
#include "backend/z80/Z80Register.h"

// A memory location can be either a register or a stack offset.
class Z80MemoryLocation {
  public:
    Z80MemoryLocation(Z80Register reg) : reg(reg), isReg(true) {}
    Z80MemoryLocation(int offset) : offset(offset), isReg(false) {}

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

#endif // __Z80_MEMORY_LOCATION_H