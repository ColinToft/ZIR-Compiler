#include "ArgParser.h"
#include "FileHandler.h"
#include "Parser.h"
#include "ParserException.h"
#include "backend/AsmPrinter.h"
#include "backend/MachineModule.h"
#include "backend/MachinePassManager.h"
#include "backend/z80/Z80AsmPrinter.h"
#include "backend/z80/Z80ISel.h"
#include "ir/IRGenerator.h"
#include "ir/Module.h"
#include <fstream>
#include <iostream>

int main(int argc, char const *argv[]) {
    ArgParser argParser(argc, argv);
    std::string filename = argParser.filename();
    FileHandler fileHandler;

    Lexer lexer(fileHandler.readFile(filename));
    std::vector<Token> tokens = lexer.tokenize();
    for (Token token : tokens) {
        token.print();
    }

    Parser parser(tokens);

    ProgramNode *Program;
    try {
        Program = parser.parse();
    } catch (ParserException &e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    std::cout << "checkpoint 2" << std::endl;

    Module *module = IRGenerator().generate("main", Program);

    std::ofstream out("out.zir");
    module->print(out);

    std::cout << "IR module has been created\n" << std::endl;

    MachineModule *machineModule = new MachineModule(module, new Z80Backend());

    std::cout << "Machine module has been created\n" << std::endl;

    MachinePassManager machinePassManager;
    machinePassManager.addPass(new Z80ISel());

    machinePassManager.runOnMachineModule(machineModule);

    std::ofstream out2("out.z80");
    Z80AsmPrinter(out2, AsmPrinter::TEXT).emit(machineModule);

    return 0;
}
