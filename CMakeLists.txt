cmake_minimum_required(VERSION 3.15)

project(Zen)

set(CMAKE_CXX_STANDARD 17)

add_executable(zen
    src/backend/z80/TIBuiltins.cpp
    src/backend/z80/Z80AsmPrinter.cpp
    src/backend/z80/Z80Backend.cpp
    src/backend/z80/Z80Instruction.cpp
    src/backend/z80/Z80ISel.cpp
    src/backend/z80/Z80Register.cpp
    src/backend/AsmPrinter.cpp
    src/backend/MachineBasicBlock.cpp
    src/backend/SymbolTable.cpp
    src/ir/Instruction.cpp
    src/ir/IRGenerator.cpp
    src/Lexer.cpp
    src/Main.cpp
    src/Parser.cpp
)

target_include_directories(zen PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS zen DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)