// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.scope;

import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.exception;
import soul.cpp20.symbols.namespaces;
import soul.cpp20.symbols.concept_group.symbol;
import soul.cpp20.symbols.alias.group.symbol;
import soul.cpp20.symbols.class_group.symbol;
import soul.cpp20.symbols.function.group.symbol;
import soul.cpp20.symbols.variable.group.symbol;
import util.unicode;

namespace soul::cpp20::symbols {

std::string ScopeKindStr(ScopeKind kind)
{
    switch (kind)
    {
        case ScopeKind::templateDeclarationScope: return "template declaration scope";
        case ScopeKind::namespaceScope: return "namespace scope";
        case ScopeKind::classScope: return "class scope";
        case ScopeKind::enumerationScope: return "enumeration scope";
        case ScopeKind::functionScope: return "function scope";
        case ScopeKind::blockScope: return "block scope";
        case ScopeKind::usingDeclarationScope: return "using declaration scope";
        case ScopeKind::usingDirectiveScope: return "using directive scope";
    }
    return "<unknown scope>";
}

Scope::Scope() : kind(ScopeKind::none)
{
}

Scope::~Scope()
{
}

void Scope::Install(Symbol* symbol)
{
    SymbolGroupKind symbolGroupKind = symbol->GetSymbolGroupKind();
    auto it = symbolMap.find(std::make_pair(symbol->InstallationName(), symbolGroupKind));
    if (it != symbolMap.cend())
    {
        Symbol* existingSymbol = it->second;
        if (existingSymbol != symbol)
        {
            throw std::runtime_error("cannot install symbol '" + util::ToUtf8(symbol->FullName()) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "': name conflicts with existing symbol '" +
                util::ToUtf8(existingSymbol->FullName()) + "'");
        }
        else
        {
            return;
        }
    }
    symbolMap[std::make_pair(symbol->InstallationName(), symbolGroupKind)] = symbol;
}

void Scope::Uninstall(Symbol* symbol)
{
    SymbolGroupKind symbolGroupKind = symbol->GetSymbolGroupKind();
    symbolMap.erase(std::make_pair(symbol->InstallationName(), symbolGroupKind));
}

Symbol* Scope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, const soul::ast::SourcePos& sourcePos, Context* context, 
    LookupFlags flags) const
{
    std::vector<Symbol*> symbols;
    Lookup(id, symbolGroupKind, scopeLookup, symbols);
    if (symbols.empty())
    {
        return nullptr;
    }
    else if (symbols.size() == 1)
    {
        if ((flags & LookupFlags::dontResolveSingle) == LookupFlags::none)
        {
            return symbols.front()->GetSingleSymbol();
        }
        else
        {
            return symbols.front();
        }
    }
    else
    {
        std::string errorMessage = "ambiguous reference to symbol '" + util::ToUtf8(id) + "': could be:\n";
        bool first = true;
        for (Symbol* symbol : symbols)
        {
            if (first)
            {
                first = false;
            }
            else
            {
                errorMessage.append(" or\n");
            }
            errorMessage.append(util::ToUtf8(symbol->FullName()));
        }
        throw Exception(errorMessage, sourcePos, context);
    }
}

void Scope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const
{
    std::vector<SymbolGroupKind> symbolGroupKindVec = SymbolGroupKindstoSymbolGroupKindVec(symbolGroupKinds);
    for (SymbolGroupKind symbolGroupKind : symbolGroupKindVec)
    {
        if ((scopeLookup & ScopeLookup::thisAndBaseScopes) != ScopeLookup::none)
        {
            auto it = symbolMap.find(std::make_pair(id, symbolGroupKind));
            if (it != symbolMap.cend())
            {
                Symbol* symbol = it->second;
                if (std::find(symbols.begin(), symbols.end(), symbol) == symbols.end())
                {
                    symbols.push_back(symbol);
                }
            }
        }
    }
}

void Scope::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot declare symbol '" + util::ToUtf8(symbol->Name()) + "' in " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

std::unique_ptr<Symbol> Scope::RemoveSymbol(Symbol* symbol)
{
    throw std::runtime_error("could not remove symbol");
}

void Scope::SetParentScope(Scope* parentScope_)
{
    throw std::runtime_error("could not set parent scope");
}

void Scope::AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add base class scope to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

void Scope::AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add using declaration '" + util::ToUtf8(usingDeclaration->FullName()) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

void Scope::AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add using directive '" + util::ToUtf8(ns->FullName()) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

ClassGroupSymbol* Scope::GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add class group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

FunctionGroupSymbol* Scope::GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add function group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

ConceptGroupSymbol* Scope::GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add concept group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

VariableGroupSymbol* Scope::GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add variable group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

AliasGroupSymbol* Scope::GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    throw Exception("cannot add alias group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

ContainerScope::ContainerScope() : Scope(), parentScope(nullptr), usingDeclarationScope(nullptr), containerSymbol(nullptr)
{
}

Scope* ContainerScope::GetClassScope() const
{
    if (Kind() == ScopeKind::classScope)
    {
        return const_cast<Scope*>(static_cast<const Scope*>(this));
    }
    Scope* parentScope = ParentScope();
    if (parentScope)
    {
        return parentScope->GetClassScope();
    }
    return nullptr;
}

void ContainerScope::AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (baseScope->IsContainerScope())
    {
        ContainerScope* containerScope = static_cast<ContainerScope*>(baseScope);
        ContainerSymbol* baseClassSymbol = containerScope->GetContainerSymbol();
        Install(baseClassSymbol);
    }
    baseScopes.push_back(baseScope);
}

Symbol* ContainerScope::GetSymbol()
{
    return containerSymbol;
}

std::string ContainerScope::FullName() const
{
    if (Kind() == ScopeKind::blockScope)
    {
        return std::string();
    }
    return util::ToUtf8(containerSymbol->FullName());
}

void ContainerScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const
{
    std::vector<SymbolGroupKind> symbolGroupKindVec = SymbolGroupKindstoSymbolGroupKindVec(symbolGroupKinds);
    for (SymbolGroupKind symbolGroupKind : symbolGroupKindVec)
    {
        Scope::Lookup(id, symbolGroupKind, scopeLookup, symbols);
        if ((scopeLookup & ScopeLookup::parentScope) != ScopeLookup::none)
        {
            if (symbols.empty())
            {
                if (parentScope)
                {
                    parentScope->Lookup(id, symbolGroupKind, scopeLookup, symbols);
                }
            }
        }
        if ((scopeLookup & ScopeLookup::baseScope) != ScopeLookup::none)
        {
            if (symbols.empty())
            {
                for (Scope* baseScope : baseScopes)
                {
                    baseScope->Lookup(id, symbolGroupKind, scopeLookup, symbols);
                }
            }
        }
        if ((scopeLookup & ScopeLookup::usingScope) != ScopeLookup::none)
        {
            if (symbols.empty())
            {
                if (usingDeclarationScope)
                {
                    usingDeclarationScope->Lookup(id, symbolGroupKind, scopeLookup, symbols);
                }
                for (Scope* usingDirectiveScope : usingDirectiveScopes)
                {
                    usingDirectiveScope->Lookup(id, symbolGroupKind, scopeLookup, symbols);
                }
            }
        }
    }
}

void ContainerScope::AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!usingDeclarationScope)
    {
        usingDeclarationScope = new UsingDeclarationScope(this);
        scopes.push_back(std::unique_ptr<Scope>(usingDeclarationScope));
    }
    usingDeclarationScope->Install(usingDeclaration);
}

void ContainerScope::AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (Kind() == ScopeKind::namespaceScope || Kind() == ScopeKind::blockScope)
    {
        for (UsingDirectiveScope* scope : usingDirectiveScopes)
        {
            if (scope->Ns() == ns) return;
        }
        UsingDirectiveScope* usingDirectiveScope = new UsingDirectiveScope(ns);
        scopes.push_back(std::unique_ptr<Scope>(usingDirectiveScope));
        usingDirectiveScopes.push_back(usingDirectiveScope);
    }
    else
    {
        throw Exception("cannot add using directive to " + ScopeKindStr(Kind()), sourcePos, context);
    }
}

void ContainerScope::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!symbol->IsValidDeclarationScope(Kind()))
    {
        throw Exception("cannot declare symbol '" + util::ToUtf8(symbol->Name()) + "' in " + ScopeKindStr(Kind()) + " '" + FullName() + "'", sourcePos, context);
    }
    containerSymbol->AddSymbol(symbol, sourcePos, context);
}

std::unique_ptr<Symbol> ContainerScope::RemoveSymbol(Symbol* symbol)
{
    return containerSymbol->RemoveSymbol(symbol);
}

ClassGroupSymbol* ContainerScope::GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = Scope::Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::classGroupSymbol)
        {
            ClassGroupSymbol* classGroupSymbol = static_cast<ClassGroupSymbol*>(symbol);
            return classGroupSymbol;
        }
    }
    ClassGroupSymbol* classGroupSymbol = new ClassGroupSymbol(name);
    AddSymbol(classGroupSymbol, sourcePos, context);
    return classGroupSymbol;
}

FunctionGroupSymbol* ContainerScope::GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = Scope::Lookup(name, SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::functionGroupSymbol)
        {
            FunctionGroupSymbol* functionGroupSymbol = static_cast<FunctionGroupSymbol*>(symbol);
            return functionGroupSymbol;
        }
    }
    FunctionGroupSymbol* functionGroupSymbol = new FunctionGroupSymbol(name);
    AddSymbol(functionGroupSymbol, sourcePos, context);
    return functionGroupSymbol;
}

ConceptGroupSymbol* ContainerScope::GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = Scope::Lookup(name, SymbolGroupKind::conceptSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::conceptGroupSymbol)
        {
            ConceptGroupSymbol* conceptGroupSymbol = static_cast<ConceptGroupSymbol*>(symbol);
            return conceptGroupSymbol;
        }
    }
    ConceptGroupSymbol* conceptGroupSymbol = new ConceptGroupSymbol(name);
    AddSymbol(conceptGroupSymbol, sourcePos, context);
    return conceptGroupSymbol;
}

VariableGroupSymbol* ContainerScope::GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = Scope::Lookup(name, SymbolGroupKind::variableSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::variableGroupSymbol)
        {
            VariableGroupSymbol* variableGroupSymbol = static_cast<VariableGroupSymbol*>(symbol);
            return variableGroupSymbol;
        }
    }
    VariableGroupSymbol* variableGroupSymbol = new VariableGroupSymbol(name);
    AddSymbol(variableGroupSymbol, sourcePos, context);
    return variableGroupSymbol;
}

AliasGroupSymbol* ContainerScope::GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = Scope::Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::aliasGroupSymbol)
        {
            AliasGroupSymbol* aliasGroupSymbol = static_cast<AliasGroupSymbol*>(symbol);
            return aliasGroupSymbol;
        }
    }
    AliasGroupSymbol* aliasGroupSymbol = new AliasGroupSymbol(name);
    AddSymbol(aliasGroupSymbol, sourcePos, context);
    return aliasGroupSymbol;
}

UsingDeclarationScope::UsingDeclarationScope(ContainerScope* parentScope_) : Scope(), parentScope(parentScope_)
{
    SetKind(ScopeKind::usingDeclarationScope);
}

std::string UsingDeclarationScope::FullName() const
{
    return parentScope->FullName();
}

void UsingDeclarationScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const
{
    Scope::Lookup(id, symbolGroupKind, ScopeLookup::thisScope, symbols);
}

UsingDirectiveScope::UsingDirectiveScope(NamespaceSymbol* ns_) : Scope(), ns(ns_)
{
    SetKind(ScopeKind::usingDirectiveScope);
}

void UsingDirectiveScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, std::vector<Symbol*>& symbols) const
{
    ns->GetScope()->Lookup(id, symbolGroupKind, scopeLookup, symbols);
}

std::string UsingDirectiveScope::FullName() const
{
    return util::ToUtf8(ns->FullName());
}

} // namespace soul::cpp20::symbols
