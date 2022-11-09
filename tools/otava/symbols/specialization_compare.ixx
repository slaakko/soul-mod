// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.specialization.compare;

import std.core;

export namespace otava::symbols {

class ClassTemplateSpecializationSymbol;
class AliasTypeTemplateSpecializationSymbol;

struct ClassTemplateSpecializationLess
{
    bool operator()(ClassTemplateSpecializationSymbol* left, ClassTemplateSpecializationSymbol* right) const;
};

struct AliasTypeTemplateSpecializationLess
{
    bool operator()(AliasTypeTemplateSpecializationSymbol* left, AliasTypeTemplateSpecializationSymbol* right) const;
};

} // namespace otava::symbols
