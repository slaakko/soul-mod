// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.alias.group.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.match;

export namespace soul::cpp20::symbols {

class AliasTypeSymbol;

class AliasGroupSymbol : public Symbol
{
public:
    AliasGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "alias group symbol"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol);
    AliasTypeSymbol* GetAliasTypeSymbol(int arity) const;
private:
    std::vector<AliasTypeSymbol*> aliasTypeSymbols;
};

} // namespace soul::cpp20::symbols
