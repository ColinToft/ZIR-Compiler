#ifndef __BACKEND_H
#define __BACKEND_H

#include <iostream>
#include <string>
#include <vector>

class AsmPrinter;
enum class AsmPrinterMode;
class MachineFunction;
class MachineModule;

template <typename IRUnitT> class Pass;

typedef Pass<MachineModule> MachineModulePass;
typedef Pass<MachineFunction> MachineFunctionPass;

/**
 * Represents a backend for the ZIR compiler.
 */
class Backend {
  public:
    virtual ~Backend() {}

    virtual int getStartAddress() { return 0; }

    virtual MachineFunctionPass *createISelPass() = 0;

    virtual AsmPrinter *createAsmPrinter(std::ostream &out,
                                         AsmPrinterMode mode) = 0;
};

#endif // __BACKEND_H