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
    std::string SymbolDocKindStr() const override { return "alias_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol);
    AliasTypeSymbol* GetAliasTypeSymbol(int arity) const;
    const std::vector<AliasTypeSymbol*>& AliasTypeSymbols() const { return aliasTypeSymbols; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    void Merge(AliasGroupSymbol* that);
private:
    std::vector<AliasTypeSymbol*> aliasTypeSymbols;
    std::vector<util::uuid> aliasTypeIds;
};

} // namespace soul::cpp20::symbols
