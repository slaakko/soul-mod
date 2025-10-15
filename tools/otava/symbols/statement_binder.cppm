// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.statement.binder;

import otava.symbols.bound.tree;
import std;
import otava.ast.node;
import otava.ast.visitor;

export namespace otava::symbols {

class Context;
class FunctionDefinitionSymbol;
class ClassTypeSymbol;
class TypeSymbol;
class VariableSymbol;

class StatementBinder : public otava::ast::DefaultVisitor
{
public:
    StatementBinder(Context* context_, FunctionDefinitionSymbol* functionDefinitionSymbol_);
    inline BoundStatementNode* GetBoundStatement() const { return boundStatement; }
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
    void Visit(otava::ast::ConstructorNode& node) override;
    void Visit(otava::ast::ConstructorInitializerNode& node) override;
    void Visit(otava::ast::MemberInitializerListNode& node) override;
    void Visit(otava::ast::MemberInitializerNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;
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
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
    void Visit(otava::ast::AliasDeclarationNode& node) override;
    void Visit(otava::ast::BoundStatementNode& node) override;
    inline FunctionDefinitionSymbol* GetFunctionDefinitionSymbol() const { return functionDefinitionSymbol; }
private:
    void SetStatement(BoundStatementNode* statement);
    bool HasThisInitializer() const;
    void CompleteMemberInitializers(const soul::ast::SourcePos& sourcePos);
    void AddDefaultMemberInitializer(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos);
    int GetBaseInitializerOrTerminatorIndex(TypeSymbol* baseClass) const;
    void CompleteBaseInitializers(const soul::ast::SourcePos& sourcePos);
    void AddDefaultBaseInitializer(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos);
    void GenerateDefaultCtorInitializer(const soul::ast::SourcePos& sourcePos);
    void GenerateDestructorTerminator(const soul::ast::SourcePos& sourcePos);
    void GenerateBaseTerminators(const soul::ast::SourcePos& sourcePos);
    void AddBaseTerminator(TypeSymbol* baseClass, int index, const soul::ast::SourcePos& sourcePos);
    void GenerateMemberTerminators(const soul::ast::SourcePos& sourcePos);
    void AddMemberTerminator(VariableSymbol* memberVar, const soul::ast::SourcePos& sourcePos);
    void GenerateSetVPtrStatements(const soul::ast::SourcePos& sourcePos);
    void BindStaticLocalVariable(VariableSymbol* variable, otava::ast::Node* initializer, otava::ast::SimpleDeclarationNode* declarationNode);
    Context* context;
    ClassTypeSymbol* currentClass; 
    BoundCtorInitializerNode* ctorInitializer;
    BoundDtorTerminatorNode* dtorTerminator;
    BoundStatementNode* boundStatement;
    FunctionDefinitionSymbol* functionDefinitionSymbol;
    ClassTypeSymbol* classTypeSymbol;
    VariableSymbol* memberVariableSymbol;
    std::vector<std::unique_ptr<BoundExpressionNode>> initializerArgs;
    bool resolveClass;
    bool resolveMemberVariable;
    bool resolveInitializerArguments;
    bool setVPtrStatementsGenerated;
    std::vector<std::pair<int, std::unique_ptr<BoundFunctionCallNode>>> baseInitializers;
    std::vector<std::pair<int, std::unique_ptr<BoundFunctionCallNode>>> memberInitializers;
    std::vector<std::unique_ptr<BoundStatementNode>> setVPtrStatements;
    std::vector<std::pair<int, std::unique_ptr<BoundFunctionCallNode>>> memberTerminators;
    std::vector<std::pair<int, std::unique_ptr<BoundFunctionCallNode>>> baseTerminators;
    bool postfix;
    std::unique_ptr<BoundExpressionStatementNode> constructFunctionStaticStatement;
    std::unique_ptr<BoundExpressionStatementNode> atExitStatement;
    VariableSymbol* globalStaticVariableSymbol;
};

FunctionDefinitionSymbol* BindFunction(otava::ast::Node* functionDefinitionNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);
BoundStatementNode* BindStatement(otava::ast::Node* statementNode, FunctionDefinitionSymbol* functionDefinitionSymbol, Context* context);


} // namespace otava::symbols
