// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.class_templates;

import std.core;
import otava.ast.templates;
import otava.symbols.classes;
import otava.symbols.type.symbol;

export namespace otava::symbols {

class CompoundTypeSymbol;

class ClassTemplateSpecializationSymbol : public ClassTypeSymbol
{
public:
    ClassTemplateSpecializationSymbol(const std::u32string& name_);
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

std::u32string MakeSpecializationName(TypeSymbol* templateSymbol, const std::vector<Symbol*>& templateArguments);

CompoundTypeSymbol* GetSpecializationArgType(TypeSymbol* specialization, int index);

TypeSymbol* InstantiateClassTemplate(TypeSymbol* typeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, Context* context);

} // namespace otava::symbols
