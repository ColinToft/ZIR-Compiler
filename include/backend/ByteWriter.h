#ifndef __BYTE_WRITER_H
#define __BYTE_WRITER_H

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

/**
 * Writes assembly to a file.
 */
class ByteWriter {
  public:
    ByteWriter(std::string filename) : filename(filename), out(filename) {}

  private:
    std::string filename;
    mutable std::ofstream out;
};

#endif // __BYTE_WRITER_H