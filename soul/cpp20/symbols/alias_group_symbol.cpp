// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.alias.group.symbol;

import soul.cpp20.symbols.alias.type.symbol;

namespace soul::cpp20::symbols {

AliasGroupSymbol::AliasGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::aliasGroupSymbol, name_)
{
}

bool AliasGroupSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::namespaceScope: 
        case ScopeKind::templateDeclarationScope: 
        case ScopeKind::classScope: 
        case ScopeKind::blockScope: 
        {
            return true;
        }
    }
    return false;
}

Symbol* AliasGroupSymbol::GetSingleSymbol() 
{
    if (aliasTypeSymbols.size() == 1)
    {
        return aliasTypeSymbols.front();
    }
    else
    {
        return this;
    }
}

void AliasGroupSymbol::AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol)
{
    aliasTypeSymbols.push_back(aliasTypeSymbol);
}

AliasTypeSymbol* AliasGroupSymbol::GetAliasTypeSymbol(int arity) const
{
    for (const auto& aliasTypeSymbol : aliasTypeSymbols)
    {
        if (aliasTypeSymbol->Arity() == arity)
        {
            return aliasTypeSymbol;
        }
    }
    return nullptr;
}

} // namespace soul::cpp20::symbols
