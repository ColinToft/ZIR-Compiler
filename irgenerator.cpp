#include "irgenerator.h"

Module *IRGenerator::generate(std::string name, ProgramNode *root) {
    Module *module = new Module(name);

    for (FunctionNode *function : root->getFunctions()) {
        Function *zirFunction = new Function(
            convertType(function->getReturnType()), function->getName());
        currentBB = new BasicBlock("entry");
        zirFunction->addBasicBlock(currentBB);

        module->addFunction(zirFunction);

        for (auto statement : function->getStatements()) {
            visitStatement(statement);
        }
    }

    return module;
}

void IRGenerator::visitStatement(StatementNode *statement) {
    if (auto functionCall = dynamic_cast<FunctionCallNode *>(statement)) {
        visitFunctionCall(functionCall);
    }
}

void IRGenerator::visitFunctionCall(FunctionCallNode *functionCall) {
    std::vector<Value *> args;
    for (auto arg : functionCall->getArgs()) {
        if (auto constant = dynamic_cast<ConstantNode *>(arg)) {
            args.push_back(new Constant(convertType(constant->getType()),
                                        constant->getValue()));
        }
    }

    currentBB->addInstruction(new FunctionCall(functionCall->getName(), args));
}

ZIRType IRGenerator::convertType(ZenType *type) {
    switch (type->getKind()) {
    case ZenType::Int:
        return ZIRType(ZIRType::Int8);
    case ZenType::Void:
        return ZIRType(ZIRType::Void);
    default:
        throw std::runtime_error("Unknown type");
    }
}