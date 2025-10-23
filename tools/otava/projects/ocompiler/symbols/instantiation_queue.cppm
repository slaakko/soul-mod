// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.instantiation_queue;

import std;
import otava.symbols.template_param_compare;
import soul.ast.source.pos;

export namespace otava::symbols {

class FunctionSymbol;
class TypeSymbol;
class Context;

class InstantiationRequest
{
public:
    InstantiationRequest(FunctionSymbol* function_, const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap_);
    FunctionSymbol* Function() const { return function; }
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& TemplateParamMap() const { return templateParameterMap; }
private:
    FunctionSymbol* function;
    std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess> templateParameterMap;
};

bool operator==(const InstantiationRequest& left, const InstantiationRequest& right);

class InstantiationQueue
{
public:
    InstantiationQueue();
    std::expected<bool, int> EnqueueInstantiationRequest(FunctionSymbol* function, 
        const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap);
    std::expected<std::vector<InstantiationRequest>*, int> GetRequests(FunctionSymbol* functionTemplate);
private:
    std::map<std::string, std::map<std::u32string, std::vector<InstantiationRequest>>> requestMap;
};

std::expected<bool, int> InstantiateEnqueuedRequests(FunctionSymbol* functionTemplate, const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
