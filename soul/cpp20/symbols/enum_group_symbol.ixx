// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.enum_group.symbol;

import std.core;
import soul.cpp20.symbols.symbol;

export namespace soul::cpp20::symbols {

class ForwardEnumDeclarationSymbol;

class EnumGroupSymbol : public Symbol
{
public:
    EnumGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "enum group symbol"; }
    std::string SymbolDocKindStr() const override { return "enum_group"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    EnumeratedTypeSymbol* GetEnumType() const { return enumType; }
    void SetEnumType(EnumeratedTypeSymbol* enumType_) { enumType = enumType_; }
    ForwardEnumDeclarationSymbol* GetForwardDeclaration() const { return forwardDeclaration; }
    void SetForwardDeclaration(ForwardEnumDeclarationSymbol* forwardDeclaration_) { forwardDeclaration = forwardDeclaration_; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    EnumeratedTypeSymbol* enumType;
    util::uuid enumTypeId;
    ForwardEnumDeclarationSymbol* forwardDeclaration;
    util::uuid fwdDeclId;
};

} // namespace soul::cpp20::symbols
