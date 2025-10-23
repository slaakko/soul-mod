// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.operation.repository;

import std;
import soul.ast.source.pos;

export namespace otava::symbols {

const int inlineClassOperationsThreshold = 4;

class BoundExpressionNode;
class FunctionSymbol;
class FunctionDefinitionSymbol;
class ClassTypeSymbol;
class Context;

class Operation
{
public:
    Operation(const std::u32string& groupName_, int arity_);
    virtual ~Operation();
    inline const std::u32string& GroupName() const { return groupName; }
    inline int Arity() const { return arity; }
    virtual std::expected<FunctionSymbol*, int> Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context) = 0;
private:
    std::u32string groupName;
    int arity;
};

class OperationGroup
{
public:
    OperationGroup(const std::u32string& name_);
    inline const std::u32string& Name() const { return name; }
    void AddOperation(Operation* operation);
    std::expected<FunctionSymbol*, int> GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    std::u32string name;
    std::map<int, std::vector<Operation*>> arityOperationsMap;
    std::vector<Operation*> anyArityOperations;
};

class OperationRepository
{
public:
    OperationRepository();
    void AddOperation(Operation* operation);
    std::expected<FunctionSymbol*, int> GetOperation(const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
        const soul::ast::SourcePos& sourcePos, Context* context);
private:
    OperationGroup* GetOrInsertOperationGroup(const std::u32string& operationGroupName);
    std::map<std::u32string, OperationGroup*> groupMap;
    std::vector<std::unique_ptr<OperationGroup>> groups;
    std::vector<std::unique_ptr<Operation>> operations;
};

std::expected<FunctionDefinitionSymbol*,int> GenerateClassDefaultCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context);
std::expected<FunctionDefinitionSymbol*, int> GenerateClassCopyCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context);
std::expected<FunctionDefinitionSymbol*, int> GenerateClassMoveCtor(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context);
std::expected<FunctionDefinitionSymbol*, int> GenerateClassCopyAssignment(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context);
std::expected<FunctionDefinitionSymbol*, int> GenerateClassMoveAssignment(ClassTypeSymbol* classType, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
