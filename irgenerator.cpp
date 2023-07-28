#include "IRGenerator.h"

Module* IRGenerator::generate(std::string name, ProgramNode* root) {
    Module* module = new Module(name);

    for (FunctionNode* function : root->getFunctions()) {
        Function* zirFunction = new Function(function->getName());
        module->addFunction(zirFunction);

        currentBB = zirFunction->getEntryBlock();

        for (auto statement : function->getStatements()) {
            visitStatement(statement);
        }
    }

    return module;
}

void IRGenerator::visitStatement(StatementNode* statement) {
    if (auto functionCall = dynamic_cast<FunctionCallNode*>(statement)) {
        visitFunctionCall(functionCall);
    }
}

void IRGenerator::visitFunctionCall(FunctionCallNode* functionCall) {
    std::vector<Value*> args;
    for (auto arg : functionCall->getArgs()) {
        if (auto constant = dynamic_cast<ConstantNode*>(arg)) {
            args.push_back(new Constant(constant->getType(), constant->getValue()));
        }
    }

    currentBB->addInstruction(new FunctionCall(functionCall->getName(), args));
}