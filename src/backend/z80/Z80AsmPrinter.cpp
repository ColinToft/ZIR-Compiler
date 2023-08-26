#include "backend/z80/Z80AsmPrinter.h"

void Z80AsmPrinter::emitProgramPrologue() {
    // TI-83+ program header
    if (mode == BINARY) {
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