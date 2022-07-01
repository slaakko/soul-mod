// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.classes;

import soul.cpp20.ast;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

ClassTypeSymbol::ClassTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::classTypeSymbol, name_)
{
    GetScope()->SetKind(ScopeKind::classScope);
}

bool ClassTypeSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: 
        case ScopeKind::templateDeclarationScope: 
        case ScopeKind::classScope: 
        case ScopeKind::blockScope: 
        {
            return true;
        }
    }
    return false;
}

void ClassTypeSymbol::AddBaseClass(Symbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context)
{
    baseClasses.push_back(baseClass);
    GetScope()->AddBaseScope(baseClass->GetScope(), sourcePos, context);
}

class ClassNameResolver : public soul::cpp20::ast::DefaultVisitor
{
public:
    std::u32string GetName() const { return name; }
    void Visit(soul::cpp20::ast::ClassSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::ClassHeadNode& node) override;
private:
    std::u32string name;
};

void ClassNameResolver::Visit(soul::cpp20::ast::ClassSpecifierNode& node)
{
    node.ClassHead()->Accept(*this);
}

void ClassNameResolver::Visit(soul::cpp20::ast::ClassHeadNode& node)
{
    name = node.ClassHeadName()->Str();
}

std::u32string GetClassName(soul::cpp20::ast::Node* node)
{
    ClassNameResolver resolver;
    node->Accept(resolver);
    return resolver.GetName();
}

void BeginClass(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context)
{
    std::u32string name = GetClassName(node);
    context->GetSymbolTable()->BeginClass(name, node, context);
}

void EndClass(soul::cpp20::symbols::Context* context)
{
    context->GetSymbolTable()->EndClass();
}

} // namespace soul::cpp20::symbols
