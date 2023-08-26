#include "backend/z80/TIBuiltins.h"
#include "backend/AsmPrinter.h"

#include <ostream>

void BCallInstruction::print(AsmPrinter *printer) {
    printer->printLine("b_call(" + label + ")");
}

void BCallInstruction::emit(AsmPrinter *printer,
                            const SymbolTable &symbolTable) {
    printer->emitByte(0xef);
    printer->emitWord(tiCallMap[label]);
}