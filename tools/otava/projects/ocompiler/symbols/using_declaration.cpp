// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.using_declaration;

import otava.symbols.context;
import otava.symbols.scope;
import otava.symbols.scope.resolver;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.error;
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
    if (!Valid()) return;
    node.Declarators()->Accept(*this);
}

void UsingDeclarationProcessor::Visit(otava::ast::QualifiedIdNode& node)
{
    if (!Valid()) return;
    std::expected<Scope*, int> rv = ResolveScope(node.Left(), context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    scope = *rv;
    node.Right()->Accept(*this);
}

void UsingDeclarationProcessor::Visit(otava::ast::IdentifierNode& node)
{
    if (!Valid()) return;
    std::vector<Symbol*> symbols;
    std::set<Scope*> visited;
    scope->Lookup(node.Str(), SymbolGroupKind::all, ScopeLookup::thisScope, LookupFlags::none, symbols, visited, context);
    if (symbols.empty())
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
    for (Symbol* symbol : symbols)
    {
        if (symbol->IsNamespaceSymbol())
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
            std::unexpected<int> result = Error("symbol '" + *sfname + "' denotes a namespace", node.GetSourcePos(), context);
            SetError(result.error());
            return;
        }
        else
        {
            std::expected<bool, int> rv = context->GetSymbolTable()->AddUsingDeclaration(&node, symbol, context);
            if (!rv)
            {
                SetError(rv.error());
                return;
            }
        }
    }
}

std::expected<bool, int> AddUsingDeclaration(otava::ast::Node* node, Context* context)
{
    UsingDeclarationProcessor processor(context);
    node->Accept(processor);
    if (!processor) return std::unexpected<int>(processor.Error());
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
