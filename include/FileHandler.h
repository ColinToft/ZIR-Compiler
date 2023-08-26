#ifndef __FILEHANDLER_H
#define __FILEHANDLER_H

#include <fstream>
#include <iostream>
#include <string>

/**
 * File handler for the Zen programming language compiler.
 */
class FileHandler {
  public:
    FileHandler() {}

    std::string readFile(std::string filename) {
        std::ifstream inputFile(filename);
        std::string inputText;
        if (inputFile.is_open()) {
            std::string line;
            while (std::getline(inputFile, line)) {
                inputText += line + "\n";
            }
            // Remove last newline
            inputText = inputText.substr(0, inputText.length() - 1);
            inputFile.close();
        } else {
            std::cout << "Unable to open file " << filename << std::endl;
            return "";
        }
        return inputText;
    }
};

#endif // __FILEHANDLER_H