module otava.symbols.type_compare;

import otava.symbols.type.symbol;
import otava.symbols.class_templates;
import otava.symbols.compound.type.symbol;

namespace otava::symbols {

bool TypesEqual(TypeSymbol* left, TypeSymbol* right)
{
    if (left == right) return true;
    if (left->Id() == right->Id()) return true;
    if (left->IsClassTemplateSpecializationSymbol() && right->IsClassTemplateSpecializationSymbol())
    {
        ClassTemplateSpecializationSymbol* leftSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(left);
        ClassTemplateSpecializationSymbol* rightSpecialization = static_cast<ClassTemplateSpecializationSymbol*>(right);
        if (!TypesEqual(leftSpecialization->ClassTemplate(), rightSpecialization->ClassTemplate())) return false;
        if (leftSpecialization->TemplateArguments().size() != rightSpecialization->TemplateArguments().size()) return false;
        int n = leftSpecialization->TemplateArguments().size();
        for (int i = 0; i < n; ++i)
        {
            Symbol* leftTemplateArg = leftSpecialization->TemplateArguments()[i];
            Symbol* rightTemplateArg = rightSpecialization->TemplateArguments()[i];
            if (leftTemplateArg->IsTypeSymbol() && rightTemplateArg->IsTypeSymbol())
            {
                TypeSymbol* leftTemplateArgType = static_cast<TypeSymbol*>(leftTemplateArg);
                TypeSymbol* rightTemplateArgType = static_cast<TypeSymbol*>(rightTemplateArg);
                if (!TypesEqual(leftTemplateArgType, rightTemplateArgType)) return false;
            }
            if (leftTemplateArg != rightTemplateArg) return false;
        }
        return true;
    }
    if (left->IsCompoundTypeSymbol() && right->IsCompoundTypeSymbol())
    {
        CompoundTypeSymbol* leftCompound = static_cast<CompoundTypeSymbol*>(left);
        CompoundTypeSymbol* rightCompound = static_cast<CompoundTypeSymbol*>(right);
        if (TypesEqual(leftCompound->BaseType(), rightCompound->BaseType()) && leftCompound->GetDerivations() == rightCompound->GetDerivations()) return true;
    }
    return false;
}

} // namespace otava::symbols
