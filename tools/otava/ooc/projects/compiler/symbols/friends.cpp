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

bool FriendSymbol::IsValidDeclarationScope(ScopeKind scopeKind) const noexcept
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
