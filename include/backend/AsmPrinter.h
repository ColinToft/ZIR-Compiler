#ifndef __ASM_PRINTER_H
#define __ASM_PRINTER_H

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

class MachineModule;

/**
 * Prints a MachineModule in assembly language.
 * The AsmPrinter is attached to a specific output stream.
 */
class AsmPrinter {
  public:
    // Are we emitting textual assembly or binary machine code?
    enum PrinterMode { TEXT, BINARY };

    AsmPrinter(std::ostream &out, PrinterMode mode) : out(out), mode(mode) {}

    /**
     * Prints a MachineModule
     */
    void emit(MachineModule *module);

    /**
     * Prints the program prologue.
     */
    virtual void emitProgramPrologue() {}

    void emitByte(uint8_t byte) const { out << byte; }

    void emitWord(uint16_t word) const {
        // Note: this is little endian.
        out << (uint8_t)(word & 0xFF);
        out << (uint8_t)((word >> 8) & 0xFF);
    }

    void emitDword(uint32_t dword) const {
        // Note: this is little endian.
        out << (uint8_t)(dword & 0xFF);
        out << (uint8_t)((dword >> 8) & 0xFF);
        out << (uint8_t)((dword >> 16) & 0xFF);
        out << (uint8_t)((dword >> 24) & 0xFF);
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
    PrinterMode mode;
    std::ostream &out;
};

#endif // __ASM_PRINTER_H