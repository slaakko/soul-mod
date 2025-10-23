// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.instantiation_queue;

import otava.symbols.function.kind;
import otava.symbols.function.symbol;
import otava.symbols.function.templates;
import otava.symbols.inline_functions;
import otava.symbols.context;
import otava.symbols.templates;
import otava.symbols.type_compare;
import otava.symbols.template_param_compare;

namespace otava::symbols {

InstantiationRequest::InstantiationRequest(FunctionSymbol* function_, const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap_) :
    function(function_), templateParameterMap(templateParameterMap_)
{
}

bool operator==(const InstantiationRequest& left, const InstantiationRequest& right)
{
    return left.Function() == right.Function() && left.TemplateParamMap() == right.TemplateParamMap();
}

struct RequestMatches
{
    RequestMatches(FunctionSymbol* functionTemplate_, Context* context_) : functionTemplate(functionTemplate_), context(context_) {}
    bool operator()(const InstantiationRequest& request) const
    {
        return FunctionMatches(functionTemplate, request.Function(), context);
    }
    Context* context;
    FunctionSymbol* functionTemplate;
};

InstantiationQueue::InstantiationQueue() : requestMap()
{
}

std::expected<bool, int> InstantiationQueue::EnqueueInstantiationRequest(FunctionSymbol* function, 
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap)
{
    InstantiationRequest request(function, templateParameterMap);
    std::expected<std::string, int> frv = function->GetScope()->GetNamespaceScope()->FullName();
    if (!frv) return std::unexpected<int>(frv.error());
    std::vector<InstantiationRequest>& requests = requestMap[*frv][function->GroupName()];
    if (std::find(requests.begin(), requests.end(), request) == requests.end())
    {
        requests.push_back(std::move(request));
    }
    return std::expected<bool, int>(true);
}

std::expected<std::vector<InstantiationRequest>*, int> InstantiationQueue::GetRequests(FunctionSymbol* functionTemplate)
{
    std::expected<std::string, int> srv = functionTemplate->GetScope()->GetNamespaceScope()->FullName();
    if (!srv) return std::unexpected<int>(srv.error());
    auto it = requestMap.find(*srv);
    if (it != requestMap.end())
    {
        auto it2 = it->second.find(functionTemplate->GroupName());
        if (it2 != it->second.end())
        {
            std::vector<InstantiationRequest>* requests = &it2->second;
            return std::expected<std::vector<InstantiationRequest>*, int>(requests);
        }
    }
    return std::expected<std::vector<InstantiationRequest>*, int>(nullptr);
}

std::expected<bool, int> InstantiateEnqueuedRequests(FunctionSymbol* functionTemplate, const soul::ast::SourcePos& sourcePos, Context* context)
{
    InstantiationQueue* instantiationQueue = context->GetInstantiationQueue();
    std::expected<std::vector<InstantiationRequest>*, int> rv = instantiationQueue->GetRequests(functionTemplate);
    if (!rv) return std::unexpected<int>(rv.error());
    std::vector<InstantiationRequest>* requests = *rv;
    if (requests)
    {
        for (auto it = requests->begin(); it != requests->end(); ++it)
        {
            const InstantiationRequest& request = *it;
            if (FunctionMatches(request.Function(), functionTemplate, context))
            {
                std::expected<std::string, int> irv = request.Function()->IrName(context);
                if (!irv) return std::unexpected<int>(irv.error());
                context->SetInstantiationIrName(*irv);
                std::expected<FunctionSymbol*, int> rv = InstantiateFunctionTemplate(functionTemplate, request.TemplateParamMap(), sourcePos, context);
                if (!rv) return std::unexpected<int>(rv.error());
            }
        }
        requests->erase(std::remove_if(requests->begin(), requests->end(), RequestMatches(functionTemplate, context)), requests->end());
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
