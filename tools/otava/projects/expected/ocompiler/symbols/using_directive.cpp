// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.using_directive;

import otava.symbols.context;
import otava.symbols.scope;
import otava.symbols.scope.resolver;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.error;
import otava.symbols.namespaces;
import util.unicode;

namespace otava::symbols {

class UsingDirectiveProcessor : public otava::ast::DefaultVisitor
{
public:
    UsingDirectiveProcessor(Context* context_);
    void Visit(otava::ast::UsingDirectiveNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
private:
    Context* context;
    Scope* scope;
};

UsingDirectiveProcessor::UsingDirectiveProcessor(Context* context_) : context(context_), scope(context->GetSymbolTable()->CurrentScope())
{
}

void UsingDirectiveProcessor::Visit(otava::ast::UsingDirectiveNode& node)
{
    if (!Valid()) return;
    node.Id()->Accept(*this);
}

void UsingDirectiveProcessor::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    std::expected<Scope*, int> s = ResolveScope(node.Left(), context);
    if (!s)
    {
        SetError(s.error());
        return;
    }
    scope = *s;
    node.Right()->Accept(*this);
}

void UsingDirectiveProcessor::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    std::expected<Symbol*, int> s = scope->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::none);
    if (!s)
    {
        SetError(s.error());
        return;
    }
    Symbol* symbol = *s;
    if (symbol)
    {
        if (symbol->IsNamespaceSymbol())
        {
            NamespaceSymbol* ns = static_cast<NamespaceSymbol*>(symbol);
            std::expected<bool, int> rv = context->GetSymbolTable()->AddUsingDirective(ns, &node, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
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
            std::unexpected<int> result = Error("symbol '" + *sfname + "' does not denote a namespace", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
    }
    else
    {
        std::expected<std::string, int> n = util::ToUtf8(node.Str());
        if (!n)
        {
            SetError(n.error());
            return;
        }
        std::unexpected<int> result = Error("symbol '" + *n + "' not found", node.GetSourcePos(), context);
        SetError(result.error());
        return;
    }
}

std::expected<bool, int> AddUsingDirective(otava::ast::Node* node, Context* context)
{
    UsingDirectiveProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
