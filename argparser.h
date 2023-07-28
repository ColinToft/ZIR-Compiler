#ifndef __ARGPARSER_H
#define __ARGPARSER_H

#include <stdexcept>
#include <string>

/**
 * @brief
 * Argument parser for the Zen programming language compiler.
 */
class ArgParser {
   public:
    ArgParser(int argc, char const* argv[]) : argc(argc), argv(argv) {
        if (argc < 2) {
            throw std::runtime_error("No input file specified.");
        }

        if (argc > 2) {
            throw std::runtime_error("Too many arguments.");
        }

        if (std::string(argv[1]).length() < 5) {
            throw std::runtime_error("Input file must have .zen extension.");
        }

        if (std::string(argv[1]).substr(std::string(argv[1]).length() - 4) !=
            ".zen") {
            throw std::runtime_error("Input file must have .zen extension.");
        }

        _filename = std::string(argv[1]);
    }

    std::string filename() { return _filename; }

   private:
    int argc;
    char const** argv;

    std::string _filename;
};

#endif  // __ARGPARSER_H