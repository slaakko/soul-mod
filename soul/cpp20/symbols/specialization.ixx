// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.specialization;

import std.core;
import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.type.symbol;

export namespace soul::cpp20::symbols {

class SpecializationSymbol : public TypeSymbol
{
public:
    SpecializationSymbol(const std::u32string& name_);
    bool Instantiated() const { return instantiated; }
    void SetInstantiated() { instantiated = true; }
    std::string SymbolKindStr() const override { return "specialization symbol"; }
    std::string SymbolDocKindStr() const override { return "specialization"; }
    TypeSymbol* ClassTemplate() const { return classTemplate; }
    void SetClassTemplate(TypeSymbol* classTemplate_);
    const std::vector<Symbol*>& TemplateArguments() const { return templateArguments; }
    void AddTemplateArgument(Symbol* templateArgument); 
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    SymbolTable* GetSymbolTable() override { return symbolTable; }
    void SetSymbolTable(SymbolTable* symbolTable_) { symbolTable = symbolTable_; }
private:
    TypeSymbol* classTemplate;
    std::vector<Symbol*> templateArguments;
    std::vector<std::pair<util::uuid, bool>> ids;
    SymbolTable* symbolTable;
    bool instantiated;
};

std::u32string MakeSpecializationName(TypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments);

} // namespace soul::cpp20::symbols
