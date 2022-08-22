// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.specialization;

import soul.cpp20.symbols.classes;
import soul.cpp20.symbols.type.symbol;
import std.core;

export namespace soul::cpp20::symbols {

class SpecializationSymbol : public TypeSymbol
{
public:
    SpecializationSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "specialization symbol"; }
    std::string SymbolDocKindStr() const override { return "specialization"; }
    TypeSymbol* ClassTemplate() const { return classTemplate; }
    void SetClassTemplate(TypeSymbol* classTemplate_);
    const std::vector<TypeSymbol*>& TemplateArguments() const { return templateArguments; }
    void AddTemplateArgument(TypeSymbol* templateArgument); 
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void ResolveTemplateArgs(SymbolTable& symbolTable);
    void Accept(Visitor& visitor) override;
private:
    TypeSymbol* classTemplate;
    std::vector<TypeSymbol*> templateArguments;
    std::vector<util::uuid> ids;
};

std::u32string MakeSpecializationName(TypeSymbol* classTemplate, const std::vector<TypeSymbol*>& templateArguments);

} // namespace soul::cpp20::symbols
