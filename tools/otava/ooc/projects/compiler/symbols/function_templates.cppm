// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.templates;

import std;
import soul.ast.source.pos;
import otava.ast.node;
import otava.symbols.templates;
import otava.symbols.template_param_compare;
import otava.symbols.function.kind;
import otava.symbols.function.symbol;

export namespace otava::symbols {

class TypeSymbol;
class Context;

struct FunctionTemplateKey
{
    FunctionTemplateKey();
    FunctionTemplateKey(FunctionSymbol* functionTemplate_, const std::vector<TypeSymbol*>& templateArgumentTypes_);
    FunctionSymbol* functionTemplate;
    std::vector<TypeSymbol*> templateArgumentTypes;
};

struct FunctionTemplateKeyLess
{
    bool operator()(const FunctionTemplateKey& left, const FunctionTemplateKey& right) const noexcept;
};

class FunctionTemplateRepository
{
public:
    FunctionTemplateRepository();
    FunctionDefinitionSymbol* GetFunctionDefinition(const FunctionTemplateKey& key) const noexcept;
    void AddFunctionDefinition(const FunctionTemplateKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol, otava::ast::Node* functionDefinitionNode);
private:
    std::map<FunctionTemplateKey, FunctionDefinitionSymbol*, FunctionTemplateKeyLess> functionTemplateMap;
    std::vector<std::unique_ptr<otava::ast::Node>> functionDefinitionNodes;
};

FunctionSymbol* InstantiateFunctionTemplate(FunctionSymbol* functionTemplate,
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
