// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.exception_handling;

import std;
import soul.ast.source.pos;
import otava.ast;
import otava.symbols.bound.tree;

export namespace otava::symbols {

class Invoke
{
public:
    Invoke();
    inline bool IsEmpty() const { return statements.empty(); }
    void Clear();
    void Add(BoundStatementNode* stmt);
    const std::vector<std::unique_ptr<BoundStatementNode>>& Statements() const { return statements; }
    void Make(otava::ast::CompoundStatementNode* compoundStatement, Context* context);
    soul::ast::SourcePos GetSourcePos() const;
private:
    std::vector<std::unique_ptr<BoundStatementNode>> statements;
};

class Cleanup;

class CleanupBlock
{
public:
    CleanupBlock(Cleanup* cleanup_);
    inline bool IsEmpty() const { return destructorCalls.empty(); }
    inline bool ContainsOne() const { return destructorCalls.size() == 1; }
    void Add(BoundFunctionCallNode* destructorCall, Context* context);
    void Make(otava::ast::CompoundStatementNode* compoundStatement, bool skipLast);
    soul::ast::SourcePos GetSourcePos() const;
private:
    Cleanup* cleanup;
    std::vector<std::unique_ptr<BoundFunctionCallNode>> destructorCalls;
};

class Cleanup
{
public:
    Cleanup();
    bool IsEmpty() const;
    bool ContainsOne() const;
    void PushCleanupBlock();
    void PopCleanupBlock();
    CleanupBlock* CurrentCleanupBlock() const { return cleanupBlocks.back().get(); }
    inline bool Changed() const { return changed; }
    inline void SetChanged() { changed = true; }
    inline void ResetChanged() { changed = false; }
    void Make(otava::ast::CompoundStatementNode* compoundStatement, bool skipLast);
    soul::ast::SourcePos GetSourcePos() const;
private:
    std::vector<std::unique_ptr<CleanupBlock>> cleanupBlocks;
    bool changed;
};

BoundStatementNode* ConvertReturnStatement(otava::ast::ReturnStatementNode* returnStatement, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);
std::unique_ptr<BoundCompoundStatementNode> MakeInvokesAndCleanups(FunctionDefinitionSymbol* functionDefinitionSymbol, BoundCompoundStatementNode* functionNody, 
    Context* context);

} // namespace otava::symbols
