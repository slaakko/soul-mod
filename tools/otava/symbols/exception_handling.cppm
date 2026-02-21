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
    inline bool IsEmpty() const noexcept { return statements.empty(); }
    void Clear();
    void Add(BoundStatementNode* stmt);
    inline const std::vector<std::unique_ptr<BoundStatementNode>>& Statements() const noexcept { return statements; }
    inline bool HasStatementsWithDestructor() const noexcept { return !statementsWithDestructor.empty(); }
    std::vector<std::unique_ptr<BoundConstructionStatementNode>> StatementsWithDestructor() { return std::move(statementsWithDestructor); }
    void Make(otava::ast::CompoundStatementNode* compoundStatement, Context* context);
    soul::ast::SourcePos GetSourcePos() const;
private:
    std::vector<std::unique_ptr<BoundStatementNode>> statements;
    std::vector<std::unique_ptr<BoundConstructionStatementNode>> statementsWithDestructor;
};

class Cleanup;

class CleanupBlock
{
public:
    CleanupBlock(Cleanup* cleanup_);
    inline bool IsEmpty() const noexcept { return destructorCalls.empty(); }
    inline bool ContainsOne() const noexcept { return destructorCalls.size() == 1; }
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
    bool IsEmpty() const noexcept;
    bool ContainsOne() const noexcept;
    void PushCleanupBlock();
    void PopCleanupBlock();
    CleanupBlock* CurrentCleanupBlock() const noexcept { return cleanupBlocks.back().get(); }
    inline bool Changed() const noexcept { return changed; }
    inline void SetChanged() noexcept { changed = true; }
    inline void ResetChanged() noexcept { changed = false; }
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
