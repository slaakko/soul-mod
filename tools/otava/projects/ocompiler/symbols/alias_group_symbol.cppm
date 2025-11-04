// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.alias.group.symbol;

import std;
import otava.symbols.symbol;

export namespace otava::symbols {

class AliasTypeSymbol;

class AliasGroupSymbol : public Symbol
{
public:
    AliasGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol, Context* context);
    AliasTypeSymbol* GetAliasTypeSymbol(int arity) const;
    inline const std::vector<AliasTypeSymbol*>& AliasTypeSymbols() const { return aliasTypeSymbols; }
    AliasTypeSymbol* GetBestMatchingAliasType(const std::vector<Symbol*>& templateArgs, Context* context) const;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(AliasGroupSymbol* that, Context* context);
    void RemoveAliasType(AliasTypeSymbol* aliasType);
private:
    std::vector<AliasTypeSymbol*> aliasTypeSymbols;
    std::vector<util::uuid> aliasTypeIds;
};

} // namespace otava::symbols
