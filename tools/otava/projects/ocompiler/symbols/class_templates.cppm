// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.class_templates;

import std;
import util.uuid;
import otava.ast.node;
import otava.ast.templates;
import otava.symbols.classes;
import otava.symbols.templates;
import otava.symbols.type.symbol;

export namespace otava::symbols {

class CompoundTypeSymbol;
class FunctionDefinitionSymbol;

class ClassTemplateSpecializationSymbol : public ClassTypeSymbol
{
public:
    ClassTemplateSpecializationSymbol(const std::u32string& name_);
    ClassTemplateSpecializationSymbol(const util::uuid& id_, const std::u32string& name_);
    inline bool Instantiated() const { return instantiated; }
    inline void SetInstantiated() { instantiated = true; }
    std::string SymbolKindStr() const override { return "specialization symbol"; }
    std::string SymbolDocKindStr() const override { return "specialization"; }
    inline ClassTypeSymbol* ClassTemplate() const { return classTemplate; }
    void SetClassTemplate(ClassTypeSymbol* classTemplate_);
    const std::u32string& SimpleName() const override { return ClassTemplate()->SimpleName(); }
    std::expected<std::string, int> IrName(Context* context) const override;
    inline const std::vector<Symbol*>& TemplateArguments() const { return templateArguments; }
    void AddTemplateArgument(Symbol* templateArgument);
    std::expected<bool, int> Write(Writer& writer) override;
    std::expected<bool, int> Read(Reader& reader) override;
    std::expected<bool, int> Resolve(SymbolTable& symbolTable, Context* context) override;
    void Accept(Visitor& visitor) override;
    std::expected<TypeSymbol*, int> UnifyTemplateArgumentType(
        const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context) override;
    bool IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const override;
    inline FunctionSymbol* Destructor() const { return destructor; }
    inline void SetDestructor(FunctionSymbol* destructor_) { destructor = destructor_; }
    std::expected<TypeSymbol*, int> FinalType(const soul::ast::SourcePos& sourcePos, Context* context) override;
    bool IsComplete(std::set<const TypeSymbol*>& visited) const override;
    inline bool InstantiatingDestructor() const { return instantiatingDestructor; }
    inline void SetInstantiatingDestructor(bool instantiating) { instantiatingDestructor = instantiating; }
    void AddInstantiatedVirtualFunctionSpecialization(FunctionSymbol* specialization);
    FunctionSymbol* GetMatchingVirtualFunctionSpecialization(FunctionSymbol* newcomer, Context* context) const;
    bool ContainsVirtualFunctionSpecialization(FunctionSymbol* specialization) const;
    ClassGroupSymbol* Group() const override { return ClassTemplate()->Group(); }
    bool IsBasicStringCharType(Context* context) override
    {
        return classTemplate->Name() == U"basic_string" &&
            templateArguments.size() == 1 &&
            (templateArguments.front()->IsCharTypeSymbol() || templateArguments.front()->IsChar8TypeSymbol());
    }
    bool IsBasicStringChar16Type(Context* context) override
    {
        return classTemplate->Name() == U"basic_string" && templateArguments.size() == 1 && templateArguments.front()->IsChar16TypeSymbol();
    }
    bool IsBasicStringChar32Type(Context* context) override
    {
        return classTemplate->Name() == U"basic_string" && templateArguments.size() == 1 && templateArguments.front()->IsChar32TypeSymbol();
    }
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

std::expected<util::uuid, int> MakeClassTemplateSpecializationSymbolId(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArguments, 
    SymbolTable& symbolTable);

struct MemFunKey
{
    MemFunKey() {}
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

std::expected<ClassTemplateSpecializationSymbol*, int> InstantiateClassTemplate(ClassTypeSymbol* classTemplate, const std::vector<Symbol*>& templateArgs,
    const soul::ast::SourcePos& sourcePos, Context* context);

std::expected<FunctionSymbol*, int> InstantiateMemFnOfClassTemplate(FunctionSymbol* memFn,
    ClassTemplateSpecializationSymbol* classTemplateSpecialization, const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap,
    const soul::ast::SourcePos& sourcePos, Context* context);

std::expected<bool, int> InstantiateDestructor(ClassTemplateSpecializationSymbol* specialization, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
