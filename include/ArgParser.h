#ifndef __ARGPARSER_H
#define __ARGPARSER_H

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ArgumentException.h"

/**
 * Argument parser for the Zen programming language compiler.
 */
class ArgParser {
  public:
    ArgParser(int argc, char const *argv[]) : argc(argc), argv(argv) {
        if (argc < 2) {
            throw ArgumentException("No input file specified.");
        }

        if (std::string(argv[1]).length() < 5) {
            throw ArgumentException("Input file must have .zen extension.");
        }

        if (std::string(argv[1]).substr(std::string(argv[1]).length() - 4) !=
            ".zen") {
            throw ArgumentException("Input file must have .zen extension.");
        }

        for (int i = 1; i < argc; i++) {
            if (std::string(argv[i]) == "-o") {
                if (i + 1 >= argc) {
                    throw ArgumentException("No output file specified.");
                }

                outputFile = std::string(argv[i + 1]);
                i++;
            } else {
                inputFile = std::string(argv[i]);
            }
        }
    }

    std::string filename() { return inputFile; }

    std::string outputFilename() {
        if (outputFile == "") {
            // Default to input file name with .8xp extension
            // Make sure input file name is put in all caps, and has a maximum
            // length of 8 characters
            for (int i = 0; i < inputFile.length(); i++) {
                if (i >= 8 || inputFile.at(i) == '.') {
                    break;
                }

                outputFile += toupper(inputFile.at(i));
            }

            outputFile += ".8xp";
        }
        return outputFile;
    }

    std::string getOutputExtension() {
        if (outputFile == "") {
            return ".8xp";
        } else {
            return outputFile.substr(outputFile.find_last_of('.'));
        }
    }

  private:
    int argc;
    char const **argv;

    std::string inputFile;

    std::string outputFile;
};

#endif // __ARGPARSER_H