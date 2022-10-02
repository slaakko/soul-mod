// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.namespaces;

import otava.ast;
import otava.symbols.context;
import otava.symbols.alias.group.symbol;
import otava.symbols.concept_group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.exception;
import otava.symbols.function.group.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.visitor;
import otava.symbols.symbol.table;

namespace otava::symbols {

NamespaceSymbol::NamespaceSymbol(const std::u32string& name_) : ContainerSymbol(SymbolKind::namespaceSymbol, name_)
{
    GetScope()->SetKind(ScopeKind::namespaceScope);
}

SymbolTable* NamespaceSymbol::GetSymbolTable() 
{
    if (symbolTable) return symbolTable;
    if (Parent()) return Parent()->GetSymbolTable();
    return nullptr;
}

bool NamespaceSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: return true;
    }
    return false;
}

void NamespaceSymbol::Import(NamespaceSymbol* that, Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    symbolTable->BeginNamespace(that->Name(), nullptr, context);
    Scope* currentScope = symbolTable->CurrentScope();
    Symbol* symbol = currentScope->GetSymbol();
    NamespaceSymbol* ns = nullptr;
    if (symbol->IsNamespaceSymbol())
    {
        ns = static_cast<NamespaceSymbol*>(symbol);
    }
    else
    {
        otava::ast::SetExceptionThrown();
        throw std::runtime_error("otava.symbols.NamespaceSymbol::Import: namespace symbol expected");
    }
    for (auto& symbol : that->Symbols())
    {
        if (symbol->IsNamespaceSymbol())
        {
            NamespaceSymbol* thatNs = static_cast<NamespaceSymbol*>(symbol.get());
            ns->Import(thatNs, context);
        }
        else
        {
            Symbol* installSymbol = symbol.get();
            switch (symbol->Kind())
            {
                case SymbolKind::conceptGroupSymbol:
                {
                    installSymbol = currentScope->GetOrInsertConceptGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    break;
                }
                case SymbolKind::classGroupSymbol:
                {
                    installSymbol = currentScope->GetOrInsertClassGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    break;
                }
                case SymbolKind::aliasGroupSymbol:
                {
                    installSymbol = currentScope->GetOrInsertAliasGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    break;
                }
                case SymbolKind::functionGroupSymbol:
                {
                    installSymbol = currentScope->GetOrInsertFunctionGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    break;
                }
                case SymbolKind::variableGroupSymbol:
                {
                    installSymbol = currentScope->GetOrInsertVariableGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    break;
                }
                case SymbolKind::enumGroupSymbol:
                {
                    installSymbol = currentScope->GetOrInsertEnumGroup(symbol->Name(), soul::ast::SourcePos(), context);
                    break;
                }
            }
            if (installSymbol->CanInstall())
            {
                currentScope->Install(installSymbol, symbol.get());
            }
        }
    }
    currentScope->Import(that->GetScope());
    symbolTable->EndNamespace();
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
    context->GetSymbolTable()->BeginNamespace(&node, context);
    currentScope = context->GetSymbolTable()->CurrentScope();
}

void BeginNamespace(otava::ast::Node* node, Context* context)
{
    NamespaceCreator creator(context);
    node->Accept(creator);
}

void EndNamespace(otava::ast::Node* node, int level, Context* context)
{
    if (!context->GetSymbolTable()->CurrentScope()->GetSymbol()->IsNamespaceSymbol())
    {
        ThrowException("cpp20.symbols.namespace: EndNamespace(): namespace scope expected", node->GetSourcePos(), context);
    }
    context->GetSymbolTable()->EndNamespace(level);
}

bool NamespaceLess::operator()(NamespaceSymbol* left, NamespaceSymbol* right) const
{
    return left->FullName() < right->FullName();
}

} // namespace otava::symbols
