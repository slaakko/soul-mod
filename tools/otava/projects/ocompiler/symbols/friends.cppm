// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.friends;

import std;
import otava.symbols.symbol;
import otava.symbols.context;
import otava.symbols.symbol.table;

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
