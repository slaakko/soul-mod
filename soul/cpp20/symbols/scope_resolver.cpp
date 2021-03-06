// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.scope.resolver;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.exception;
import util.unicode;

namespace soul::cpp20::symbols {

class ScopeResolver : public soul::cpp20::ast::DefaultVisitor
{
public:
    ScopeResolver(Context* context_);
    Scope* GetScope() const { return currentScope; }
    void Visit(soul::cpp20::ast::NestedNameSpecifierNode& node) override;
    void Visit(soul::cpp20::ast::ColonColonNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    bool first;
    Scope* currentScope;
};

ScopeResolver::ScopeResolver(Context* context_) : context(context_), first(false), currentScope(nullptr)
{
}

void ScopeResolver::Visit(soul::cpp20::ast::NestedNameSpecifierNode& node)
{
    first = true;
    currentScope = context->GetSymbolTable()->CurrentScope();
    VisitSequence(node);
}

void ScopeResolver::Visit(soul::cpp20::ast::ColonColonNode& node)
{
    if (first)
    {
        currentScope = context->GetSymbolTable()->GlobalNs()->GetScope();
        first = false;
    }
}

void ScopeResolver::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    first = false;
    Symbol* symbol = currentScope->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::none);
    if (symbol)
    {
        Scope* scope = symbol->GetScope();
        if (scope)
        {
            currentScope = scope;
        }
        else
        {
            throw Exception("symbol '" + util::ToUtf8(symbol->FullName()) + "' does not have a scope", node.GetSourcePos(), context);
        }
    }
    else
    {
        throw Exception("symbol '" + util::ToUtf8(node.Str()) + "' not found from " + ScopeKindStr(currentScope->Kind()) + " '" + currentScope->FullName() + "'",
            node.GetSourcePos(), context);
    }
}

Scope* ResolveScope(soul::cpp20::ast::Node* nnsNode, Context* context)
{
    ScopeResolver resolver(context);
    nnsNode->Accept(resolver);
    return resolver.GetScope();
}

void BeginScope(soul::cpp20::ast::Node* nnsNode, Context* context)
{
    Scope* scope = ResolveScope(nnsNode, context);
    context->GetSymbolTable()->BeginScope(scope);
}

void EndScope(Context* context)
{
    context->GetSymbolTable()->EndScope();
}

} // namespace soul::cpp20::symbols
