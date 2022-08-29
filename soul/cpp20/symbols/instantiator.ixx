// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.instantiator;

import std.core;
import soul.cpp20.ast.visitor;

export namespace soul::cpp20::symbols {

class Context;

class Instantiator : public soul::cpp20::ast::DefaultVisitor
{
public:
    Instantiator(Context* context_);
    void Visit(soul::cpp20::ast::ClassSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::BeginAccessGroupNode& node) override;
    void Visit(soul::cpp20::ast::AliasDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::MemberDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::SimpleDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::UsingDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::UsingDirectiveNode& node) override;
    void Visit(soul::cpp20::ast::FunctionDefinitionNode& node) override;
    void Visit(soul::cpp20::ast::NoDeclSpecFunctionDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::TemplateDeclarationNode& node) override;
private:
    Context* context;
    bool innerClass;
    int index;
};

} // namespace soul::cpp20::symbols
