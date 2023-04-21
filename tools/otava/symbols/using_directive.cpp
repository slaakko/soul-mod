// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.using_directive;

import otava.symbols.context;
import otava.symbols.scope;
import otava.symbols.scope.resolver;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.exception;
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
    node.Id()->Accept(*this);
}

void UsingDirectiveProcessor::Visit(otava::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void UsingDirectiveProcessor::Visit(otava::ast::IdentifierNode& node)
{
    Symbol* symbol = scope->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::allScopes, node.GetSourcePos(), context, LookupFlags::none);
    if (symbol)
    {
        if (symbol->IsNamespaceSymbol())
        {
            NamespaceSymbol* ns = static_cast<NamespaceSymbol*>(symbol);
            context->GetSymbolTable()->AddUsingDirective(ns, &node, context);
        }
        else
        {
            ThrowException("symbol '" + util::ToUtf8(symbol->FullName()) + "' does not denote a namespace", node.GetSourcePos(), context);
        }
    }
    else
    {
        ThrowException("symbol '" + util::ToUtf8(node.Str()) + "' not found", node.GetSourcePos(), context);
    }
}

void AddUsingDirective(otava::ast::Node* node, Context* context)
{
    UsingDirectiveProcessor processor(context);
    node->Accept(processor);
}

} // namespace otava::symbols
