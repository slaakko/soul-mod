// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.match;

namespace otava::symbols {

ArgumentMatch::ArgumentMatch() : conversionFun(nullptr), conversionKind(ConversionKind::implicitConversion), distance(0)
{
}

bool BetterArgumentMatch::operator()(const ArgumentMatch& left, const ArgumentMatch& right) const
{
    if (left.conversionFun == nullptr && right.conversionFun != nullptr) return true;
    if (right.conversionFun == nullptr && left.conversionFun != nullptr) return false;
    if (left.conversionKind == ConversionKind::implicitConversion && right.conversionKind == ConversionKind::narrowingConversion) return true;
    if (left.conversionKind == ConversionKind::narrowingConversion && right.conversionKind == ConversionKind::implicitConversion) return false;
    if (left.distance < right.distance) return true;
    if (left.distance > right.distance) return false;
    return false;
}

FunctionMatch::FunctionMatch(FunctionSymbol* function_) : function(function_), numConversions(0)
{
}

bool BetterFunctionMatch::operator()(const FunctionMatch& left, const FunctionMatch& right) const
{
    BetterArgumentMatch betterArgumentMatch;
    int leftBetterArgumentMatches = 0;
    int rightBetterArgumentMatches = 0;
    int n = std::max(int(left.argumentMatches.size()), int(right.argumentMatches.size()));
    for (int i = 0; i < n; ++i)
    {
        ArgumentMatch leftMatch;
        if (i < int(left.argumentMatches.size()))
        {
            leftMatch = left.argumentMatches[i];
        }
        ArgumentMatch rightMatch;
        if (i < int(right.argumentMatches.size()))
        {
            rightMatch = right.argumentMatches[i];
        }
        if (betterArgumentMatch(leftMatch, rightMatch))
        {
            ++leftBetterArgumentMatches;
        }
        else if (betterArgumentMatch(rightMatch, leftMatch))
        {
            ++rightBetterArgumentMatches;
        }
    }
    if (leftBetterArgumentMatches > rightBetterArgumentMatches)
    {
        return true;
    }
    if (rightBetterArgumentMatches > leftBetterArgumentMatches)
    {
        return false;
    }
    if (left.numConversions < right.numConversions)
    {
        return true;
    }
    if (left.numConversions > right.numConversions)
    {
        return false;
    }
    return false;
}

} // namespace otava::symbols
