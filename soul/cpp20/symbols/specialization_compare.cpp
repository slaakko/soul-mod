// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.specialization.compare;

import soul.cpp20.symbols.specialization;

namespace soul::cpp20::symbols {

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
        return left;
    }
    else if (n > m)
    {
        return right;
    }
    for (int i = 0; i < n; ++i)
    {
        TypeSymbol* leftArg = left->TemplateArguments()[i];
        TypeSymbol* rightArg = right->TemplateArguments()[i];
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

} // namespace soul::cpp20::symbols
