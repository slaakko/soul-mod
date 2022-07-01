// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.templates;

import std.core;
import soul.cpp20.symbols.type.symbol;

export namespace soul::cpp20::symbols {

/*
class TypenameConstraintSymbol : public TypeSymbol
{
public:
    TypenameConstraintSymbol();
};
*/

class TemplateParameterSymbol : public TypeSymbol
{
public:
    TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, int index_);
    Symbol* Constraint() const { return constraint; }
    int Index() const { return index; }
private:
    Symbol* constraint;
    int index;
};

class TemplateDeclarationSymbol : public ContainerSymbol
{
public:
    TemplateDeclarationSymbol();
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::string SymbolKindStr() const override { return "template declaration symbol"; }
    const std::vector<TemplateParameterSymbol*>& TemplateParameters() const { return templateParameters; }
private:
    std::vector<TemplateParameterSymbol*> templateParameters;
};


} // namespace soul::cpp20::symbols
