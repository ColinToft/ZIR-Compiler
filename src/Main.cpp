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
    std::string moduleName =
        filename.substr(0, filename.length() - 4); // Remove .zen extension

    std::string outputExtension = argParser.getOutputExtension();

    // Create the output stream. If the output is a binary file, open it in
    // binary mode. Otherwise, open it in text mode.
    std::ofstream out;
    if (outputExtension == ".8xp") {
        out = std::ofstream(argParser.outputFilename(),
                            std::ios_base::out | std::ios_base::binary);
    } else {
        out = std::ofstream(argParser.outputFilename());
    }

    FileHandler fileHandler;

    std::cout << "Reading file " << filename << std::endl;
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

    Module *module = IRGenerator().generate(moduleName, Program);

    // If the output file type is .zir, print the module to the .zir file
    if (argParser.outputFilename().substr(argParser.outputFilename().length() -
                                          4) == ".zir") {
        module->print(out);
        return 0;
    }

    MachineModule *machineModule = new MachineModule(module, new Z80Backend());

    MachineModuleAnalysisManager MMAM;
    MachineFunctionAnalysisManager MFAM;

    BackendPassBuilder BPB;

    BPB.registerModuleAnalyses(MMAM);
    BPB.registerFunctionAnalyses(MFAM);

    BPB.crossRegisterManagers(MMAM, MFAM);

    AsmPrinterMode mode = outputExtension == ".8xp" ? AsmPrinterMode::BINARY
                                                    : AsmPrinterMode::TEXT;
    MachineModulePassManager *MPM =
        BPB.buildBackendPassPipeline(out, mode, machineModule->getBackend());

    MPM->run(machineModule, MMAM);
    return 0;
}
