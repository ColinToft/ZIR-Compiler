#include "ir/irgenerator.h"

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
    } else if (auto returnStatement = dynamic_cast<ReturnNode *>(statement)) {
        visitReturn(returnStatement);
    } else {
        throw std::runtime_error("Unknown statement reached in IR generator");
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

    currentBB->addInstruction(
        new CallInstruction(functionCall->getName(), args));
}

void IRGenerator::visitReturn(ReturnNode *returnNode) {
    if (auto constant =
            dynamic_cast<ConstantNode *>(returnNode->getExpression())) {
        currentBB->addInstruction(new ReturnInstruction(new Constant(
            convertType(constant->getType()), constant->getValue())));
    }
}

ZIRType IRGenerator::convertType(ZenType *type) {
    switch (type->getKind()) {
    case ZenType::Int16:
        return ZIRType(ZIRType::Int16);
    case ZenType::Void:
        return ZIRType(ZIRType::Void);
    default:
        throw std::runtime_error("Unknown type");
    }
}