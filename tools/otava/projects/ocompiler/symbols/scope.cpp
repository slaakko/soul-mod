// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.scope;

import otava.symbols.symbol;
import otava.symbols.context;
import otava.symbols.error;
import otava.symbols.namespaces;
import otava.symbols.concept_group.symbol;
import otava.symbols.alias.group.symbol;
import otava.symbols.class_group.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.variable.group.symbol;
import otava.symbols.enum_group.symbol;
import otava.symbols.symbol.table;
import otava.symbols.templates;
import otava.symbols.class_templates;
import otava.symbols.inline_functions;
import util.unicode;

namespace otava::symbols {

std::string SymbolGroupStr(SymbolGroupKind group)
{
    std::string groupStr;
    if ((group & SymbolGroupKind::functionSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("functionSymbolGroup");
    }
    if ((group & SymbolGroupKind::typeSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("typeSymbolGroup");
    }
    if ((group & SymbolGroupKind::variableSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("variableSymbolGroup");
    }
    if ((group & SymbolGroupKind::enumConstantSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("enumConstantSymbolGroup");
    }
    if ((group & SymbolGroupKind::conceptSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("conceptSymbolGroup");
    }
    if ((group & SymbolGroupKind::blockSymbolGroup) != SymbolGroupKind::none)
    {
        if (!groupStr.empty())
        {
            groupStr.append(" | ");
        }
        groupStr.append("blockSymbolGroup");
    }
    return groupStr;
}

std::vector<SymbolGroupKind> SymbolGroupKindstoSymbolGroupKindVec(SymbolGroupKind symbolGroupKinds)
{
    std::vector<SymbolGroupKind> symbolGroupKindVec;
    if ((symbolGroupKinds & SymbolGroupKind::functionSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::functionSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::typeSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::typeSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::variableSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::variableSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::enumConstantSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::enumConstantSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::conceptSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::conceptSymbolGroup);
    }
    if ((symbolGroupKinds & SymbolGroupKind::blockSymbolGroup) != SymbolGroupKind::none)
    {
        symbolGroupKindVec.push_back(SymbolGroupKind::blockSymbolGroup);
    }
    return symbolGroupKindVec;
}

std::string ScopeKindStr(ScopeKind kind)
{
    switch (kind)
    {
        case ScopeKind::templateDeclarationScope: return "template declaration scope";
        case ScopeKind::namespaceScope: return "namespace scope";
        case ScopeKind::classScope: return "class scope";
        case ScopeKind::enumerationScope: return "enumeration scope";
        case ScopeKind::functionScope: return "function scope";
        case ScopeKind::arrayScope: return "array scope";
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

void Scope::Import(Scope* that, Context* context)
{
    for (const auto& p : that->symbolMap)
    {
        Symbol* s = p.second;
        Install(s, context);
    }
}

void Scope::Install(Symbol* symbol, Context* context)
{
    Install(symbol, symbol, context);
}

void Scope::Install(Symbol* symbol, Symbol* from, Context* context)
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
            aliasGroup->Merge(fromAliasGroup, context);
        }
        else if (from->IsVariableGroupSymbol() && symbol->IsVariableGroupSymbol())
        {
            VariableGroupSymbol* fromVariableGroup = static_cast<VariableGroupSymbol*>(from);
            VariableGroupSymbol* variableGroup = static_cast<VariableGroupSymbol*>(symbol);
            variableGroup->Merge(fromVariableGroup);
        }
        else if (from->IsConceptGroupSymbol() && symbol->IsConceptGroupSymbol())
        {
            ConceptGroupSymbol* fromConceptGroup = static_cast<ConceptGroupSymbol*>(from);
            ConceptGroupSymbol* conceptGroup = static_cast<ConceptGroupSymbol*>(symbol);
            conceptGroup->Merge(fromConceptGroup);
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

std::expected<Symbol*, int> Scope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKind, ScopeLookup scopeLookup, const soul::ast::SourcePos& sourcePos, 
    Context* context, LookupFlags flags) const
{
    std::vector<Symbol*> symbols;
    std::set<Scope*> visited;
    Lookup(id, symbolGroupKind, scopeLookup, flags, symbols, visited, context);
    if (symbols.empty())
    {
        return std::expected<Symbol*, int>(nullptr);
    }
    else if (symbols.size() == 1)
    {
        if ((flags & LookupFlags::dontResolveSingle) == LookupFlags::none)
        {
            return std::expected<Symbol*, int>(symbols.front()->GetSingleSymbol());
        }
        else
        {
            return std::expected<Symbol*, int>(symbols.front());
        }
    }
    else
    {
        std::expected<std::string, int> sid = util::ToUtf8(id);
        if (!sid) return std::unexpected<int>(sid.error());
        std::string errorMessage = "ambiguous reference to symbol '" + *sid + "': could be:\n";
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
            std::expected<std::u32string, int> fname = symbol->FullName();
            if (!fname) return std::unexpected<int>(fname.error());
            std::expected<std::string, int> sfname = util::ToUtf8(*fname);
            if (!sfname) return std::unexpected<int>(sfname.error());
            errorMessage.append(*sfname);
        }
        return Error(errorMessage, sourcePos, context);
    }
}

Scope* Scope::GroupScope()
{
    if (IsTemplateDeclarationScope())
    {
        std::vector<Scope*> pscopes = ParentScopes();
        return pscopes.front();
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

std::expected<bool, int> Scope::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> sname = util::ToUtf8(symbol->Name());
    if (!sname) return std::unexpected<int>(sname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot declare symbol '" + *sname + "' in " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<std::unique_ptr<Symbol>, int> Scope::RemoveSymbol(Symbol* symbol)
{
    return std::unexpected<int>(util::AllocateError("could not remove symbol"));
}

std::expected<bool, int> Scope::AddParentScope(Scope* parentScope_)
{
    return std::unexpected<int>(util::AllocateError("could not add parent scope"));
}

std::expected<bool, int> Scope::PushParentScope(Scope* parentScope)
{
    return std::unexpected<int>(util::AllocateError("could not push parent scope"));
}

std::expected<bool, int> Scope::PopParentScope()
{
    return std::unexpected<int>(util::AllocateError("could not pop parent scope"));
}

std::expected<bool, int> Scope::AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add base class scope to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<bool, int> Scope::AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::u32string, int> fname = usingDeclaration->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname) return std::unexpected<int>(sfname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add using declaration '" + *sfname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'",
        sourcePos, context);
}

std::expected<bool, int> Scope::AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::u32string, int> fname = ns->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    std::expected<std::string, int> sfname = util::ToUtf8(*fname);
    if (!sfname) return std::unexpected<int>(sfname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add using directive '" + *sfname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<ClassGroupSymbol*, int> Scope::GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> sname = util::ToUtf8(name);
    if (!sname) return std::unexpected<int>(sname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add class group '" + *sname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<FunctionGroupSymbol*, int> Scope::GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> sname = util::ToUtf8(name);
    if (!sname) return std::unexpected<int>(sname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add function group '" + *sname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<ConceptGroupSymbol*, int> Scope::GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> sname = util::ToUtf8(name);
    if (!sname) return std::unexpected<int>(sname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add concept group '" + *sname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<VariableGroupSymbol*, int> Scope::GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> sname = util::ToUtf8(name);
    if (!sname) return std::unexpected<int>(sname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add variable group '" + *sname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<AliasGroupSymbol*, int> Scope::GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> sname = util::ToUtf8(name);
    if (!sname) return std::unexpected<int>(sname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add alias group '" + *sname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

std::expected<EnumGroupSymbol*, int> Scope::GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<std::string, int> sname = util::ToUtf8(name);
    if (!sname) return std::unexpected<int>(sname.error());
    std::expected<std::string, int> scopefname = FullName();
    if (!scopefname) return std::unexpected<int>(scopefname.error());
    return Error("cannot add enum group '" + *sname + "' to " + ScopeKindStr(kind) + " '" + *scopefname + "'", sourcePos, context);
}

ContainerScope::ContainerScope() : Scope(), parentScopes(), usingDeclarationScope(nullptr), containerSymbol(nullptr), parentScopePushed(false)
{
}

std::expected<bool, int> ContainerScope::AddParentScope(Scope* parentScope)
{
    if (std::find(parentScopes.begin(), parentScopes.end(), parentScope) == parentScopes.end())
    {
        parentScopes.push_back(parentScope);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ContainerScope::PushParentScope(Scope* parentScope)
{
    if (!parentScopePushed)
    {
        parentScopePushed = true;
        parentScopes.push_back(parentScope);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ContainerScope::PopParentScope()
{
    if (parentScopePushed)
    {
        parentScopePushed = false;
        parentScopes.pop_back();
    }
    return std::expected<bool, int>(true);
}

void ContainerScope::ClearParentScopes()
{
    parentScopes.clear();
}

void ContainerScope::Import(Scope* that, Context* context)
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
            usingDeclarationScope->Import(thatScope->usingDeclarationScope, context);
        }
        for (UsingDirectiveScope* thatUsingDirectiveScope : thatScope->usingDirectiveScopes)
        {
            UsingDirectiveScope* usingDirectiveScope = new UsingDirectiveScope(thatUsingDirectiveScope->Ns());
            scopes.push_back(std::unique_ptr<Scope>(usingDirectiveScope));
            usingDirectiveScopes.push_back(usingDirectiveScope);
            usingDirectiveScope->Import(thatUsingDirectiveScope, context);
        }
    }
}

Scope* ContainerScope::GetClassScope() const
{
    if (Kind() == ScopeKind::classScope)
    {
        return const_cast<Scope*>(static_cast<const Scope*>(this));
    }
    for (Scope* parentScope : parentScopes)
    {
        Scope* classScope = parentScope->GetClassScope();
        if (classScope)
        {
            return classScope;
        }
    }
    return nullptr;
}

Scope* ContainerScope::GetNamespaceScope() const
{
    if (Kind() == ScopeKind::namespaceScope)
    {
        return const_cast<Scope*>(static_cast<const Scope*>(this));
    }
    for (Scope* parentScope : parentScopes)
    {
        Scope* namespaceScope = parentScope->GetNamespaceScope();
        if (namespaceScope)
        {
            return namespaceScope;
        }
    }
    return nullptr;
}

std::expected<bool, int> ContainerScope::AddBaseScope(Scope* baseScope, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (baseScope->IsContainerScope())
    {
        ContainerScope* containerScope = static_cast<ContainerScope*>(baseScope);
        ContainerSymbol* baseClassSymbol = containerScope->GetContainerSymbol();
        Install(baseClassSymbol, context);
    }
    baseScopes.push_back(baseScope);
    return  std::expected<bool, int>(true);
}

Symbol* ContainerScope::GetSymbol()
{
    return containerSymbol;
}

ClassTemplateSpecializationSymbol* ContainerScope::GetClassTemplateSpecialization(std::set<Scope*>& visited) const
{
    if (containerSymbol->IsClassTemplateSpecializationSymbol())
    {
        return static_cast<ClassTemplateSpecializationSymbol*>(containerSymbol);
    }
    else
    {
        for (Scope* parentScope : parentScopes)
        {
            if (visited.find(parentScope) == visited.end())
            {
                visited.insert(parentScope);
                ClassTemplateSpecializationSymbol* sp = parentScope->GetClassTemplateSpecialization(visited);
                if (sp)
                {
                    return sp;
                }
            }
        }
    }
    return nullptr;
}

std::expected<std::string, int> ContainerScope::FullName() const
{
    if (Kind() == ScopeKind::blockScope)
    {
        return std::expected<std::string, int>(std::string());
    }
    std::expected<std::u32string, int> fname = containerSymbol->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    return util::ToUtf8(*fname);
}

void ContainerScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags,
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    Scope::Lookup(id, symbolGroupKinds, scopeLookup, flags, symbols, visited, context);
    if ((scopeLookup & ScopeLookup::parentScope) != ScopeLookup::none)
    {
        for (Scope* parentScope : parentScopes)
        {
            if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
            {
                parentScope->Lookup(id, symbolGroupKinds, scopeLookup, flags, symbols, visited, context);
            }
        }
    }
    if ((scopeLookup & ScopeLookup::baseScope) != ScopeLookup::none)
    {
        if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
        {
            for (Scope* baseScope : baseScopes)
            {
                baseScope->Lookup(id, symbolGroupKinds, scopeLookup, flags, symbols, visited, context);
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
                    usingDeclarationScope->Lookup(id, symbolGroupKinds, scopeLookup, flags, symbols, visited, context);
                }
            }
            for (Scope* usingDirectiveScope : usingDirectiveScopes)
            {
                if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
                {
                    usingDirectiveScope->Lookup(id, symbolGroupKinds, scopeLookup, flags, symbols, visited, context);
                }
            }
        }
    }
}

std::expected<bool, int> ContainerScope::AddUsingDeclaration(Symbol* usingDeclaration, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!usingDeclarationScope)
    {
        usingDeclarationScope = new UsingDeclarationScope(this);
        scopes.push_back(std::unique_ptr<Scope>(usingDeclarationScope));
    }
    usingDeclarationScope->Install(usingDeclaration, context);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ContainerScope::AddUsingDirective(NamespaceSymbol* ns, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (Kind() == ScopeKind::namespaceScope || Kind() == ScopeKind::blockScope)
    {
        for (UsingDirectiveScope* scope : usingDirectiveScopes)
        {
            if (scope->Ns() == ns) return std::expected<bool, int>(true);
        }
        UsingDirectiveScope* usingDirectiveScope = new UsingDirectiveScope(ns);
        scopes.push_back(std::unique_ptr<Scope>(usingDirectiveScope));
        usingDirectiveScopes.push_back(usingDirectiveScope);
    }
    else
    {
        return Error("cannot add using directive to " + ScopeKindStr(Kind()), sourcePos, context);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ContainerScope::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (!symbol->IsValidDeclarationScope(Kind()))
    {
        std::expected<std::string, int> sname = util::ToUtf8(symbol->Name());
        if (!sname) return std::unexpected<int>(sname.error());
        std::expected<std::string, int> scopefname = FullName();
        if (!scopefname) return std::unexpected<int>(scopefname.error());
        return Error("cannot declare symbol '" + *sname + "' in " + ScopeKindStr(Kind()) + " '" + *scopefname + "'", sourcePos, context);
    }
    return containerSymbol->AddSymbol(symbol, sourcePos, context);
}

std::expected<std::unique_ptr<Symbol>, int> ContainerScope::RemoveSymbol(Symbol* symbol)
{
    return std::expected<std::unique_ptr<Symbol>, int>(containerSymbol->RemoveSymbol(symbol));
}

std::expected<ClassGroupSymbol*, int> ContainerScope::GetOrInsertClassGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> rv = Scope::Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (!rv) return std::unexpected<int>(rv.error());
    Symbol* symbol = *rv;
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::classGroupSymbol)
        {
            ClassGroupSymbol* classGroupSymbol = static_cast<ClassGroupSymbol*>(symbol);
            return std::expected<ClassGroupSymbol*, int>(classGroupSymbol);
        }
    }
    ClassGroupSymbol* classGroupSymbol = new ClassGroupSymbol(name);
    std::expected<bool, int> arv = AddSymbol(classGroupSymbol, sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    return std::expected<ClassGroupSymbol*, int>(classGroupSymbol);
}

std::expected<FunctionGroupSymbol*, int> ContainerScope::GetOrInsertFunctionGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> rv = Scope::Lookup(name, SymbolGroupKind::functionSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (!rv) return std::unexpected<int>(rv.error());
    Symbol* symbol = *rv;
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::functionGroupSymbol)
        {
            FunctionGroupSymbol* functionGroupSymbol = static_cast<FunctionGroupSymbol*>(symbol);
            return std::expected<FunctionGroupSymbol*, int>(functionGroupSymbol);
        }
    }
    FunctionGroupSymbol* functionGroupSymbol = new FunctionGroupSymbol(name);
    std::expected<bool, int> arv = AddSymbol(functionGroupSymbol, sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    return std::expected<FunctionGroupSymbol*, int>(functionGroupSymbol);
}

std::expected<ConceptGroupSymbol*, int> ContainerScope::GetOrInsertConceptGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> rv = Scope::Lookup(name, SymbolGroupKind::conceptSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (!rv) return std::unexpected<int>(rv.error());
    Symbol* symbol = *rv;
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::conceptGroupSymbol)
        {
            ConceptGroupSymbol* conceptGroupSymbol = static_cast<ConceptGroupSymbol*>(symbol);
            return std::expected<ConceptGroupSymbol*, int>(conceptGroupSymbol);
        }
    }
    ConceptGroupSymbol* conceptGroupSymbol = new ConceptGroupSymbol(name);
    std::expected<bool, int> arv = AddSymbol(conceptGroupSymbol, sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    return std::expected<ConceptGroupSymbol*, int>(conceptGroupSymbol);
}

std::expected<VariableGroupSymbol*, int> ContainerScope::GetOrInsertVariableGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> rv = Scope::Lookup(name, SymbolGroupKind::variableSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (!rv) return std::unexpected<int>(rv.error());
    Symbol* symbol = *rv;
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::variableGroupSymbol)
        {
            VariableGroupSymbol* variableGroupSymbol = static_cast<VariableGroupSymbol*>(symbol);
            return std::expected<VariableGroupSymbol*, int>(variableGroupSymbol);
        }
    }
    VariableGroupSymbol* variableGroupSymbol = new VariableGroupSymbol(name);
    std::expected<bool, int> arv = AddSymbol(variableGroupSymbol, sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    return std::expected<VariableGroupSymbol*, int>(variableGroupSymbol);
}

std::expected<AliasGroupSymbol*, int> ContainerScope::GetOrInsertAliasGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> rv = Scope::Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (!rv) return std::unexpected<int>(rv.error());
    Symbol* symbol = *rv;
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::aliasGroupSymbol)
        {
            AliasGroupSymbol* aliasGroupSymbol = static_cast<AliasGroupSymbol*>(symbol);
            return std::expected<AliasGroupSymbol*, int>(aliasGroupSymbol);
        }
    }
    AliasGroupSymbol* aliasGroupSymbol = new AliasGroupSymbol(name);
    std::expected<bool, int> arv = AddSymbol(aliasGroupSymbol, sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    return std::expected<AliasGroupSymbol*, int>(aliasGroupSymbol);
}

std::expected<EnumGroupSymbol*, int> ContainerScope::GetOrInsertEnumGroup(const std::u32string& name, const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<Symbol*, int> rv = Scope::Lookup(name, SymbolGroupKind::typeSymbolGroup, ScopeLookup::thisScope, sourcePos, context, LookupFlags::dontResolveSingle);
    if (!rv) return std::unexpected<int>(rv.error());
    Symbol* symbol = *rv;
    if (symbol)
    {
        if (symbol->Kind() == SymbolKind::enumGroupSymbol)
        {
            EnumGroupSymbol* enumGroupSymbol = static_cast<EnumGroupSymbol*>(symbol);
            return std::expected<EnumGroupSymbol*, int>(enumGroupSymbol);
        }
    }
    EnumGroupSymbol* enumGroupSymbol = new EnumGroupSymbol(name);
    std::expected<bool, int> arv = AddSymbol(enumGroupSymbol, sourcePos, context);
    if (!arv) return std::unexpected<int>(arv.error());
    return std::expected<EnumGroupSymbol*, int>(enumGroupSymbol);
}

bool ContainerScope::HasParentScope(const Scope* parentScope) const
{
    const Scope* thisScope = this;
    if (thisScope == parentScope)
    {
        return true;
    }
    for (Scope* scope : parentScopes)
    {
        if (scope->HasParentScope(parentScope)) return true;
    }
    return false;
}

UsingDeclarationScope::UsingDeclarationScope(ContainerScope* parentScope_) : Scope(), parentScope(parentScope_)
{
    SetKind(ScopeKind::usingDeclarationScope);
}

std::expected<std::string, int> UsingDeclarationScope::FullName() const
{
    return parentScope->FullName();
}

void UsingDeclarationScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags,
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    Scope::Lookup(id, symbolGroupKinds, ScopeLookup::thisScope, flags, symbols, visited, context);
}

UsingDirectiveScope::UsingDirectiveScope(NamespaceSymbol* ns_) : Scope(), ns(ns_)
{
    SetKind(ScopeKind::usingDirectiveScope);
}

void UsingDirectiveScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags,
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    if (visited.find(ns->GetScope()) == visited.end())
    {
        visited.insert(ns->GetScope());
        ns->GetScope()->Lookup(id, symbolGroupKinds, scopeLookup, flags, symbols, visited, context);
    }
}

std::expected<std::string, int> UsingDirectiveScope::FullName() const
{
    std::expected<std::u32string, int> fname = ns->FullName();
    if (!fname) return std::unexpected<int>(fname.error());
    return util::ToUtf8(*fname);
}

InstantiationScope::InstantiationScope(Scope* parentScope_)
{
    SetKind(ScopeKind::instantiationScope);
    parentScopes.push_back(parentScope_);
}

std::expected<std::string, int> InstantiationScope::FullName() const
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

std::expected<bool, int>  InstantiationScope::PushParentScope(Scope* parentScope_)
{
    parentScopes.insert(parentScopes.begin(), parentScope_);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> InstantiationScope::PopParentScope()
{
    parentScopes.erase(parentScopes.begin());
    return std::expected<bool, int>(true);
}

bool InstantiationScope::HasParentScope(const Scope* parentScope) const
{
    const Scope* thisScope = this;
    if (thisScope == parentScope)
    {
        return true;
    }
    for (Scope* scope : parentScopes)
    {
        if (scope->HasParentScope(parentScope)) return true;
    }
    return false;
}

ClassTemplateSpecializationSymbol* InstantiationScope::GetClassTemplateSpecialization(std::set<Scope*>& visited) const
{
    for (const Scope* parentScope : parentScopes)
    {
        if (visited.find(parentScope) == visited.end())
        {
            visited.insert(parentScope);
            ClassTemplateSpecializationSymbol* sp = parentScope->GetClassTemplateSpecialization(visited);
            if (sp)
            {
                return sp;
            }
        }
    }
    return nullptr;
}

Scope* InstantiationScope::GetClassScope() const
{
    for (Scope* parentScope : parentScopes)
    {
        Scope* classScope = parentScope->GetClassScope();
        if (classScope)
        {
            return classScope;
        }
    }
    return nullptr;
}

Scope* InstantiationScope::GetNamespaceScope() const
{
    for (Scope* parentScope : parentScopes)
    {
        Scope* namespaceScope = parentScope->GetNamespaceScope();
        if (namespaceScope)
        {
            return namespaceScope;
        }
    }
    return nullptr;
}

void InstantiationScope::Lookup(const std::u32string& id, SymbolGroupKind symbolGroupKinds, ScopeLookup scopeLookup, LookupFlags flags,
    std::vector<Symbol*>& symbols, std::set<Scope*>& visited, Context* context) const
{
    std::vector<Symbol*> foundSymbols;
    Scope::Lookup(id, symbolGroupKinds, ScopeLookup::thisScope, flags, foundSymbols, visited, context);
    for (Symbol* symbol : foundSymbols)
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
                if (symbols.empty() || (flags & LookupFlags::all) != LookupFlags::none)
                {
                    if (visited.find(parentScope) == visited.end())
                    {
                        visited.insert(parentScope);
                        parentScope->Lookup(id, symbolGroupKinds, scopeLookup, flags, symbols, visited, context);
                    }
                }
            }
        }
    }
}

} // namespace otava::symbols
