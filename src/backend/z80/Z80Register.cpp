#include "backend/z80/Z80Register.h"

std::string getRegisterName(Z80Register reg) {
    switch (reg) {
    case Z80Register::A:
        return "a";
    case Z80Register::B:
        return "b";
    case Z80Register::C:
        return "c";
    case Z80Register::D:
        return "d";
    case Z80Register::E:
        return "e";
    case Z80Register::H:
        return "h";
    case Z80Register::L:
        return "l";
    case Z80Register::AF:
        return "af";
    case Z80Register::BC:
        return "bc";
    case Z80Register::DE:
        return "de";
    case Z80Register::HL:
        return "hl";
    case Z80Register::SP:
        return "sp";
    case Z80Register::IX:
        return "ix";
    case Z80Register::IY:
        return "iy";
    default:
        return "unknown";
    }
};
