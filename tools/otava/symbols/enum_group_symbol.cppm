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
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    inline EnumeratedTypeSymbol* GetEnumType() const { return enumType; }
    inline void SetEnumType(EnumeratedTypeSymbol* enumType_) { enumType = enumType_; }
    inline ForwardEnumDeclarationSymbol* GetForwardDeclaration() const { return forwardDeclaration; }
    inline void SetForwardDeclaration(ForwardEnumDeclarationSymbol* forwardDeclaration_) { forwardDeclaration = forwardDeclaration_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    void Merge(EnumGroupSymbol* that);
private:
    EnumeratedTypeSymbol* enumType;
    util::uuid enumTypeId;
    ForwardEnumDeclarationSymbol* forwardDeclaration;
    util::uuid fwdDeclId;
};

} // namespace otava::symbols
