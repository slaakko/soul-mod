// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.specialization.compare;

import std.core;

export namespace otava::symbols {

class SpecializationSymbol;

struct SpecializationLess
{
    bool operator()(SpecializationSymbol* left, SpecializationSymbol* right) const;
};

} // namespace otava::symbols
