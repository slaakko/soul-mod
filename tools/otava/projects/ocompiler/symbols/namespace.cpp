// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.namespaces;

import otava.ast;
import otava.symbols.alias.group.symbol;
import otava.symbols.concept_group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.error;
import otava.symbols.function.group.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.visitor;
import otava.symbols.scope;
import otava.symbols.symbol.table;

namespace otava::symbols {

NamespaceSymbol::NamespaceSymbol(const std::u32string& name_) : ContainerSymbol(SymbolKind::namespaceSymbol, name_)
{
    GetScope()->SetKind(ScopeKind::namespaceScope);
}

bool NamespaceSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: return true;
    }
    return false;
}

std::expected<bool, int> NamespaceSymbol::Import(NamespaceSymbol* that, Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    std::expected<bool, int> rv = symbolTable->BeginNamespace(that->Name(), nullptr, context);
    if (!rv) return rv;
    Scope* currentScope = symbolTable->CurrentScope();
    Symbol* symbol = currentScope->GetSymbol();
    NamespaceSymbol* ns = nullptr;
    if (symbol->IsNamespaceSymbol())
    {
        ns = static_cast<NamespaceSymbol*>(symbol);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("otava.symbols.NamespaceSymbol::Import: namespace symbol expected"));
    }
    for (auto& symbol : that->Symbols())
    {
        if (symbol->IsNamespaceSymbol())
        {
            NamespaceSymbol* thatNs = static_cast<NamespaceSymbol*>(symbol.get());
            rv = ns->Import(thatNs, context);
            if (!rv) return rv;
        }
        else
        {
            Symbol* installSymbol = symbol.get();
            switch (symbol->Kind())
            {
                case SymbolKind::functionDefinitionSymbol:
                {
                    FunctionDefinitionSymbolSet* functionDefinitionSymbolSet = context->GetFunctionDefinitionSymbolSet();
                    FunctionDefinitionSymbol* functionDefinition = static_cast<FunctionDefinitionSymbol*>(installSymbol);
                    functionDefinitionSymbolSet->AddFunctionDefinitionSymbol(functionDefinition);
                    break;
                }
                case SymbolKind::conceptGroupSymbol:
                {
                    std::expected<ConceptGroupSymbol*, int> rv = currentScope->GetOrInsertConceptGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    installSymbol = *rv;
                    break;
                }
                case SymbolKind::classGroupSymbol:
                {
                    std::expected<ClassGroupSymbol*, int> rv = currentScope->GetOrInsertClassGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    installSymbol = *rv;
                    break;
                }
                case SymbolKind::aliasGroupSymbol:
                {
                    std::expected<AliasGroupSymbol*, int> rv = currentScope->GetOrInsertAliasGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    installSymbol = *rv;
                    break;
                }
                case SymbolKind::functionGroupSymbol:
                {
                    std::expected<FunctionGroupSymbol*, int> rv = currentScope->GetOrInsertFunctionGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    installSymbol = *rv;
                    break;
                }
                case SymbolKind::variableGroupSymbol:
                {
                    std::expected<VariableGroupSymbol*, int> rv = currentScope->GetOrInsertVariableGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    installSymbol = *rv;
                    break;
                }
                case SymbolKind::enumGroupSymbol:
                {
                    std::expected<EnumGroupSymbol*, int> rv = currentScope->GetOrInsertEnumGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    if (!rv) return std::unexpected<int>(rv.error());
                    installSymbol = *rv;
                    break;
                }
            }
            if (installSymbol->CanInstall())
            {
                currentScope->Install(installSymbol, symbol.get(), context);
            }
        }
    }
    currentScope->Import(that->GetScope(), context);
    rv = symbolTable->EndNamespace();
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

void NamespaceSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

bool NamespaceSymbol::ContainsSymbols() const
{
    for (const auto& symbol : Symbols())
    {
        if (!symbol->IsNamespaceSymbol()) return true;
    }
    return false;
}

class NamespaceCreator : public otava::ast::DefaultVisitor
{
public:
    NamespaceCreator(Context* context_);
    void Visit(otava::ast::ColonColonNode& node) override;
    void Visit(otava::ast::IdentifierNode& node) override;
private:
    Context* context;
    Scope* currentScope;
    bool first;
};

NamespaceCreator::NamespaceCreator(Context* context_) : context(context_), currentScope(context->GetSymbolTable()->CurrentScope()), first(true)
{
}

void NamespaceCreator::Visit(otava::ast::ColonColonNode& node)
{
    if (first)
    {
        currentScope = context->GetSymbolTable()->GlobalNs()->GetScope();
        first = false;
    }
}

void NamespaceCreator::Visit(otava::ast::IdentifierNode& node)
{
    first = false;
    std::expected<bool, int> rv = context->GetSymbolTable()->BeginNamespace(&node, context);
    if (!rv)
    {
        SetError(rv.error());
        return;
    }
    currentScope = context->GetSymbolTable()->CurrentScope();
}

std::expected<bool, int> BeginNamespace(otava::ast::Node* node, Context* context)
{
    NamespaceCreator creator(context);
    node->Accept(creator);
    if (!creator) return std::unexpected<int>(creator.Error());
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EndNamespace(otava::ast::Node* node, int level, Context* context)
{
    if (!context->GetSymbolTable()->CurrentScope()->GetSymbol()->IsNamespaceSymbol())
    {
        return Error("otava.symbols.namespace: EndNamespace(): namespace scope expected", node->GetSourcePos(), context);
    }
    return context->GetSymbolTable()->EndNamespace(level);
}

bool NamespaceLess::operator()(NamespaceSymbol* left, NamespaceSymbol* right) const
{
    std::expected<std::u32string, int> l = left->FullName();
    std::expected<std::u32string, int> r = right->FullName();
    if (!l || !r) return false;
    std::u32string ls = *l;
    std::u32string rs = *r;
    return ls < rs;
}

} // namespace otava::symbols
