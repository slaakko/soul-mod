// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.class_templates;

import std.core;
import otava.ast.node;
import otava.ast.templates;
import otava.symbols.classes;
import otava.symbols.type.symbol;

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
    TypeSymbol* ClassTemplate() const { return classTemplate; }
    void SetClassTemplate(TypeSymbol* classTemplate_);
    std::string IrName(Context* context) const override;
    const std::vector<Symbol*>& TemplateArguments() const { return templateArguments; }
    void AddTemplateArgument(Symbol* templateArgument);
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Accept(Visitor& visitor) override;
    TypeSymbol* UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*>& templateParameterMap, Context* context) override;
private:
    TypeSymbol* classTemplate;
    std::vector<Symbol*> templateArguments;
    std::vector<std::pair<util::uuid, bool>> ids;
    bool instantiated;
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

CompoundTypeSymbol* GetSpecializationArgType(TypeSymbol* specialization, int index);

TypeSymbol* InstantiateClassTemplate(TypeSymbol* typeSymbol, const std::vector<Symbol*>& templateArgs, otava::ast::TemplateIdNode* node, Context* context);

FunctionDefinitionSymbol* InstantiateMemFnOfClassTemplate(FunctionSymbol* memFn,
    ClassTemplateSpecializationSymbol* classTemplateSpecialization, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
