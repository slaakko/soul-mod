// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.exception_handling;

import std;
import otava.ast;
import otava.symbols.bound.tree;

export namespace otava::symbols {

class CleanUp
{
public:
    CleanUp();
    inline bool IsEmpty() const { return destructionStatements .empty(); }
    inline int Count() const { return destructionStatements.size(); }
    inline bool Changed() const { return changed; }
    inline void ResetChanged() { changed = false; }
    inline FunctionDefinitionSymbol* CleanupFnSymbol() const { return cleanupFnSymbol; }
    inline void SetCleanupFnSymbol(FunctionDefinitionSymbol* cleanupFnSymbol_) { cleanupFnSymbol = cleanupFnSymbol_; }
    void Add(BoundExpressionStatementNode* destructionStatement, Context* context);
    BoundStatementNode* CloneStatement(int index) const;
private:
    std::vector<std::unique_ptr<BoundStatementNode>> destructionStatements;
    bool changed;
    FunctionDefinitionSymbol* cleanupFnSymbol;
};

BoundStatementNode* GenerateInvoke(BoundStatementNode* stmt, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);
BoundStatementNode* ConvertReturnStatement(otava::ast::ReturnStatementNode* returnStatement, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);

} // namespace otava::symbols
