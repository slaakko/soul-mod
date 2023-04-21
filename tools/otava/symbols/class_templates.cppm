// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.class_templates;

import std.core;
import otava.ast.node;
import otava.ast.templates;
import otava.symbols.classes;
import otava.symbols.templates;

export namespace otava::symbols {

class CompoundTypeSymbol;
class FunctionDefinitionSymbol;

class ClassTemplateSpecializationSymbol : public ClassTypeSymbol
{
public:
    ClassTemplateSpecializationSymbol(const std::u32string& name_);
    bool Instantiated() const { return instantiated; }
    void SetInstantiated() { instantiated = true; }
    std::string SymbolKindStr() const override { return "specialization symbol"; }
    std::string SymbolDocKindStr() const override { return "specialization"; }
    ClassTypeSymbol* ClassTemplate() const { return classTemplate; }
    void SetClassTemplate(ClassTypeSymbol* classTemplate_);
    const std::u32string& SimpleName() const override { return ClassTemplate()->SimpleName(); }
    std::string IrName(Context* context) const override;
    const std::vector<Symbol*>& TemplateArguments() const { return templateArguments; }
    void AddTemplateArgument(Symbol* templateArgument);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    TypeSymbol* UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context) override;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    FunctionSymbol* Destructor() const { return destructor; }
    void SetDestructor(FunctionSymbol* destructor_) { destructor = destructor_; }
    TypeSymbol* FinalType(const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsComplete(std::set<const TypeSymbol*>& visited) const override;
    bool InstantiatingDestructor() const { return instantiatingDestructor; }
    void SetInstantiatingDestructor(bool instantiating) { instantiatingDestructor = instantiating; }
    void AddInstantiatedVirtualFunctionSpecialization(FunctionSymbol* specialization);
    FunctionSymbol* GetMatchingVirtualFunctionSpecialization(FunctionSymbol* newcomer, Context* context) const;
    bool ContainsVirtualFunctionSpecialization(FunctionSymbol* specialization) const;
private:
    ClassTypeSymbol* classTemplate;
    std::vector<Symbol*> templateArguments;
    std::vector<std::pair<util::uuid, bool>> ids;
    FunctionSymbol* destructor;
    util::uuid destructorId;
    bool instantiated;
    bool instantiatingDestructor;
    std::vector<FunctionSymbol*> instantiatedVirtualFunctionSpecializations;
    std::vector<util::uuid> instantiatedVirtualFunctionSpecializationIds;
};

struct MemFunKey
{
    MemFunKey(FunctionSymbol* memFun_, const std::vector<TypeSymbol*>& templateArgumentTypes_);
    FunctionSymbol* memFun;
    std::vector<TypeSymbol*> templateArgumentTypes;
};

struct MemFunKeyLess
{
    bool operator()(const MemFunKey& left, const MemFunKey& right) const;
};

class ClassTemplateRepository
{
public:
    ClassTemplateRepository();
    FunctionDefinitionSymbol* GetFunctionDefinition(const MemFunKey& key) const;
    void AddFunctionDefinition(const MemFunKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol, otava::ast::Node* functionDefinitionNode);
private:
    std::map<MemFunKey, FunctionDefinitionSymbol*, MemFunKeyLess> memFunMap;
    std::vector<std::unique_ptr<otava::ast::Node>> functionDefinitionNodes;
};

std::u32string MakeSpecializationName(TypeSymbol* templateSymbol, const std::vector<Symbol*>& templateArguments);

CompoundTypeSymbol* GetCompoundSpecializationArgType(TypeSymbol* specialization, int index);
ClassTemplateSpecializationSymbol* GetClassTemplateSpecializationArgType(TypeSymbol* specialization, int index);

ClassTemplateSpecializationSymbol* InstantiateClassTemplate(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArgs, 
    const soul::ast::SourcePos& sourcePos, Context* context);

FunctionSymbol* InstantiateMemFnOfClassTemplate(FunctionSymbol* memFn,
    ClassTemplateSpecializationSymbol* classTemplateSpecialization, const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap,
    const soul::ast::SourcePos& sourcePos, Context* context);

void InstantiateDestructor(ClassTemplateSpecializationSymbol* specialization, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
