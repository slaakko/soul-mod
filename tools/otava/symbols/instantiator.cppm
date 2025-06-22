// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.instantiator;

import std.core;
import otava.ast.visitor;

export namespace otava::symbols {

class ClassTypeSymbol;
class FunctionSymbol;
class Context;
class InstantiationScope;

class Instantiator : public otava::ast::DefaultVisitor
{
public:
    Instantiator(Context* context_, InstantiationScope* instantiationScope_);
    void SetFunctionNode(otava::ast::Node* functionNode_);
    FunctionSymbol* GetSpecialization() const { return specialization; }
    std::vector<ClassTypeSymbol*> GetBaseClasses() { return std::move(baseClasses); }
    void Visit(otava::ast::ClassSpecifierNode& node) override;
    void Visit(otava::ast::BeginAccessGroupNode& node) override;
    void Visit(otava::ast::AliasDeclarationNode& node) override;
    void Visit(otava::ast::MemberDeclarationNode& node) override;
    void Visit(otava::ast::SimpleDeclarationNode& node) override;
    void Visit(otava::ast::UsingDeclarationNode& node) override;
    void Visit(otava::ast::UsingDirectiveNode& node) override;
    void Visit(otava::ast::FunctionDefinitionNode& node) override;
    void Visit(otava::ast::NoDeclSpecFunctionDeclarationNode& node) override;
    void Visit(otava::ast::TemplateDeclarationNode& node) override;
    void Visit(otava::ast::CompoundStatementNode& node) override;
    void Visit(otava::ast::IfStatementNode& node) override;
    void Visit(otava::ast::SwitchStatementNode& node) override;
    void Visit(otava::ast::WhileStatementNode& node) override;
    void Visit(otava::ast::DoStatementNode& node) override;
    void Visit(otava::ast::ForStatementNode& node) override;
    void Visit(otava::ast::ExpressionStatementNode& node) override;
    void Visit(otava::ast::ReturnStatementNode& node) override;
    void Visit(otava::ast::ExceptionDeclarationNode& node) override;
private:
    Context* context;
    bool innerClass;
    int index;
    InstantiationScope* instantiationScope;
    std::vector<ClassTypeSymbol*> baseClasses;
    otava::ast::Node* functionNode;
    FunctionSymbol* specialization;
};

} // namespace otava::symbols
