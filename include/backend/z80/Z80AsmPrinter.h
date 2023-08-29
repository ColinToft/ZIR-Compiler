#ifndef __Z80_ASM_PRINTER_H
#define __Z80_ASM_PRINTER_H

#include <iostream>
#include <stdint.h>
#include <string>

#include "backend/AsmPrinter.h"

/**
 * Prints a MachineModule in Z80 assembly language.
 */
class Z80AsmPrinter : public AsmPrinter {
  public:
    Z80AsmPrinter(std::ostream &out, AsmPrinterMode mode)
        : AsmPrinter(out, mode) {}

    /**
     * Prints the program prologue.
     */
    void emitProgramPrologue(MachineModule *module,
                             const SymbolTable *table) override;

    /**
     * Prints the program epilogue.
     */
    void emitProgramEpilogue(MachineModule *module,
                             const SymbolTable *table) override;

    /**
     * Emits the 8XP header for a program.
     */
    void emit8XPHeader(uint16_t moduleSize, std::string moduleName);

    /**
     * Emits the 8XP footer for a prorgam (the checksum).
     */
    void emit8XPFooter();

    /**
     * When emitting a byte, update the checksum.
     */
    void emitByte(uint8_t byte) const override;

  private:
    void resetChecksum() { checksum = 0; }

    mutable uint16_t checksum = 0;
};

#endif // __Z80_ASM_PRINTER_H