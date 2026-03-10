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

class Cleanup;

class CleanupBlock
{
public:
    CleanupBlock(Cleanup* cleanup_);
    inline bool IsEmpty() const noexcept { return destructorCalls.empty(); }
    void Add(BoundExpressionNode* destructorCall, Context* context);
    void Make(otava::ast::CompoundStatementNode* compoundStatement);
    soul::ast::SourcePos GetSourcePos() const;
private:
    Cleanup* cleanup;
    std::vector<std::unique_ptr<BoundExpressionNode>> destructorCalls;
};

class Cleanup
{
public:
    Cleanup();
    bool IsEmpty() const noexcept;
    void PushCleanupBlock();
    void PopCleanupBlock();
    CleanupBlock* CurrentCleanupBlock() const noexcept { return cleanupBlocks.back().get(); }
    inline bool Changed() const noexcept { return changed; }
    inline void SetChanged() noexcept { changed = true; }
    inline void ResetChanged() noexcept { changed = false; }
    void Make(otava::ast::CompoundStatementNode* compoundStatement);
    soul::ast::SourcePos GetSourcePos() const;
private:
    std::vector<std::unique_ptr<CleanupBlock>> cleanupBlocks;
    bool changed;
};

void MakeInvokesAndCleanups(BoundFunctionNode* boundFunction, Context* context);
BoundStatementNode* ConvertReturnStatement(otava::ast::ReturnStatementNode* returnStatement, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);

} // namespace otava::symbols
