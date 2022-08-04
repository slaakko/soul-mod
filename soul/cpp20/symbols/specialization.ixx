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
    ClassTypeSymbol* ClassTemplate() const { return classTemplate; }
    void SetClassTemplate(ClassTypeSymbol* classTemplate_);
    const std::vector<TypeSymbol*>& TemplateArguments() const { return templateArguments; }
    void AddTemplateArgument(TypeSymbol* templateArgument); 
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
private:
    ClassTypeSymbol* classTemplate;
    std::vector<TypeSymbol*> templateArguments;
    std::vector<util::uuid> ids;
};

std::u32string MakeSpecializationName(ClassTypeSymbol* classTemplate, const std::vector<TypeSymbol*>& templateArguments);

} // namespace soul::cpp20::symbols
