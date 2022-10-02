// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.scope.resolver;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.namespaces;
import otava.symbols.declaration;
import otava.symbols.exception;
import otava.symbols.type.resolver;
import otava.symbols.type.symbol;
import otava.symbols.alias.type.symbol;
import util.unicode;

namespace otava::symbols {

class ScopeResolver : public otava::ast::DefaultVisitor
{
public:
    ScopeResolver(Context* context_);
    Scope* GetScope() const { return currentScope; }
    void Visit(otava::ast::NestedNameSpecifierNode& node) override;
    void Visit(otava::ast::ColonColonNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
    void Visit(otava::ast::TemplateIdNode& node) override;
private:
    Context* context;
    bool first;
    Scope* currentScope;
};

ScopeResolver::ScopeResolver(Context* context_) : context(context_), first(false), currentScope(nullptr)
{
}

void ScopeResolver::Visit(otava::ast::NestedNameSpecifierNode& node)
{
    first = true;
    currentScope = context->GetSymbolTable()->CurrentScope();
    VisitSequence(node);
}

void ScopeResolver::Visit(otava::ast::ColonColonNode& node)
{
    if (first)
    {
        currentScope = context->GetSymbolTable()->GlobalNs()->GetScope();
        first = false;
    }
}

void ScopeResolver::Visit(otava::ast::IdentifierNode& node)
{
    first = false;
    Symbol* symbol = currentScope->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::none);
    if (!symbol)
    {
        symbol = context->GetSymbolTable()->LookupInScopeStack(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context, LookupFlags::none);
    }
    if (symbol)
    {
        while (symbol && symbol->IsAliasTypeSymbol())
        {
            AliasTypeSymbol* aliasTypeSymbol = static_cast<AliasTypeSymbol*>(symbol);
            symbol = aliasTypeSymbol->ReferredType();
        }
        if (symbol)
        {
            Scope* scope = symbol->GetScope();
            if (scope)
            {
                currentScope = scope;
            }
            else
            {
                ThrowException("symbol '" + util::ToUtf8(symbol->FullName()) + "' does not have a scope", node.GetSourcePos(), context);
            }
        }
        else
        {
            ThrowException("symbol '" + util::ToUtf8(node.Str()) + "' not found from " + ScopeKindStr(currentScope->Kind()) + " '" + currentScope->FullName() + "'", node.GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("symbol '" + util::ToUtf8(node.Str()) + "' not found from " + ScopeKindStr(currentScope->Kind()) + " '" + currentScope->FullName() + "'", node.GetSourcePos(), context);
    }
}

void ScopeResolver::Visit(otava::ast::TemplateIdNode& node)
{
    first = false;
    context->GetSymbolTable()->BeginScope(currentScope);
    TypeSymbol* type = ResolveType(&node, DeclarationFlags::none, context);
    currentScope = type->GetScope();
    context->GetSymbolTable()->EndScope();
}

Scope* ResolveScope(otava::ast::Node* nnsNode, Context* context)
{
    ScopeResolver resolver(context);
    nnsNode->Accept(resolver);
    return resolver.GetScope();
}

void BeginScope(otava::ast::Node* nnsNode, Context* context)
{
    Scope* scope = ResolveScope(nnsNode, context);
    context->GetSymbolTable()->BeginScope(scope);
}

void EndScope(Context* context)
{
    context->GetSymbolTable()->EndScope();
}

void AddParentScope(otava::ast::Node* node, Context* context)
{
    if (context->GetFlag(ContextFlags::addClassScope))
    {
        if (node->IsQualifiedIdNode())
        {
            if (context->GetSymbolTable()->CurrentScope()->IsNamespaceScope())
            {
                otava::ast::QualifiedIdNode* qualifiedIdNode = static_cast<otava::ast::QualifiedIdNode*>(node);
                Scope* scope = ResolveScope(qualifiedIdNode->Left(), context);
                if (scope->IsClassScope())
                {
                    context->GetSymbolTable()->CurrentScope()->PushParentScope(scope);
                }
            }
        }
    }
}

} // namespace otava::symbols
