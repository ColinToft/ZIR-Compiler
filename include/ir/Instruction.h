#ifndef __INSTRUCTION_H
#define __INSTRUCTION_H

#include <iostream>
#include <string>
#include <vector>

#include "ir/Value.h"

class BasicBlock;

class Instruction {

  public:
    enum Type {
        CALL = 0,
        BRANCH = 1,
        JUMP = 2,
        RETURN = 3,
    };

    Instruction(Type type) : type(type) {}
    virtual ~Instruction() {}
    virtual void print(std::ostream &out) = 0;

    Type getType() { return type; }

  private:
    Type type;
};

class CallInstruction : public Instruction {
  public:
    CallInstruction(std::string name, std::vector<Value *> arguments)
        : Instruction(CALL), name(name), arguments(arguments) {}

    ~CallInstruction() {
        for (auto argument : arguments) {
            delete argument;
        }
    }

    void print(std::ostream &out);

    std::string getName() { return name; }

    std::vector<Value *> &getArguments() { return arguments; }

  private:
    std::string name;
    std::vector<Value *> arguments;
};

class BranchInstruction : public Instruction {
  public:
    BranchInstruction(Value *condition, BasicBlock *trueBlock,
                      BasicBlock *falseBlock)
        : Instruction(BRANCH), condition(condition), trueBlock(trueBlock),
          falseBlock(falseBlock) {}

    ~BranchInstruction() { delete condition; }

    void print(std::ostream &out);

  private:
    Value *condition;
    BasicBlock *trueBlock;
    BasicBlock *falseBlock;
};

class ReturnInstruction : public Instruction {
  public:
    ReturnInstruction(Value *value) : Instruction(RETURN), value(value) {}

    ~ReturnInstruction() { delete value; }

    void print(std::ostream &out);

    ZIRType getReturnType() { return value->getType(); }

  private:
    Value *value;
};

class JumpInstruction : public Instruction {
  public:
    JumpInstruction(BasicBlock *block) : Instruction(JUMP), block(block) {}

    void print(std::ostream &out);

  private:
    BasicBlock *block;
};

#endif // __INSTRUCTION_H