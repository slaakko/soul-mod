// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.templates;

import std.core;
import otava.symbols.type.symbol;
import otava.ast.node;
import otava.ast.templates;

export namespace otava::symbols {

class Value;
class ParameterSymbol;

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
    TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, int index_, otava::ast::Node* defaultTemplateArgNode_);
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::string SymbolKindStr() const override { return "template parameter symbol"; }
    std::string SymbolDocKindStr() const override { return "template_paremeter"; }
    Symbol* Constraint() const { return constraint; }
    otava::ast::Node* DefaultTemplateArg() const { return defaultTemplateArgNode; }
    int Index() const { return index; }
    ParameterSymbol* GetParameterSymbol() const { return parameterSymbol; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    TypeSymbol* Unify(TypeSymbol* argType, Context* context) override;
private:
    Symbol* constraint;
    util::uuid constraintId;
    int index;
    otava::ast::Node* defaultTemplateArgNode;
    int64_t defaultTemplateArgNodeId;
    ParameterSymbol* parameterSymbol;
};

class BoundTemplateParameterSymbol : public TypeSymbol
{
public:
    BoundTemplateParameterSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "bound template parameter symbol"; }
    std::string SymbolDocKindStr() const override { return "bound_template_paremeter"; }
    TemplateParameterSymbol* GetTemplateParameterSymbol() const { return templateParameterSymbol; }
    void SetTemplateParameterSymbol(TemplateParameterSymbol* templateParameterSymbol_) { templateParameterSymbol = templateParameterSymbol_; }
    Symbol* BoundSymbol() const { return boundSymbol; }
    void SetBoundSymbol(Symbol* symbol) { boundSymbol = symbol; }
    void Accept(Visitor& visitor) override;
private:
    TemplateParameterSymbol* templateParameterSymbol;
    Symbol* boundSymbol;
};

class TemplateDeclarationSymbol : public ContainerSymbol
{
public:
    TemplateDeclarationSymbol();
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    int Arity() const { return templateParameters.size(); }
    std::string SymbolKindStr() const override { return "template declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "template_declaration"; }
    const std::vector<TemplateParameterSymbol*>& TemplateParameters() const { return templateParameters; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    std::vector<TemplateParameterSymbol*> templateParameters;
};

void BeginTemplateDeclaration(otava::ast::Node* node, Context* context);
void EndTemplateDeclaration(otava::ast::Node* node, Context* context);
void RemoveTemplateDeclaration(Context* context);
void AddTemplateParameter(otava::ast::Node* templateParameterNode, int index, Context* context);
bool TemplateArgCanBeTypeId(otava::ast::Node* templateIdNode, int index);
TypeSymbol* Instantiate(TypeSymbol* typeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, Context* context);

} // namespace otava::symbols
