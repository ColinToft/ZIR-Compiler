#include "backend/z80/Z80Instruction.h"
#include "backend/AsmPrinter.h"

void Z80CallInstruction::print(AsmPrinter *printer) {
    printer->printLine("call " + label);
}

void Z80CallInstruction::emit(AsmPrinter *printer,
                              const SymbolTable *symbolTable) {
    printer->emitByte(0xcd);
    printer->emitWord(symbolTable->getSymbol(label));
}

void Z80RetInstruction::print(AsmPrinter *printer) {
    printer->printLine("ret");
}

void Z80RetInstruction::emit(AsmPrinter *printer,
                             const SymbolTable *symbolTable) {
    printer->emitByte(0xc9);
}

void Z80LdInstruction::print(AsmPrinter *printer) {
    printer->print("ld ", true);
    dest->print(printer);
    printer->print(", ");
    src->print(printer);
    printer->printLine();
}

void Z80LdInstruction::emit(AsmPrinter *printer,
                            const SymbolTable *symbolTable) {
    if (dest->isRegisterPair() && src->isImmediate()) {
        Z80RegisterOperand *destReg = static_cast<Z80RegisterOperand *>(dest);
        int regCode = destReg->getRegisterCode();
        printer->emitByte((regCode << 4) | 0x01);

        Z80ImmediateOperand *srcImm = static_cast<Z80ImmediateOperand *>(src);
        printer->emitWord(srcImm->getValue());
    } else {
        throw UnsupportedFeatureException("Unsupported ld instruction");
    }
}

void Z80DBInstruction::print(AsmPrinter *printer) {
    printer->printLine(".db " + std::to_string((int)value));
}

void Z80DBInstruction::emit(AsmPrinter *printer,
                            const SymbolTable *symbolTable) {
    printer->emitByte(value);
}
