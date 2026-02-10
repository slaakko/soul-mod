// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.friends;

import otava.symbols.visitor;

namespace otava::symbols {

FriendSymbol::FriendSymbol(const std::u32string& name_) : Symbol(SymbolKind::friendSymbol, name_)
{
}

std::string FriendSymbol::SymbolKindStr() const 
{ 
    return "friend symbol"; 
}

std::string FriendSymbol::SymbolDocKindStr() const 
{ 
    return "friend"; 
}

bool FriendSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const
{
    switch (scopeKind)
    {
        case ScopeKind::classScope:
        case ScopeKind::blockScope:
        {
            return true;
        }
    }
    return false;
}

void FriendSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::symbols
