// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.specialization.compare;

import otava.symbols.specialization;

namespace otava::symbols {

bool SpecializationLess::operator()(SpecializationSymbol* left, SpecializationSymbol* right) const
{
    if (left->ClassTemplate() < right->ClassTemplate())
    {
        return true;
    }
    else if (left->ClassTemplate() > right->ClassTemplate())
    {
        return false;
    }
    int n = left->TemplateArguments().size();
    int m = right->TemplateArguments().size();
    if (n < m)
    {
        return true;
    }
    else if (n > m)
    {
        return false;
    }
    for (int i = 0; i < n; ++i)
    {
        Symbol* leftArg = left->TemplateArguments()[i];
        Symbol* rightArg = right->TemplateArguments()[i];
        if (leftArg < rightArg)
        {
            return true;
        }
        else if (leftArg > rightArg)
        {
            return false;
        }
    }
    return false;
}

} // namespace otava::symbols
