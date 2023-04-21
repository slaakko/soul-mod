// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.alias.group.symbol;

import std.core;
import otava.symbols.type.symbol;

export namespace otava::symbols {

class AliasTypeSymbol;

class AliasGroupSymbol : public TypeSymbol
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
    AliasTypeSymbol* GetBestMatchingAliasType(const std::vector<Symbol*>& templateArgs) const;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    void Merge(AliasGroupSymbol* that);
    void RemoveAliasType(AliasTypeSymbol* aliasType);
private:
    std::vector<AliasTypeSymbol*> aliasTypeSymbols;
    std::vector<util::uuid> aliasTypeIds;
};

} // namespace otava::symbols
