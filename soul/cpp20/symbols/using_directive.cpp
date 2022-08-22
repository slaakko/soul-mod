// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.using_directive;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.scope;
import soul.cpp20.symbols.scope.resolver;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.namespaces;
import util.unicode;

namespace soul::cpp20::symbols {

class UsingDirectiveProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    UsingDirectiveProcessor(Context* context_);
    void Visit(soul::cpp20::ast::UsingDirectiveNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    Scope* scope;
};

UsingDirectiveProcessor::UsingDirectiveProcessor(Context* context_) : context(context_), scope(context->GetSymbolTable()->CurrentScope())
{
}

void UsingDirectiveProcessor::Visit(soul::cpp20::ast::UsingDirectiveNode& node)
{
    node.Id()->Accept(*this);
}

void UsingDirectiveProcessor::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void UsingDirectiveProcessor::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    Symbol* symbol = scope->Lookup(node.Str(), SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, node.GetSourcePos(), context, LookupFlags::none);
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

void AddUsingDirective(soul::cpp20::ast::Node* node, Context* context)
{
    UsingDirectiveProcessor processor(context);
    node->Accept(processor);
}

} // namespace soul::cpp20::symbols
