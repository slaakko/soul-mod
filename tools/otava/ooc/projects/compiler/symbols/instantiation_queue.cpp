// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.instantiation_queue;

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

bool operator==(const InstantiationRequest& left, const InstantiationRequest& right) noexcept
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

void InstantiationQueue::EnqueueInstantiationRequest(FunctionSymbol* function, const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap)
{
    InstantiationRequest request(function, templateParameterMap);
    std::vector<InstantiationRequest>& requests = requestMap[function->GetScope()->GetNamespaceScope()->FullName()][function->GroupName()];
    if (std::find(requests.begin(), requests.end(), request) == requests.end())
    {
        requests.push_back(std::move(request));
    }
}

std::vector<InstantiationRequest>* InstantiationQueue::GetRequests(FunctionSymbol* functionTemplate)
{
    auto it = requestMap.find(functionTemplate->GetScope()->GetNamespaceScope()->FullName());
    if (it != requestMap.end())
    {
        auto it2 = it->second.find(functionTemplate->GroupName());
        if (it2 != it->second.end())
        {
            std::vector<InstantiationRequest>* requests = &it2->second;
            return requests;
        }
    }
    return nullptr;
}

void InstantiateEnqueuedRequests(FunctionSymbol* functionTemplate, const soul::ast::SourcePos& sourcePos, Context* context)
{
    InstantiationQueue* instantiationQueue = context->GetInstantiationQueue();
    std::vector<InstantiationRequest>* requests = instantiationQueue->GetRequests(functionTemplate);
    if (requests)
    {
        for (auto it = requests->begin(); it != requests->end(); ++it)
        {
            const InstantiationRequest& request = *it;
            if (FunctionMatches(request.Function(), functionTemplate, context))
            {
                context->SetInstantiationIrName(request.Function()->IrName(context));
                InstantiateFunctionTemplate(functionTemplate, request.TemplateParamMap(), sourcePos, context);
            }
        }
        requests->erase(std::remove_if(requests->begin(), requests->end(), RequestMatches(functionTemplate, context)), requests->end());
    }
}

} // namespace otava::symbols
