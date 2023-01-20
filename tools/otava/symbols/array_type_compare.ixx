// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.array.type.compare;

import std.core;

export namespace otava::symbols {

class ArrayTypeSymbol;

struct ArrayTypeLess
{
    bool operator()(ArrayTypeSymbol* left, ArrayTypeSymbol* right) const;
};

} // namespace otava::symbols
