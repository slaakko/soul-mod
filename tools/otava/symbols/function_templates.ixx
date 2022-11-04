// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.templates;

import std.core;
import soul.ast.source.pos;

export namespace otava::symbols {

class FunctionDefinitionSymbol;
class FunctionSymbol;
class TemplateParameterSymbol;
class TypeSymbol;
class Context;

struct FunctionTemplateKey
{
    FunctionTemplateKey(FunctionSymbol* functionTemplate_, const std::vector<TypeSymbol*>& templateArgumentTypes_);
    FunctionSymbol* functionTemplate;
    std::vector<TypeSymbol*> templateArgumentTypes;
};

struct FunctionTemplateKeyLess
{
    bool operator()(const FunctionTemplateKey& left, const FunctionTemplateKey& right) const;
};

class FunctionTemplateRepository
{
public:
    FunctionTemplateRepository();
    FunctionDefinitionSymbol* GetFunctionDefinition(const FunctionTemplateKey& key) const;
    void AddFunctionDefinition(const FunctionTemplateKey& key, FunctionDefinitionSymbol* functionDefinitionSymbol);
private:
    std::map<FunctionTemplateKey, FunctionDefinitionSymbol*, FunctionTemplateKeyLess> functionTemplateMap;
};

FunctionDefinitionSymbol* InstantiateFunctionTemplate(FunctionSymbol* functionTemplate, const std::map<TemplateParameterSymbol*, TypeSymbol*>& templateParameterMap,
    const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
