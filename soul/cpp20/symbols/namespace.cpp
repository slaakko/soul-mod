// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.namespaces;

import soul.cpp20.ast;
import soul.cpp20.symbols.context;
import soul.cpp20.symbols.alias.group.symbol;
import soul.cpp20.symbols.concept_group.symbol;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.enum_group.symbol;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.variable.group.symbol;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

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
        soul::cpp20::ast::SetExceptionThrown();
        throw std::runtime_error("soul.cpp20.symbols.NamespaceSymbol::Import: namespace symbol expected");
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

class NamespaceCreator : public soul::cpp20::ast::DefaultVisitor
{
public:
    NamespaceCreator(Context* context_);
    void Visit(soul::cpp20::ast::ColonColonNode& node) override;
    void Visit(soul::cpp20::ast::IdentifierNode& node) override;
private:
    Context* context;
    Scope* currentScope;
    bool first;
};

NamespaceCreator::NamespaceCreator(Context* context_) : context(context_), currentScope(context->GetSymbolTable()->CurrentScope()), first(true)
{
}

void NamespaceCreator::Visit(soul::cpp20::ast::ColonColonNode& node)
{
    if (first)
    {
        currentScope = context->GetSymbolTable()->GlobalNs()->GetScope();
        first = false;
    }
}

void NamespaceCreator::Visit(soul::cpp20::ast::IdentifierNode& node)
{
    first = false;
    context->GetSymbolTable()->BeginNamespace(&node, context);
    currentScope = context->GetSymbolTable()->CurrentScope();
}

void BeginNamespace(soul::cpp20::ast::Node* node, Context* context)
{
    NamespaceCreator creator(context);
    node->Accept(creator);
}

void EndNamespace(soul::cpp20::ast::Node* node, int level, Context* context)
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

} // namespace soul::cpp20::symbols
