// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.compound.type.symbol;

import std.core;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.derivations;

export namespace soul::cpp20::symbols {

class CompoundTypeSymbol : public TypeSymbol
{
public:
    CompoundTypeSymbol(const std::u32string& name_);
    CompoundTypeSymbol(TypeSymbol* baseType_, const Derivations& derivations_);
    TypeSymbol* GetBaseType() override { return baseType; }
    std::string SymbolKindStr() const override { return "compound type symbol"; }
    std::string SymbolDocKindStr() const override { return "compound_type"; }
    TypeSymbol* BaseType() const { return baseType; }
    const Derivations& GetDerivations() const { return derivations; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    SymbolTable* GetSymbolTable() override { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_) { symbolTable = symbolTable_; }
private:
    TypeSymbol* baseType;
    Derivations derivations;
    util::uuid baseTypeId;
    SymbolTable* symbolTable;
};

std::u32string MakeCompoundTypeName(TypeSymbol* baseType, const Derivations& derivations);

} // namespace soul::cpp20::symbols
