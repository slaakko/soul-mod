// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.using_declaration;

import otava.symbols.context;
import otava.symbols.scope;
import otava.symbols.scope.resolver;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.exception;
import util.unicode;

namespace otava::symbols {

class UsingDeclarationProcessor : public otava::ast::DefaultVisitor
{
public:
    UsingDeclarationProcessor(Context* context_);
    void Visit(otava::ast::UsingDeclarationNode& node) override;
    void Visit(otava::ast::QualifiedIdNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
private:
    Context* context;
    Scope* scope;
};

UsingDeclarationProcessor::UsingDeclarationProcessor(Context* context_) : context(context_), scope(context->GetSymbolTable()->CurrentScope())
{
}

void UsingDeclarationProcessor::Visit(otava::ast::UsingDeclarationNode& node)
{
    node.Declarators()->Accept(*this);
}

void UsingDeclarationProcessor::Visit(otava::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void UsingDeclarationProcessor::Visit(otava::ast::IdentifierNode& node)
{
    std::vector<Symbol*> symbols;
    std::set<Scope*> visited;
    scope->Lookup(node.Str(), SymbolGroupKind::all, ScopeLookup::thisScope, LookupFlags::none, symbols, visited, context);
    if (symbols.empty())
    {
        ThrowException("symbol '" + util::ToUtf8(node.Str()) + "' not found", node.GetSourcePos(), context);
    }
    for (Symbol* symbol : symbols)
    {
        if (symbol->IsNamespaceSymbol())
        {
            ThrowException("symbol '" + util::ToUtf8(symbol->FullName()) + "' denotes a namespace", node.GetSourcePos(), context);
        }
        else
        {
            context->GetSymbolTable()->AddUsingDeclaration(&node, symbol, context);
        }
    }
}

void AddUsingDeclaration(otava::ast::Node* node, Context* context)
{
    UsingDeclarationProcessor processor(context);
    node->Accept(processor);
}

} // namespace otava::symbols
