// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.using_declaration;

import soul.cpp20.symbols.context;
import soul.cpp20.symbols.scope;
import soul.cpp20.symbols.scope.resolver;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.exception;
import util.unicode;

namespace soul::cpp20::symbols {

class UsingDeclarationProcessor : public soul::cpp20::ast::DefaultVisitor
{
public:
    UsingDeclarationProcessor(Context* context_);
    void Visit(soul::cpp20::ast::UsingDeclarationNode& node) override;
    void Visit(soul::cpp20::ast::QualifiedIdNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    Scope* scope;
};

UsingDeclarationProcessor::UsingDeclarationProcessor(Context* context_) : context(context_), scope(context->GetSymbolTable()->CurrentScope())
{
}

void UsingDeclarationProcessor::Visit(soul::cpp20::ast::UsingDeclarationNode& node)
{
    node.Declarators()->Accept(*this);
}

void UsingDeclarationProcessor::Visit(soul::cpp20::ast::QualifiedIdNode& node)
{
    scope = ResolveScope(node.Left(), context);
    node.Right()->Accept(*this);
}

void UsingDeclarationProcessor::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    std::vector<Symbol*> symbols;
    scope->Lookup(node.Str(), SymbolGroupKind::all, ScopeLookup::thisScope, symbols);
    if (symbols.empty())
    {
        throw Exception("symbol '" + util::ToUtf8(node.Str()) + "' not found", node.GetSourcePos(), context);
    }
    for (Symbol* symbol : symbols)
    {
        if (symbol->IsNamespaceSymbol())
        {
            throw Exception("symbol '" + util::ToUtf8(symbol->FullName()) + "' denotes a namespace", node.GetSourcePos(), context);
        }
        else
        {
            context->GetSymbolTable()->AddUsingDeclaration(&node, symbol, context);
        }
    }
}

void AddUsingDeclaration(soul::cpp20::ast::Node* node, Context* context)
{
    UsingDeclarationProcessor processor(context);
    node->Accept(processor);
}

} // namespace soul::cpp20::symbols
