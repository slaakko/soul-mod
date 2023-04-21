// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.specialization.compare;

import otava.symbols.class_templates;
import otava.symbols.alias.type.templates;

namespace otava::symbols {

bool ClassTemplateSpecializationLess::operator()(ClassTemplateSpecializationSymbol* left, ClassTemplateSpecializationSymbol* right) const
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
        if (leftArg->Id() < rightArg->Id())
        {
            return true;
        }
        else if (rightArg->Id() < leftArg->Id())
        {
            return false;
        }
    }
    return false;
}

bool AliasTypeTemplateSpecializationLess::operator()(AliasTypeTemplateSpecializationSymbol* left, AliasTypeTemplateSpecializationSymbol* right) const
{
    if (left->AliasTypeTemplate() < right->AliasTypeTemplate())
    {
        return true;
    }
    else if (left->AliasTypeTemplate() > right->AliasTypeTemplate())
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
