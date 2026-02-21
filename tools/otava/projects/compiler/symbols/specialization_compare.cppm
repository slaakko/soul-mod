// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.specialization.compare;

import std;

export namespace otava::symbols {

class ClassTemplateSpecializationSymbol;
class AliasTypeTemplateSpecializationSymbol;

struct ClassTemplateSpecializationLess
{
    bool operator()(ClassTemplateSpecializationSymbol* left, ClassTemplateSpecializationSymbol* right) const noexcept;
};

struct AliasTypeTemplateSpecializationLess
{
    bool operator()(AliasTypeTemplateSpecializationSymbol* left, AliasTypeTemplateSpecializationSymbol* right) const noexcept;
};

} // namespace otava::symbols
