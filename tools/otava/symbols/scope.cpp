// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.scope;

import otava.symbols.symbol;
import otava.symbols.context;
import otava.symbols.exception;
import otava.symbols.namespaces;
import otava.symbols.concept_group.symbol;
import otava.symbols.alias.group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.symbol.table;
import otava.symbols.templates;
import otava.ast.error;
import util.unicode;

namespace otava::symbols {

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
        case ScopeKind::instantiationScope: return "instantiation scope";
    }
    return "<unknown scope>";
}

Scope::Scope() : kind(ScopeKind::none)
{
}

Scope::~Scope()
{
}

void Scope::Import(Scope* that)
{
    for (const auto& p : that->symbolMap)
    {
        Symbol* s = p.second;
        Install(s);
    }
}

void Scope::Install(Symbol* symbol)
{
    Install(symbol, symbol);
}

void Scope::Install(Symbol* symbol, Symbol* from)
{
    SymbolGroupKind symbolGroupKind = symbol->GetSymbolGroupKind();
    if (from != symbol)
    {
        if (from->IsFunctionGroupSymbol() && symbol->IsFunctionGroupSymbol())
        {
            FunctionGroupSymbol* fromFunctionGroup = static_cast<FunctionGroupSymbol*>(from);
            FunctionGroupSymbol* functionGroup = static_cast<FunctionGroupSymbol*>(symbol);
            functionGroup->Merge(fromFunctionGroup);
        }
        else if (from->IsClassGroupSymbol() && symbol->IsClassGroupSymbol())
        {
            ClassGroupSymbol* fromClassGroup = static_cast<ClassGroupSymbol*>(from);
            ClassGroupSymbol* classGroup = static_cast<ClassGroupSymbol*>(symbol);
            classGroup->Merge(fromClassGroup);
        }
        else if (from->IsAliasGroupSymbol() && symbol->IsAliasGroupSymbol())
        {
            AliasGroupSymbol* fromAliasGroup = static_cast<AliasGroupSymbol*>(from);
            AliasGroupSymbol* aliasGroup = static_cast<AliasGroupSymbol*>(symbol);
            aliasGroup->Merge(fromAliasGroup);
        }
        else if (from->IsVariableGroupSymbol() && symbol->IsVariableGroupSymbol())
        {
            VariableGroupSymbol* fromVariableGroup = static_cast<VariableGroupSymbol*>(from);
            VariableGroupSymbol* variableGroup = static_cast<VariableGroupSymbol*>(symbol);
            variableGroup->Merge(fromVariableGroup);
        }
        else if (from->IsEnumGroupSymbol() && symbol->IsEnumGroupSymbol())
        {
            EnumGroupSymbol* fromEnumGroup = static_cast<EnumGroupSymbol*>(from);
            EnumGroupSymbol* enumGroup = static_cast<EnumGroupSymbol*>(symbol);
            enumGroup->Merge(fromEnumGroup);
        }
    }
    symbolMap[std::make_pair(symbol->Name(), symbolGroupKind)] = symbol;
}

void Scope::Uninstall(Symbol* symbol)
{
    SymbolGroupKind symbolGroupKind = symbol->GetSymbolGroupKind();
    symbolMap.erase(std::make_pair(symbol->Name(), symbolGroupKind));
}

Symbol* Scope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, const soul::ast::SourcePos& sourcePos, Context* context, 
    LookupFlags flags) const
{
    std::vector<Symbol*> symbols;
    std::set<Scope*> visited;
    Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
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
        ThrowException(errorMessage, sourcePos, context);
    }
}

Scope* Scope::GroupScope()
{
    if (IsTemplateDeclarationScope())
    {
        return ParentScopes().front();
    }
    else
    {
        return this;
    }
}

Scope* Scope::SymbolScope()
{
    return this;
}

void Scope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags, 
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
    {
        std::vector<SymbolGroupKind> symbolGroupKindVec = SymbolGroupKindstoSymbolGroupKindVec(symbolGroupKinds);
        for (SymbolGroupKind symbolGroupKind : symbolGroupKindVec)
        {
            if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
            {
                if ((scopeLookup & ScopeLookup::thisAndBaseScopes) != ScopeLookup::none)
                {
                    auto it = symbolMap.find(std::make_pair(id, symbolGroupKind));
                    if (it != symbolMap.cend())
                    {
                        Symbol* symbol = it->second;
                        if (symbol->IsForwardDeclarationSymbol() && (flags & LookupFlags::noFwdDeclarationSymbol) != LookupFlags::none)
                        {
                            continue;
                        }
                        else if (std::find(symbols.begin(), symbols.end(), symbol) == symbols.end())
                        {
                            symbols.push_back(symbol);
                        }
                    }
                }
            }
        }
    }
}

void Scope::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot declare symbol '" + util::ToUtf8(symbol->Name()) + "' in " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

std::unique_ptr<Symbol> Scope::RemoveSymbol(Symbol* symbol)
{
    otava::ast::SetExceptionThrown();
    throw std::runtime_error("could not remove symbol");
}

void Scope::AddParentScope(Scope* parentScope_)
{
    otava::ast::SetExceptionThrown();
    throw std::runtime_error("could not add parent scope");
}

void Scope::PushParentScope(Scope* parentScope)
{
    otava::ast::SetExceptionThrown();
    throw std::runtime_error("could not push parent scope");
}

void Scope::PopParentScope()
{
    otava::ast::SetExceptionThrown();
    throw std::runtime_error("could not pop parent scope");
}

void Scope::AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add base class scope to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

void Scope::AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add using declaration '" + util::ToUtf8(usingDeclaration->FullName()) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

void Scope::AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add using directive '" + util::ToUtf8(ns->FullName()) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

ClassGroupSymbol* Scope::GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add class group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

FunctionGroupSymbol* Scope::GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add function group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

ConceptGroupSymbol* Scope::GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add concept group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

VariableGroupSymbol* Scope::GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add variable group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

AliasGroupSymbol* Scope::GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add alias group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

EnumGroupSymbol* Scope::GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("cannot add enum group '" + util::ToUtf8(name) + "' to " + ScopeKindStr(kind) + " '" + FullName() + "'", sourcePos, context);
}

ContainerScope::ContainerScope() : Scope(), parentScopes(), usingDeclarationScope(nullptr), containerSymbol(nullptr), parentScopePushed(false)
{
}

void ContainerScope::AddParentScope(Scope* parentScope)
{
    parentScopes.push_back(parentScope);
}

void ContainerScope::PushParentScope(Scope* parentScope)
{
    if (!parentScopePushed)
    {
        parentScopePushed = true;
        parentScopes.push_back(parentScope);
    }
}

void ContainerScope::PopParentScope()
{
    if (parentScopePushed)
    {
        parentScopePushed = false;
        parentScopes.pop_back();
    }
}

void ContainerScope::ClearParentScopes()
{
    parentScopes.clear();
}

void ContainerScope::Import(Scope* that)
{
    if (that->IsContainerScope())
    {
        ContainerScope* thatScope = static_cast<ContainerScope*>(that);
        if (thatScope->usingDeclarationScope)
        {
            if (!usingDeclarationScope)
            {
                usingDeclarationScope = new UsingDeclarationScope(this);
                scopes.push_back(std::unique_ptr<Scope>(usingDeclarationScope));
            }
            usingDeclarationScope->Import(thatScope->usingDeclarationScope);
        }
        for (UsingDirectiveScope* thatUsingDirectiveScope : thatScope->usingDirectiveScopes)
        {
            UsingDirectiveScope* usingDirectiveScope = new UsingDirectiveScope(thatUsingDirectiveScope->Ns());
            scopes.push_back(std::unique_ptr<Scope>(usingDirectiveScope));
            usingDirectiveScopes.push_back(usingDirectiveScope);
            usingDirectiveScope->Import(thatUsingDirectiveScope);
        }
    }
}

Scope* ContainerScope::GetClassScope() const
{
    if (Kind() == ScopeKind::classScope)
    {
        return const_cast<Scope*>(static_cast<const Scope*>(this));
    }
    for (Scope* parentScope : ParentScopes())
    {
        Scope* classScope = parentScope->GetClassScope();
        if (classScope)
        {
            return classScope;
        }
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

void ContainerScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags, 
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    std::vector<SymbolGroupKind> symbolGroupKindVec = SymbolGroupKindstoSymbolGroupKindVec(symbolGroupKinds);
    for (SymbolGroupKind symbolGroupKind : symbolGroupKindVec)
    {
        Scope::Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
        if ((scopeLookup & ScopeLookup::parentScope) != ScopeLookup::none)
        {
            for (const auto& parentScope : parentScopes)
            {
                if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
                {
                    parentScope->Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
                }
            }
        }
        if ((scopeLookup & ScopeLookup::baseScope) != ScopeLookup::none)
        {
            if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
            {
                for (Scope* baseScope : baseScopes)
                {
                    baseScope->Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
                }
            }
        }
        if ((scopeLookup & ScopeLookup::usingScope) != ScopeLookup::none)
        {
            if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
            {
                if (usingDeclarationScope)
                {
                    if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
                    {
                        usingDeclarationScope->Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
                    }
                }
                for (Scope* usingDirectiveScope : usingDirectiveScopes)
                {
                    if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
                    {
                        usingDirectiveScope->Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
                    }
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
        ThrowException("cannot add using directive to " + ScopeKindStr(Kind()), sourcePos, context);
    }
}

void ContainerScope::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!symbol->IsValidDeclarationScope(Kind()))
    {
        ThrowException("cannot declare symbol '" + util::ToUtf8(symbol->Name()) + "' in " + ScopeKindStr(Kind()) + " '" + FullName() + "'", sourcePos, context);
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

EnumGroupSymbol* ContainerScope::GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    Symbol* symbol = Scope::Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::enumGroupSymbol)
        {
            EnumGroupSymbol* enumGroupSymbol = static_cast<EnumGroupSymbol*>(symbol);
            return enumGroupSymbol;
        }
    }
    EnumGroupSymbol* enumGroupSymbol = new EnumGroupSymbol(name);
    AddSymbol(enumGroupSymbol, sourcePos, context);
    return enumGroupSymbol;
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

void UsingDeclarationScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, LookupFlags flags, 
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    Scope::Lookup(id, symbolGroupKind, ScopeLookup::thisScope, flags, symbols, visited, context);
}

UsingDirectiveScope::UsingDirectiveScope(NamespaceSymbol* ns_) : Scope(), ns(ns_)
{
    SetKind(ScopeKind::usingDirectiveScope);
}

void UsingDirectiveScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, LookupFlags flags, 
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    if (visited.find(ns->GetScope()) == visited.end())
    {
        visited.insert(ns->GetScope());
        ns->GetScope()->Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
    }
}

std::string UsingDirectiveScope::FullName() const
{
    return util::ToUtf8(ns->FullName());
}

InstantiationScope::InstantiationScope(Scope* parentScope_)
{
    SetKind(ScopeKind::instantiationScope);
    parentScopes.push_back(parentScope_);
}

std::string InstantiationScope::FullName() const
{
    Scope* first = *parentScopes.begin();
    return first->FullName();
}

Scope* InstantiationScope::GroupScope()
{
    Scope* first = *parentScopes.begin();
    return first->GroupScope();
}

Scope* InstantiationScope::SymbolScope()
{
    Scope* first = *parentScopes.begin();
    return first->SymbolScope();
}

void InstantiationScope::PushParentScope(Scope* parentScope_)
{
    parentScopes.insert(parentScopes.begin(), parentScope_);
}

void InstantiationScope::PopParentScope()
{
    parentScopes.erase(parentScopes.begin());
}

void InstantiationScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, LookupFlags flags,
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    std::vector<Symbol*> foundSymbols;
    Scope::Lookup(id, symbolGroupKind, ScopeLookup::thisScope, flags, foundSymbols, visited, context);
    for (const auto& symbol : foundSymbols)
    {
        if (symbol->IsBoundTemplateParameterSymbol())
        {
            BoundTemplateParameterSymbol* boundTemplateParameterSymbol = static_cast<BoundTemplateParameterSymbol*>(symbol);
            symbols.push_back(boundTemplateParameterSymbol->BoundSymbol());
        }
        else
        {
            symbols.push_back(symbol);
        }
    }
    if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
    {
        if ((scopeLookup & ScopeLookup::parentScope) != ScopeLookup::none)
        {
            for (Scope* parentScope : parentScopes)
            {
                if (symbols.empty())
                {
                    parentScope->Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
                }
            }
        }
    }
}

} // namespace otava::symbols
