#include <fstream>
#include <iostream>

#include "ArgParser.h"
#include "FileHandler.h"
#include "Parser.h"
#include "ParserException.h"
#include "PassManager.h"

#include "backend/BackendPassBuilder.h"
#include "backend/MachineModule.h"
#include "backend/z80/Z80Backend.h"
#include "ir/IRGenerator.h"
#include "ir/Module.h"

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

    Module *module = IRGenerator().generate("MAIN", Program);

    std::ofstream out("main.zir");
    module->print(out);

    MachineModule *machineModule = new MachineModule(module, new Z80Backend());

    MachineModuleAnalysisManager MMAM;
    MachineFunctionAnalysisManager MFAM;

    BackendPassBuilder BPB;

    BPB.registerModuleAnalyses(MMAM);
    BPB.registerFunctionAnalyses(MFAM);

    BPB.crossRegisterManagers(MMAM, MFAM);

    std::ofstream asmFile("MAIN.8xp",
                          std::ios_base::out | std::ios_base::binary);
    MachineModulePassManager *MPM = BPB.buildBackendPassPipeline(
        asmFile, AsmPrinterMode::BINARY, machineModule->getBackend());

    MPM->run(machineModule, MMAM);
    return 0;
}
