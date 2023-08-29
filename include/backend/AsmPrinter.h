#ifndef __ASM_PRINTER_H
#define __ASM_PRINTER_H

#include <fstream>
#include <iostream>
#include <ostream>
#include <stdint.h>
#include <string>

#include "backend/SymbolTable.h"

#include "AnalysisManager.h"
#include "Pass.h"

class MachineModule;

// Are we emitting textual assembly or binary machine code?
enum class AsmPrinterMode { TEXT, BINARY };

/**
 * Prints a MachineModule in assembly language.
 * The AsmPrinter is attached to a specific output stream.
 */
class AsmPrinter : public MachineModulePass {
  public:
    AsmPrinter(std::ostream &out, AsmPrinterMode mode) : out(out), mode(mode) {}

    /**
     * Prints a MachineModule
     */
    void run(MachineModule *module,
             MachineModuleAnalysisManager &MMAM) override;

    /**
     * Prints the program prologue.
     */
    virtual void emitProgramPrologue(MachineModule *module,
                                     const SymbolTable *table) {}

    /**
     * Prints the program epilogue.
     */
    virtual void emitProgramEpilogue(MachineModule *module,
                                     const SymbolTable *table) {}

    virtual void emitByte(uint8_t byte) const { out << byte; }

    void emitWord(uint16_t word) const {
        // Note: this is little endian.
        emitByte(word & 0xFF);
        emitByte((word >> 8) & 0xFF);
    }

    void emitDword(uint32_t dword) const {
        // Note: this is little endian.
        emitByte(dword & 0xFF);
        emitByte((dword >> 8) & 0xFF);
        emitByte((dword >> 16) & 0xFF);
        emitByte((dword >> 24) & 0xFF);
    }

    void emitBytes(std::string bytes, int length) const {
        int fromString = bytes.length() < length ? bytes.length() : length;

        for (int i = 0; i < fromString; i++) {
            emitByte(bytes[i]);
        }

        for (int i = fromString; i < length; i++) {
            emitByte(0x00);
        }
    }

    void print(std::string text, bool indent = false) {
        if (indent) {
            out << "\t";
        }
        out << text;
    }

    void printLine(std::string line, bool indent = true) {
        if (indent) {
            out << "\t";
        }
        out << line << std::endl;
    }

    void printLine() { out << std::endl; }

  protected:
    AsmPrinterMode mode;
    std::ostream &out;

    SymbolTable *symbolTable;
};

#endif // __ASM_PRINTER_H