#ifndef __Z80_ASM_PRINTER_H
#define __Z80_ASM_PRINTER_H

#include <iostream>
#include <string>

#include "backend/AsmPrinter.h"

/**
 * Prints a MachineModule in Z80 assembly language.
 */
class Z80AsmPrinter : public AsmPrinter {
  public:
    Z80AsmPrinter(std::ostream &out, PrinterMode mode)
        : AsmPrinter(out, mode) {}

    /**
     * Prints the program prologue.
     */
    void emitProgramPrologue() override;
};

#endif // __Z80_ASM_PRINTER_H