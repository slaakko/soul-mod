// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.type.compare;

import otava.symbols.function.type.symbol;

namespace otava::symbols {

bool FunctionTypeCompare::operator()(FunctionTypeSymbol* left, FunctionTypeSymbol* right) const noexcept
{
    if (left->ParameterTypes().size() < right->ParameterTypes().size())
    {
        return true;
    }
    if (left->ParameterTypes().size() > right->ParameterTypes().size())
    {
        return false;
    }
    int n = left->ParameterTypes().size();
    for (int i = 0; i < n; ++i)
    {
        TypeSymbol* leftParamType = left->ParameterTypes()[i];
        TypeSymbol* rightParamType = right->ParameterTypes()[i];
        if (leftParamType < rightParamType) return true;
        if (leftParamType > rightParamType) return false;
    }
    return left->ReturnType() < right->ReturnType();
}

} // namespace otava::symbols
