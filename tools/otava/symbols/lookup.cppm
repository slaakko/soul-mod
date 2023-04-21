// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.lookup;

import std.core;

export namespace otava::symbols {

enum class ScopeLookup : int32_t
{
    none = 0,
    thisScope = 1 << 0,
    parentScope = 1 << 1,
    baseScope = 1 << 2,
    thisAndParentScope = thisScope | parentScope,
    thisAndBaseScopes = thisScope | baseScope,
    thisAndBaseAndParentScope = thisScope | baseScope | parentScope,
    usingScope = 1 << 3,
    allScopes = thisAndBaseAndParentScope | usingScope
};

constexpr ScopeLookup operator|(ScopeLookup left, ScopeLookup right)
{
    return ScopeLookup(int32_t(left) | int32_t(right));
}

constexpr ScopeLookup operator&(ScopeLookup left, ScopeLookup right)
{
    return ScopeLookup(int32_t(left) & int32_t(right));
}

constexpr ScopeLookup operator~(ScopeLookup lookup)
{
    return ScopeLookup(~int32_t(lookup));
}

enum class LookupFlags : int32_t
{
    none = 0, dontResolveSingle = 1 << 0, all = 1 << 1, noFwdDeclarationSymbol = 1 << 2
};

constexpr LookupFlags operator|(LookupFlags left, LookupFlags right)
{
    return LookupFlags(int32_t(left) | int32_t(right));
}

constexpr LookupFlags operator&(LookupFlags left, LookupFlags right)
{
    return LookupFlags(int32_t(left) & int32_t(right));
}

constexpr LookupFlags operator~(LookupFlags flags)
{
    return LookupFlags(~int32_t(flags));
}

} // namespace otava::symbols
