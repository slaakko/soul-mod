// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.optimizer;

import std;
import otava.intermediate;

export namespace otava::optimizer {

enum class Optimizations : std::uint64_t
{
    none = 0,
    xor_ = 1 << 0,
    jump = 1 << 1,
    removeNops = 1 << 2,
    jumpTableSwitch = 1 << 3,
    arithmetic = 1 << 4,
    identity = 1 << 5,
    deadCodeElimination = 1 << 6,
    moveLocalsToEntryBlock = 1 << 7,
    inlining = 1 << 8,
    o0 = none,
    o1 = xor_ | jump | removeNops | jumpTableSwitch | arithmetic | identity | deadCodeElimination | moveLocalsToEntryBlock,
    o2 = xor_ | jump | removeNops | jumpTableSwitch | arithmetic | identity | deadCodeElimination | moveLocalsToEntryBlock | inlining,
    o3 = xor_ | jump | removeNops | jumpTableSwitch | arithmetic | identity | deadCodeElimination | moveLocalsToEntryBlock | inlining
};

constexpr Optimizations operator|(Optimizations left, Optimizations right)
{
    return Optimizations(static_cast<std::uint64_t>(left) | static_cast<std::uint64_t>(right));
}

constexpr Optimizations operator&(Optimizations left, Optimizations right)
{
    return Optimizations(static_cast<std::uint64_t>(left) & static_cast<std::uint64_t>(right));
}

constexpr Optimizations operator~(Optimizations operand)
{
    return Optimizations(~static_cast<std::uint64_t>(operand));
}

Optimizations currentOptimizations = Optimizations::o2;

inline void SetOptimizations(Optimizations optimizations)
{
    currentOptimizations = optimizations;
}

inline bool HasOptimization(Optimizations optimization)
{
    return (currentOptimizations & optimization) != Optimizations::none;
}

class Optimizer
{
public:
    static Optimizer& Instance();
    std::expected<bool, int> SetOptimizations(const std::string& optLevel);
    inline const std::string& OptLevel() const { return optLevel; }
private:
    Optimizer();
    std::map<std::string, Optimizations> optMap;
    std::string optLevel;
};

std::expected<bool, int> Optimize(otava::intermediate::Context* context);

} // otava::optimizer
