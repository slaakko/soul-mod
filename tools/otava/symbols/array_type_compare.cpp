// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.array.type.compare;

import otava.symbols.array.type.symbol;

namespace otava::symbols {

bool ArrayTypeLess::operator()(ArrayTypeSymbol* left, ArrayTypeSymbol* right) const
{
    if (left->ElementType() < right->ElementType()) return true;
    if (left->ElementType() > right->ElementType()) return false;
    return left->Size() < right->Size();
}

} // namespace otava::symbols
