// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.templates;

import std;
import otava.symbols.type.symbol;
import otava.ast.node;
import otava.ast.templates;

export namespace otava::symbols {

class Value;
class ParameterSymbol;
class FunctionDefinitionSymbol;
class ExplicitlyInstantiatedFunctionDefinitionSymbol;

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
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    inline Symbol* Constraint() const { return constraint; }
    inline otava::ast::Node* DefaultTemplateArg() const { return defaultTemplateArgNode; }
    inline int Index() const { return index; }
    inline ParameterSymbol* GetParameterSymbol() const { return parameterSymbol; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    TypeSymbol* Unify(TypeSymbol* argType, Context* context) override;
    TypeSymbol* UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context) override;
private:
    Symbol* constraint;
    util::uuid constraintId;
    int index;
    otava::ast::Node* defaultTemplateArgNode;
    std::int64_t defaultTemplateArgNodeId;
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
    inline Symbol* BoundSymbol() const { return boundSymbol; }
    inline void SetBoundSymbol(Symbol* symbol) { boundSymbol = symbol; }
    void Accept(Visitor& visitor) override;
    bool IsExportSymbol(Context* context) const override { return false; }
private:
    TemplateParameterSymbol* templateParameterSymbol;
    Symbol* boundSymbol;
};

class TemplateDeclarationSymbol : public ContainerSymbol
{
public:
    TemplateDeclarationSymbol();
    void AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline int Arity() const { return templateParameters.size(); }
    std::string SymbolKindStr() const override { return "template declaration symbol"; }
    std::string SymbolDocKindStr() const override { return "template_declaration"; }
    inline const std::vector<TemplateParameterSymbol*>& TemplateParameters() const { return templateParameters; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    std::vector<TemplateParameterSymbol*> templateParameters;
};

class ExplicitInstantiationSymbol : public Symbol
{
public:
    ExplicitInstantiationSymbol();
    ExplicitInstantiationSymbol(ClassTemplateSpecializationSymbol* specialization_);
    inline ClassTemplateSpecializationSymbol* Specialization() const { return specialization; }
    void AddFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol, const soul::ast::SourcePos& sourcePos, Context* context);
    FunctionDefinitionSymbol* GetFunctionDefinitionSymbol(int index)  const;
    FunctionDefinitionSymbol* Destructor() const;
    std::string SymbolKindStr() const override { return "explicit instantiation symbol"; }
    std::string SymbolDocKindStr() const override { return "explicit_instantiation"; }
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
private:
    ClassTemplateSpecializationSymbol* specialization;
    util::uuid specializationId;
    std::vector<std::unique_ptr<ExplicitlyInstantiatedFunctionDefinitionSymbol>> functionDefinitionSymbols;
    FunctionDefinitionSymbol* destructor;
};

void BeginTemplateDeclaration(otava::ast::Node* node, Context* context);
void EndTemplateDeclaration(otava::ast::Node* node, Context* context);
void RemoveTemplateDeclaration(Context* context);
void AddTemplateParameter(otava::ast::Node* templateParameterNode, int index, Context* context);
bool TemplateArgCanBeTypeId(otava::ast::Node* templateIdNode, int index);
void ProcessExplicitInstantiation(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
