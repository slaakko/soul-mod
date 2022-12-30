// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.type.symbol;

import otava.symbols.symbol.table;
import otava.symbols.visitor;
import otava.symbols.alias.type.symbol;
import otava.symbols.compound.type.symbol;
import otava.symbols.derivations;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.symbol;
import otava.symbols.exception;
import otava.symbols.context;
import otava.symbols.class_templates;

namespace otava::symbols {

TypeSymbol::TypeSymbol(SymbolKind kind_, const std::u32string& name_) : ContainerSymbol(kind_, name_)
{
}

bool TypeSymbol::IsAutoTypeSymbol() const
{
    if (IsFundamentalTypeSymbol())
    {
        const FundamentalTypeSymbol* fundamentalTypeSymbol = static_cast<const FundamentalTypeSymbol*>(this);
        return fundamentalTypeSymbol->IsAutoTypeSymbol();
    }
    return false;
}

bool TypeSymbol::IsPointerType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivation::pointerDerivation);
    }
    return false;
}

bool TypeSymbol::IsArrayType() const
{
    return false; // TODO!!!
}

bool TypeSymbol::IsConstType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivation::constDerivation);
    }
    return false;
}

bool TypeSymbol::IsLValueRefType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivation::lvalueRefDerivation);
    }
    return false;
}

bool TypeSymbol::IsRValueRefType() const
{
    if (IsCompoundTypeSymbol())
    {
        const CompoundTypeSymbol* compoundTypeSymbol = static_cast<const CompoundTypeSymbol*>(this);
        return HasDerivation(compoundTypeSymbol->GetDerivations(), Derivation::rvalueRefDerivation);
    }
    return false;
}

bool TypeSymbol::IsReferenceType() const
{
    return IsLValueRefType() || IsRValueRefType();
}

TypeSymbol* TypeSymbol::AddConst(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::constDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemoveConst(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveConst(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::AddPointer(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::pointerDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemovePointer(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemovePointer(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::AddLValueRef(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::lvalueRefDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemoveLValueRef(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveLValueRef(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::AddRValueRef(Context* context)
{
    SymbolTable* symbolTable = context->GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::rvalueRefDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemoveRValueRef(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveRValueRef(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::RemoveReference(Context* context)
{
    if (IsLValueRefType())
    {
        return RemoveLValueRef(context);
    }
    else if (IsRValueRefType())
    {
        return RemoveRValueRef(context);
    }
    else
    {
        return this;
    }
}

TypeSymbol* TypeSymbol::RemoveRefOrPtr(Context* context)
{
    if (IsReferenceType())
    {
        return PlainType(context);
    }
    else if (IsPointerType())
    {
        return RemovePointer(context);
    }
    return this;
}

TypeSymbol* TypeSymbol::DirectType(Context* context)
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = context->GetSymbolTable();
        CompoundTypeSymbol* compoundType = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType()->DirectType(context), compoundType->GetDerivations());
    }
    else if (IsAliasTypeSymbol())
    {
        AliasTypeSymbol* aliasTypeSymbol = static_cast<AliasTypeSymbol*>(this);
        TypeSymbol* referredType = aliasTypeSymbol->ReferredType();
        while (referredType->IsAliasTypeSymbol())
        {
            aliasTypeSymbol = static_cast<AliasTypeSymbol*>(referredType);
            referredType = aliasTypeSymbol->ReferredType();
        }
        return referredType;
    }
    else
    {
        return this;
    }
}

const Derivations& TypeSymbol::GetDerivations() const
{
    static Derivations emptyDerivations;
    return emptyDerivations;
}

TypeSymbol* TypeSymbol::RemoveDerivations(const Derivations& derivations, Context* context) 
{
    if (IsPointerType()) return nullptr;
    return this;
}

TypeSymbol* TypeSymbol::Unify(TypeSymbol* argType, Context* context)
{
    return nullptr;
}

otava::intermediate::Type* TypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("IRTYPE not implemented", sourcePos, context);
}

void TypeSymbol::AddSymbol(Symbol* symbol, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ContainerSymbol::AddSymbol(symbol, sourcePos, context);
}

NestedTypeSymbol::NestedTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::nestedTypeSymbol, name_)
{
}

void NestedTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ErrorTypeSymbol::ErrorTypeSymbol() : TypeSymbol(SymbolKind::errorSymbol, U"<error_type>")
{
}

void ErrorTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

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
