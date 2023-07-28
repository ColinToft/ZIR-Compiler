#include <fstream>
#include <iostream>
#include "argparser.h"
#include "filehandler.h"
#include "parser.h"

int main(int argc, char const* argv[]) {
    ArgParser argParser(argc, argv);
    std::string filename = argParser.filename();
    FileHandler fileHandler;

    Lexer lexer(fileHandler.readFile(filename));
    std::vector<Token> tokens = lexer.tokenize();
    for (Token token : tokens) {
        token.print();
    }
    Parser parser(tokens);
    parser.parse()->print(0);

    return 0;
}
