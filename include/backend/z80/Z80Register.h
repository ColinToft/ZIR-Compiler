#ifndef __Z80REGISTER_H
#define __Z80REGISTER_H

#include <iostream>
#include <stdint.h>
#include <string>

/**
 * Represents a register in Z80 assembly.
 */
enum Z80Register {
    A,
    B,
    C,
    D,
    E,
    H,
    L,
    AF,
    BC,
    DE,
    HL,
    SP,
    IX,
    IY,
};

/**
 * Returns the name of the register.
 */
std::string getRegisterName(Z80Register reg);

#endif // __Z80REGISTER_H