// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.enum_group.symbol;

import std;
import otava.symbols.symbol;
import otava.symbols.context;
import otava.symbols.enums;
import otava.symbols.symbol.table;

export namespace otava::symbols {

class EnumGroupSymbol : public Symbol
{
public:
    EnumGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    inline EnumeratedTypeSymbol* GetEnumType() const { return enumType; }
    inline void SetEnumType(EnumeratedTypeSymbol* enumType_) { enumType = enumType_; }
    inline ForwardEnumDeclarationSymbol* GetForwardDeclaration() const { return forwardDeclaration; }
    inline void SetForwardDeclaration(ForwardEnumDeclarationSymbol* forwardDeclaration_) { forwardDeclaration = forwardDeclaration_; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(EnumGroupSymbol* that);
private:
    EnumeratedTypeSymbol* enumType;
    util::uuid enumTypeId;
    ForwardEnumDeclarationSymbol* forwardDeclaration;
    util::uuid fwdDeclId;
};

} // namespace otava::symbols
