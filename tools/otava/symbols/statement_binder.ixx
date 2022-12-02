// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.statement.binder;

import std.core;
import otava.ast.node;
import otava.ast.visitor;

export namespace otava::symbols {

class BoundStatementNode;
class Context;
class FunctionDefinitionSymbol;
class BoundCtorInitializerNode;
class ClassTypeSymbol;
class VariableSymbol;
class BoundExpressionNode;
class BoundFunctionCallNode;
class BoundStatement;

class StatementBinder : public otava::ast::DefaultVisitor
{
public:
    StatementBinder(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_);
    BoundStatementNode* GetBoundStatement() const { return boundStatement; }
    void CompileStatement(otava::ast::Node* statementNode, bool setPostfix);
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
    void Visit(otava::ast::ConstructorNode& node) override;
    void Visit(otava::ast::ConstructorInitializerNode& node) override;
    void Visit(otava::ast::MemberInitializerListNode& node) override;
    void Visit(otava::ast::MemberInitializerNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::ExpressionListNode& node) override;
    void Visit(otava::ast::FunctionBodyNode& node) override;
    void Visit(otava::ast::CompoundStatementNode& node) override;
    void Visit(otava::ast::IfStatementNode& node) override;
    void Visit(otava::ast::SwitchStatementNode& node) override;
    void Visit(otava::ast::CaseStatementNode& node) override;
    void Visit(otava::ast::DefaultStatementNode& node) override;
    void Visit(otava::ast::WhileStatementNode& node) override;
    void Visit(otava::ast::DoStatementNode& node) override;
    void Visit(otava::ast::RangeForStatementNode& node) override;
    void Visit(otava::ast::ForStatementNode& node) override;
    void Visit(otava::ast::BreakStatementNode& node) override;
    void Visit(otava::ast::ContinueStatementNode& node) override;
    void Visit(otava::ast::ReturnStatementNode& node) override;
    void Visit(otava::ast::ExpressionStatementNode& node) override;
    void Visit(otava::ast::DeclarationStatementNode& node) override;
private:
    void SetStatement(BoundStatementNode* statement);
    Context* context;
    BoundCtorInitializerNode* ctorInitializer;
    BoundStatementNode* boundStatement;
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    ClassTypeSymbol* classTypeSymbol;
    VariableSymbol* memberVariableSymbol;
    std::vector<std::unique_ptr<BoundExpressionNode>> initializerArgs;
    bool resolveClass;
    bool resolveMemberVariable;
    bool resolveInitializerArguments;
    std::vector<std::pair<int, std::unique_ptr<BoundFunctionCallNode>>> memberInitializers;
    bool postfix;
};

void BindFunction(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);
BoundStatementNode* BindStatement(otava::ast::Node* statementNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);


} // namespace otava::symbols
