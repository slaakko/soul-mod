
// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.scope.resolver;

import otava.symbols.context;
import otava.symbols.symbol.table;
import otava.symbols.namespaces;
import otava.symbols.declaration;
import otava.symbols.error;
import otava.symbols.type.resolver;
import otava.symbols.type.symbol;
import otava.symbols.alias.type.symbol;
import util.unicode;

namespace otava::symbols {

class ScopeResolver : public otava::ast::DefaultVisitor
{
public:
    ScopeResolver(Context* context_);
    inline Scope* GetScope() const { return currentScope; }
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
    std::expected<Symbol*, int> rv = currentScope->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::allScopes, node.GetSourcePos(), 
        context, LookupFlags::none);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    Symbol* symbol = *rv;
    if (!symbol)
    {
        rv = context->GetSymbolTable()->LookupInScopeStack(node.Str(), SymbolGroupKind::typeSymbolGroup, node.GetSourcePos(), context, LookupFlags::none);
        if (!rv)
        {
            SetError(rv.error());
            return;
        }
        symbol = *rv;
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
                std::expected<std::u32string, int> fname = symbol->FullName();
                if (!fname)
                {
                    SetError(fname.error());
                    return;
                }
                std::expected<std::string, int> sfname = util::ToUtf8(*fname);
                if (!sfname)
                {
                    SetError(sfname.error());
                    return;
                }
                std::unexpected<int> result = Error("symbol '" + *sfname + "' does not have a scope", node.GetSourcePos(), context);
                SetError(result.error());
                return;
            }
        }
        else
        {
            std::expected<std::string, int> scopefname = currentScope->FullName();
            if (!scopefname)
            {
                SetError(scopefname.error());
                return;
            }
            std::expected<std::string, int> name = util::ToUtf8(node.Str());
            if (!name)
            {
                SetError(name.error());
                return;
            }
            std::unexpected<int> result = Error("symbol '" + *name + "' not found from " + ScopeKindStr(currentScope->Kind()) + 
                " '" + *scopefname + "'", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    else
    {
        std::expected<std::string, int> scopefname = currentScope->FullName();
        if (!scopefname)
        {
            SetError(scopefname.error());
            return;
        }
        std::expected<std::string, int> name = util::ToUtf8(node.Str());
        if (!name)
        {
            SetError(name.error());
            return;
        }
        std::unexpected<int> result = Error("symbol '" + *name + "' not found from " + ScopeKindStr(currentScope->Kind()) + 
            " '" + *scopefname + "'", node.GetSourcePos(), context);
    }
}

void ScopeResolver::Visit(otava::ast::TemplateIdNode& node)
{
    first = false;
    context->GetSymbolTable()->BeginScope(currentScope);
    std::expected<TypeSymbol*, int> rv = ResolveType(&node, DeclarationFlags::none, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    TypeSymbol* type = *rv;
    currentScope = type->GetScope();
    context->GetSymbolTable()->EndScope();
}

std::expected<Scope*, int> ResolveScope(otava::ast::Node* nnsNode, Context* context)
{
    ScopeResolver resolver(context);
    nnsNode->Accept(resolver);
    if (!resolver) return std::unexpected<int>(resolver.Error());
    return std::expected<Scope*, int>(resolver.GetScope());
}

std::expected<bool, int> BeginScope(otava::ast::Node* nnsNode, Context* context)
{
    std::expected<Scope*, int> scope = ResolveScope(nnsNode, context);
    if (!scope) return std::unexpected<int>(scope.error());
    context->GetSymbolTable()->BeginScope(*scope);
    return std::expected<bool, int>(true);
}

void EndScope(Context* context)
{
    context->GetSymbolTable()->EndScope();
}

std::expected<bool, int> AddParentScope(otava::ast::Node* node, Context* context)
{
    if (context->GetFlag(ContextFlags::addClassScope))
    {
        if (node->IsQualifiedIdNode())
        {
            if (context->GetSymbolTable()->CurrentScope()->IsNamespaceScope())
            {
                otava::ast::QualifiedIdNode* qualifiedIdNode = static_cast<otava::ast::QualifiedIdNode*>(node);
                std::expected<Scope*, int> scopeRv = ResolveScope(qualifiedIdNode->Left(), context);
                if (!scopeRv) return std::unexpected<int>(scopeRv.error());
                Scope* scope = *scopeRv;
                if (scope->IsClassScope())
                {
                    std::expected<bool, int> rv = context->GetSymbolTable()->CurrentScope()->PushParentScope(scope);
                    if (!rv) return rv;
                }
            }
        }
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
