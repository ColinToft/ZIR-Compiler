#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <iostream>
#include <string>
#include <vector>

#include "value.h"

class BasicBlock;

class Instruction {
  public:
    Instruction() {}
    virtual ~Instruction() {}
    virtual void print(std::ostream &out) = 0;
};

class FunctionCall : public Instruction {
  public:
    FunctionCall(std::string name, std::vector<Value *> arguments)
        : name(name), arguments(arguments) {}

    void print(std::ostream &out);

  private:
    std::string name;
    std::vector<Value *> arguments;
};

class Branch : public Instruction {
  public:
    Branch(Value *condition, BasicBlock *trueBlock, BasicBlock *falseBlock)
        : condition(condition), trueBlock(trueBlock), falseBlock(falseBlock) {}

    void print(std::ostream &out);

  private:
    Value *condition;
    BasicBlock *trueBlock;
    BasicBlock *falseBlock;
};

class Jump : public Instruction {
  public:
    Jump(BasicBlock *block) : block(block) {}

    void print(std::ostream &out);

  private:
    BasicBlock *block;
};

#endif // __INSTRUCTION_H