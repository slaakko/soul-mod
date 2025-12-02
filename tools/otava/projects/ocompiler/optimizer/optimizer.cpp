// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.optimizer;

import otava.optimizer.arithmetics;
import otava.optimizer.dead_code_elimination;
import otava.optimizer.identity_calls;
import otava.optimizer.inliner;
import otava.optimizer.locals;
import otava.optimizer.jumps;
import util.error;

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

std::expected<bool, int> Optimizer::SetOptimizations(const std::string& optLevel)
{
    this->optLevel = optLevel;
    auto it = optMap.find(optLevel);
    if (it != optMap.end())
    {
        otava::optimizer::SetOptimizations(it->second);
    }
    else
    {
        return std::unexpected<int>(util::AllocateError("invalid optimization level '" + optLevel + "'"));
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Optimize(otava::intermediate::Context* context)
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
                std::expected<bool, int> rv = OptimizeIdentityCalls(fn, context);
                if (!rv) return rv;
            }
            if (HasOptimization(Optimizations::inlining))
            {
                std::expected<bool, int> rv = Inline(fn, context);
                if (!rv) return rv;
            }
            if (HasOptimization(Optimizations::moveLocalsToEntryBlock))
            {
                MoveLocalsToEntryBlock(fn);
            }
            if (HasOptimization(Optimizations::arithmetic))
            {
                std::expected<bool, int> rv = OptimizeArithmetics(fn, context);
                if (!rv) return rv;
            }
            if (HasOptimization(Optimizations::jump))
            {
                std::expected<bool, int> rv = OptimizeJumps(fn);
                if (!rv) return rv;
            }
            if (HasOptimization(Optimizations::deadCodeElimination))
            {
                DeadCodeElimination(fn);
            }
        }
        fn = next;
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::optimizer
