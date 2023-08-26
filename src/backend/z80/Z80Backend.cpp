#include "backend/z80/Z80Backend.h"

#include <iostream>
#include <string>

#include "backend/z80/Z80Instruction.h"
#include "backend/z80/Z80Register.h"
#include "ir/Value.h"

std::vector<Z80MemoryLocation *>
Z80Backend::getMemoryLocationsForArguments(std::vector<Value *> values) {
    std::vector<Z80MemoryLocation *> memoryLocations;

    if (values.size() > 1) {
        throw std::runtime_error("Z80Backend::getMemoryLocationsForArguments: "
                                 "Currently only one argument is supported.");
    }

    if (values.size() == 0) {
        return memoryLocations;
    }

    if (values[0]->getType() != ZIRType(ZIRType::Int16)) {
        throw std::runtime_error("Z80Backend::getMemoryLocationsForArguments: "
                                 "Currently only register arguments are "
                                 "supported.");
    }

    memoryLocations.emplace_back(new Z80MemoryLocation(Z80Register::HL));

    return memoryLocations;
}
