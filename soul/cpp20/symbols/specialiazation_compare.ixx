// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.specialization.compare;

export namespace soul::cpp20::symbols {

class SpecializationSymbol;

struct SpecializationLess
{
    bool operator()(SpecializationSymbol* left, SpecializationSymbol* right) const;
};

} // namespace soul::cpp20::symbols
