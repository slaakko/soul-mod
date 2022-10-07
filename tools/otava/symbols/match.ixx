// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.match;

import std.core;
import otava.symbols.bound.tree;
import otava.symbols.fundamental.type.conversion;

export namespace otava::symbols {

struct ArgumentMatch
{
    ArgumentMatch();
    FunctionSymbol* conversionFun;
    ConversionKind conversionKind;
    int32_t distance;
};

struct BetterArgumentMatch
{
    bool operator()(const ArgumentMatch& left, const ArgumentMatch& right) const;
};

struct FunctionMatch
{
    FunctionMatch(FunctionSymbol* function_);
    FunctionSymbol* function;
    std::vector<ArgumentMatch> argumentMatches;
    int numConversions;
};

struct BetterFunctionMatch
{
    bool operator()(const FunctionMatch& left, const FunctionMatch& right) const;
};

} // namespace otava::symbols
