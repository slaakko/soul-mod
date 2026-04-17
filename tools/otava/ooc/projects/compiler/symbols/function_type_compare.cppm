// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function.type.compare;

import std;

export namespace otava::symbols {

class FunctionTypeSymbol;

struct FunctionTypeCompare
{
    bool operator()(FunctionTypeSymbol* left, FunctionTypeSymbol* right) const noexcept;
};

} // namespace otava::symbols
