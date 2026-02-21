// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.enum_group.symbol;

import std;
import otava.symbols.symbol;

export namespace otava::symbols {

class ForwardEnumDeclarationSymbol;

class EnumGroupSymbol : public Symbol
{
public:
    EnumGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "enum group symbol"; }
    std::string SymbolDocKindStr() const override { return "enum_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const noexcept override;
    Symbol* GetSingleSymbol() noexcept override;
    inline EnumeratedTypeSymbol* GetEnumType() const noexcept { return enumType; }
    inline void SetEnumType(EnumeratedTypeSymbol* enumType_) noexcept { enumType = enumType_; }
    inline ForwardEnumDeclarationSymbol* GetForwardDeclaration() const noexcept { return forwardDeclaration; }
    inline void SetForwardDeclaration(ForwardEnumDeclarationSymbol* forwardDeclaration_) noexcept { forwardDeclaration = forwardDeclaration_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    void Merge(EnumGroupSymbol* that);
private:
    EnumeratedTypeSymbol* enumType;
    util::uuid enumTypeId;
    ForwardEnumDeclarationSymbol* forwardDeclaration;
    util::uuid fwdDeclId;
};

} // namespace otava::symbols
