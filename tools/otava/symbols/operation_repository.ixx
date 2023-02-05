// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.operation.repository;

import std.core;
import soul.ast.source.pos;

export namespace otava::symbols {

class BoundExpressionNode;
class FunctionSymbol;
class Context;

class Operation
{
public:
    Operation(const std::u32string& groupName_, int arity_);
    virtual ~Operation();
    const std::u32string& GroupName() const { return groupName; }
    int Arity() const { return arity; }
    virtual FunctionSymbol* Get(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) = 0;
private:
    std::u32string groupName; 
    int arity;
};

class OperationGroup
{
public:
    OperationGroup(const std::u32string& name_);
    const std::u32string& Name() const { return name; }
    void AddOperation(Operation* operation);
    FunctionSymbol* GetOperation(std::vector<std::unique_ptr<BoundExpressionNode>>& args, const soul::ast::SourcePos& sourcePos,
        otava::symbols::Context* context);
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
    FunctionSymbol* GetOperation(const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
        const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
private:
    OperationGroup* GetOrInsertOperationGroup(const std::u32string& operationGroupName);
    std::map<std::u32string, OperationGroup*> groupMap;
    std::vector<std::unique_ptr<OperationGroup>> groups;
    std::vector<std::unique_ptr<Operation>> operations;
};

} // namespace otava::symbols
