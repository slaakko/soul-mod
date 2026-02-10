// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.templates;

import std;
import otava.symbols.classes;
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
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    void Accept(Visitor& visitor) override;
};

class TemplateParameterSymbol : public TypeSymbol
{
public:
    TemplateParameterSymbol(const std::u32string& name_);
    TemplateParameterSymbol(Symbol* constraint_, const std::u32string& name_, const util::uuid& id_, int index_, otava::ast::Node* defaultTemplateArgNode_);
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    inline Symbol* Constraint() const { return constraint; }
    inline otava::ast::Node* DefaultTemplateArg() const { return defaultTemplateArgNode; }
    inline int Index() const { return index; }
    inline ParameterSymbol* GetParameterSymbol() const { return parameterSymbol; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    std::expected<TypeSymbol*, int> Unify(TypeSymbol* argType, Context* context) override;
    std::expected<TypeSymbol*, int> UnifyTemplateArgumentType(
        const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context) override;
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
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
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
    std::expected<bool, int> AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context) override;
    inline int Arity() const { return templateParameters.size(); }
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    inline const std::vector<TemplateParameterSymbol*>& TemplateParameters() const { return templateParameters; }
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    void Accept(Visitor& visitor) override;
private:
    std::vector<TemplateParameterSymbol*> templateParameters;
};

class ExplicitInstantiationSymbol : public Symbol
{
public:
    ExplicitInstantiationSymbol();
    ExplicitInstantiationSymbol(ClassTemplateSpecializationSymbol* specialization_);
    ~ExplicitInstantiationSymbol(); 
    inline ClassTemplateSpecializationSymbol* Specialization() const { return specialization; }
    void AddFunctionDefinitionSymbol(FunctionDefinitionSymbol* functionDefinitionSymbol, const soul::ast::SourcePos& sourcePos, Context* context);
    std::expected<FunctionDefinitionSymbol*, int> GetFunctionDefinitionSymbol(int index)  const;
    FunctionDefinitionSymbol* Destructor() const;
    std::string SymbolKindStr() const override;
    std::string SymbolDocKindStr() const override;
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
private:
    ClassTemplateSpecializationSymbol* specialization;
    util::uuid specializationId;
    std::vector<ExplicitlyInstantiatedFunctionDefinitionSymbol*> functionDefinitionSymbols;
    std::map<std::int32_t, ExplicitlyInstantiatedFunctionDefinitionSymbol*> functionDefinitionSymbolMap;
    FunctionDefinitionSymbol* destructor;
};

std::expected<bool, int> BeginTemplateDeclaration(otava::ast::Node* node, Context* context);
std::expected<bool, int> EndTemplateDeclaration(otava::ast::Node* node, Context* context);
std::expected<bool, int> RemoveTemplateDeclaration(Context* context);
std::expected<bool, int> AddTemplateParameter(otava::ast::Node* templateParameterNode, int index, Context* context);
bool TemplateArgCanBeTypeId(otava::ast::Node* templateIdNode, int index);
std::expected<bool, int> ProcessExplicitInstantiation(otava::ast::Node* node, Context* context);

} // namespace otava::symbols
