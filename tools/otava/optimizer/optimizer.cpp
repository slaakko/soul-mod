// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.optimizer;

import otava.optimizer.dead_code_elimination;
import otava.optimizer.identity_calls;

namespace otava::optimizer {

Optimizer& Optimizer::Instance()
{
    static Optimizer instance;
    return instance;
}

Optimizer::Optimizer()
{
    optLevel = "2";
    optMap["0"] = Optimizations::o0;
    optMap["1"] = Optimizations::o1;
    optMap["2"] = Optimizations::o2;
    optMap["3"] = Optimizations::o3;
}

void Optimizer::SetOptimizations(const std::string& optLevel)
{
    this->optLevel = optLevel;
    auto it = optMap.find(optLevel);
    if (it != optMap.end())
    {
        otava::optimizer::SetOptimizations(it->second);
    }
    else
    {
        throw std::runtime_error("invalid optimization level '" + optLevel + "'");
    }
}

void Optimize(otava::intermediate::Context* context)
{
    otava::intermediate::Code* code = &context->GetCode();
    otava::intermediate::Function* fn = code->FirstFunction();
    while (fn)
    {
        otava::intermediate::Function* next = fn->Next();
        if (fn->IsDefined())
        {
            if (HasOptimization(Optimizations::deadCodeElimination))
            {
                DeadCodeElimination(fn);
            }
            if (HasOptimization(Optimizations::identity))
            {
                OptimizeIdentityCalls(fn, context);
            }
        }
        fn = next;
    }
}

} // namespace otava::optimizer
