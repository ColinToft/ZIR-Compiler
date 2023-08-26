#ifndef __IR_GENERATOR_H
#define __IR_GENERATOR_H

#include <iostream>
#include <string>
#include <vector>

#include "AST.h"
#include "ir/Module.h"

/**
 * Converts the AST to the ZIR intermediate representation.
 */
class IRGenerator {
  public:
    IRGenerator() {}

    Module *generate(std::string name, ProgramNode *root);

  private:
    void visitStatement(StatementNode *statement);
    void visitFunctionCall(FunctionCallNode *functionCall);
    void visitReturn(ReturnNode *returnNode);

    ZIRType convertType(ZenType *type);

    BasicBlock *currentBB;
};

#endif // __IR_GENERATOR_H