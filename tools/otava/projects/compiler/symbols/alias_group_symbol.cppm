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
    std::string SymbolKindStr() const override { return "alias group symbol"; }
    std::string SymbolDocKindStr() const override { return "alias_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    Symbol* GetSingleSymbol() noexcept override;
    void AddAliasTypeSymbol(AliasTypeSymbol* aliasTypeSymbol, Context* context);
    AliasTypeSymbol* GetAliasTypeSymbol(int arity) const noexcept;
    inline const std::vector<AliasTypeSymbol*>& AliasTypeSymbols() const noexcept { return aliasTypeSymbols; }
    AliasTypeSymbol* GetBestMatchingAliasType(const std::vector<Symbol*>& templateArgs, Context* context) noexcept;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(AliasGroupSymbol* that, Context* context);
    void RemoveAliasType(AliasTypeSymbol* aliasType);
private:
    std::vector<AliasTypeSymbol*> aliasTypeSymbols;
    std::vector<util::uuid> aliasTypeIds;
};

} // namespace otava::symbols
