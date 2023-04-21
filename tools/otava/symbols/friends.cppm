// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.friends;

import std.core;
import otava.symbols.symbol;

export namespace otava::symbols {

class FriendSymbol : public Symbol
{
public:
    FriendSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "friend symbol"; }
    std::string SymbolDocKindStr() const override { return "friend"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    void Accept(Visitor& visitor) override;
};

} // namespace otava::symbols
