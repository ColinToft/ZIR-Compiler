# ZIR Compiler

The ZIR compiler is a compiler that uses an intermediate representation (a language in between a high-level language and assembly) in order to allow support for multiple programming languages and assembly targets.

## Quick Start

This project is built with CMake.
You can also run the `build.sh` script which automates the build process.

Running the compiler can be done as follows (example shown is for Linux):
Note that you can use the -o flag to name the resulting output file.

```bash
./bin/zen examples/print.zen  # Default: output a .8xp executable (Z80 assembly) that can be run on many TI calculators
./bin/zen examples/print.zen -o print.z80  # Output textual Z80 assembly
./bin/zen examples/print.zen -o print.zir  # Output textual intermediate representation

```

## Background and Goals

This compiler is part of a larger project of mine, the Zenith computer. This is a computer that I am building on a breadboard using integrated circuits for RAM, flash storage, small LCD display, and a Z80 CPU chip, among other things. The goal is for this computer to be built and wired by myself, and for me to have written every line of code (operating system and programs) that it runs. This is a fairly ambitious project, but my goal is to improve my knowledge about all aspects of computer science, including the low-level hardware, compiler, operating system, and high-level programming languages. For this reason, this project uses no external libraries, and is not a fork of an existing compiler, even though these may have helped speed up development and improve the compiler's efficiency. Thus, this project is mainly for educational purposes as opposed to building an extremely high-performance system.

## Compiler Design

The ZIR compiler is built in C++ and is inspired in many ways by the [LLVM Project](https://github.com/llvm/llvm-project).
Although I am primarily building the compiler to compile my Zen programming language to Z80 assembly language, since it uses an intermediate representation it would be fairly simple to add in support for other programming languages and other assembly backends.

## Current State

At the time of writing, the project was started quite recently and as such there is much more that remains to be implemented.
In its current state, the vast majority of the underlying infrastructure is built, and the compiler is able to successfully compile very simple programs.
Future work will mainly focus on adding additional features to the Zen programming language, and adding compiler optimization passes.

## Zen Programming Language

This is a C-inspired programming language that I am developing alongside this compiler.
Working examples of this programming language will be placed in the examples folder in the root of this repository, which can be compiled by the ZIR compiler.

Compilation is done using a hand-written recursive descent parser, then the abstract syntax tree is converted into the ZIR intermediate representation for further optimization and code generation.

## ZIR (Zen Intermediate Representation)

Most of the work that has gone into this compiler so far is constructing the ZIR intermediate reprentation and the associated framework.
Programming languages (such as the Zen programming language) are parsed into this intermediate representation, which then is optimized by running a sequence of optimization passes on the IR. These optimization passes could be run on a per-module, per-function, or per-loop basis depending on the optimization. The `PassManager` class is responsible for orchestrating and running different passes as required on the code.

Furthermore, analysis passes are used in order to generate useful information about the code without changing the code itself. For example, the `SymbolTableAnalysis` runs just before the assembly code is output, and generates a table of labels and their associated locations in the code. This analysis is required during the actual code generation phase.

## Z80 Backend

The first backend (assembly target) I have added to this compiler is the Z80 assembly language.
I chose this mainly because the processor itself is cheap and can be purchased in a format that can be directly used on a breadboard for testing.
It is also the same processor used many Texas Instruments graphing calculators.
Currently, the compiler will generate an .8xp executable by default, which runs on TI-83 and TI-84 series calculators.
