// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.code;

import std.core;
import otava.intermediate.data;
import otava.intermediate.metadata;
import otava.intermediate.basic.block;
import util.code.formatter;
import util.component;

export namespace otava::intermediate {

class Instruction;
class FunctionType;
class Visitor;

class Code : public util::Component
{
public:
    Code();
    void Finalize();
    void Write(util::CodeFormatter& formatter);
    Context* GetContext() const { return context; }
    void SetContext(Context* context_) { context = context_; }
    Function* CurrentFunction() const { return currentFunction; }
    void SetCurrentFunction(Function* function);
    Function* GetFunction(const std::string& functionId) const;
    Function* GetOrInsertFunction(const std::string& functionId, FunctionType* functionType);
    Function* AddFunctionDefinition(const SourcePos& sourcePos, FunctionType* functionType, const std::string& functionId, bool once, MetadataRef* metadataRef, Context* context);
    Function* AddFunctionDeclaration(const SourcePos& sourcePos, FunctionType* functionType, const std::string& functionId);
    Function* FirstFunction();
    Function* LastFunction();
    void VisitFunctions(Visitor& visitor);
    void AddFunction(Function* fn);
    std::unique_ptr<Function> RemoveFunction(Function* fn);
private:
    Context* context;
    Function* currentFunction;
    util::Container functions;
    std::map<std::string, Function*> functionMap;
};

} // otava::intermediate
