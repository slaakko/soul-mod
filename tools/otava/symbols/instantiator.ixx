// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.instantiator;

import std.core;
import otava.ast.visitor;

export namespace otava::symbols {

class Context;

class Instantiator : public otava::ast::DefaultVisitor
{
public:
    Instantiator(Context* context_);
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
private:
    Context* context;
    bool innerClass;
    int index;
};

} // namespace otava::symbols
