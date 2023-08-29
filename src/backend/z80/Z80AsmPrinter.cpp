#include "backend/z80/Z80AsmPrinter.h"

#include "backend/MachineModule.h"

void Z80AsmPrinter::emitProgramPrologue(MachineModule *module,
                                        const SymbolTable *table) {
    // TI-83+ program header
    if (mode == AsmPrinterMode::BINARY) {
        emit8XPHeader(table->getProgramSize(), module->getName());
        emitByte(0xbb);
        emitByte(0x6d);
    } else {
        printLine(".nolist", false);
        printLine("#include \"ti83plus.inc\"", false);
        printLine(".list", false);
        printLine();
        printLine(".org userMem-2", false);
        printLine(".db t2ByteTok, tAsmCmp", false);
        printLine();
    }
}

void Z80AsmPrinter::emitProgramEpilogue(MachineModule *module,
                                        const SymbolTable *table) {
    if (mode == AsmPrinterMode::BINARY) {
        emit8XPFooter();
    }
}

void Z80AsmPrinter::emit8XPHeader(uint16_t programSize,
                                  std::string moduleName) {
    // TI Variable file format
    emitBytes("**TI83F*", 8); // 8-byte signature
    // Further signature
    emitByte(0x1a);
    emitByte(0x0a);
    emitByte(0x00);

    // Comment (max 42 chars)
    std::string comment = "Created by Zenith Z80 Assembler";

    emitBytes(comment, 42);

    // Length of the data section
    emitWord(programSize + 19 + 2); // 19 bytes of header data after this field

    // All sizes are +2 for the 0xbb and 0x6d bytes

    // Data section
    resetChecksum();

    // Always 0x000d
    emitWord(0x000d);

    // Length of the variable data
    emitWord(programSize + 2 + 2);

    // Variable type ID
    emitByte(0x06); // 0x06 = program

    // Program name (max 8 chars)
    emitBytes(moduleName, 8);

    // Program version
    emitByte(0x00);

    // Program flags
    emitByte(0x00);

    // Size of the program
    emitWord(programSize + 2 + 2);

    emitWord(programSize + 2);
}

void Z80AsmPrinter::emit8XPFooter() {
    // Checksum
    emitWord(checksum);
}

void Z80AsmPrinter::emitByte(uint8_t byte) const {
    AsmPrinter::emitByte(byte);
    checksum += byte;
}