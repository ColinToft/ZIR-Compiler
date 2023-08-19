#include "argparser.h"
#include "filehandler.h"
#include "ir/module.h"
#include "irgenerator.h"
#include "parser.h"
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
    ProgramNode *Program = parser.parse();

    std::ofstream out("out.zir");
    Module *module = IRGenerator().generate("main", Program);

    module->print(out);

    return 0;
}
