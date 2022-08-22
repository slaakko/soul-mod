// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.templates;

import std.core;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class TypenameConstraintSymbol : public TypeSymbol
{
public:
    TypenameConstraintSymbol();
    std::string SymbolKindStr() const override { return "typename constraint symbol"; }
    std::string SymbolDocKindStr() const override { return "typename_constraint"; }
    void Accept(Visitor& visitor) override;
};

class TemplateParameterSymbol : public TypeSymbol
{
public:
    TemplateParameterSymbol(const std::u32string& name_);
    TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, int index_);
    std::string SymbolKindStr() const override { return "template parameter symbol"; }
    std::string SymbolDocKindStr() const override { return "template_paremeter"; }
    Symbol* Constraint() const { return constraint; }
    int Index() const { return index; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    Symbol* constraint;
    util::uuid constraintId;
    int index;
};

class TemplateDeclarationSymbol : public ContainerSymbol
{
public:
    TemplateDeclarationSymbol();
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::string SymbolKindStr() const override { return "template declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "template_declaration"; }
    const std::vector<TemplateParameterSymbol*>& TemplateParameters() const { return templateParameters; }
    void Accept(Visitor& visitor) override;
private:
    std::vector<TemplateParameterSymbol*> templateParameters;
};

void BeginTemplateDeclaration(soul::cpp20::ast::Node* node, Context* context);
void EndTemplateDeclaration(Context* context);
void RemoveTemplateDeclaration(Context* context);
void AddTemplateParameter(soul::cpp20::ast::Node* templateParameterNode, int index, Context* context);
bool TemplateArgCanBeTypeId(soul::cpp20::ast::Node* templateIdNode, int index);

} // namespace soul::cpp20::symbols
