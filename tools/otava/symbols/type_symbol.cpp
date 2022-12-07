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

TypeSymbol* TypeSymbol::AddConst() 
{
    SymbolTable* symbolTable = GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::constDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemoveConst()
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveConst(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::AddPointer() 
{
    SymbolTable* symbolTable = GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::pointerDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemovePointer() 
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemovePointer(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::AddLValueRef()
{
    SymbolTable* symbolTable = GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::lvalueRefDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemoveLValueRef()
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveLValueRef(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::AddRValueRef()
{
    SymbolTable* symbolTable = GetSymbolTable();
    Derivations derivations;
    derivations.vec.push_back(Derivation::rvalueRefDerivation);
    return symbolTable->MakeCompoundType(this, derivations);
}

TypeSymbol* TypeSymbol::RemoveRValueRef()
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = GetSymbolTable();
        CompoundTypeSymbol* compoundTypeSymbol = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType(), otava::symbols::RemoveRValueRef(compoundTypeSymbol->GetDerivations()));
    }
    return this;
}

TypeSymbol* TypeSymbol::RemoveReference()
{
    if (IsLValueRefType())
    {
        return RemoveLValueRef();
    }
    else if (IsRValueRefType())
    {
        return RemoveRValueRef();
    }
    else
    {
        return this;
    }
}

TypeSymbol* TypeSymbol::RemoveRefOrPtr()
{
    if (IsReferenceType())
    {
        return PlainType();
    }
    else if (IsPointerType())
    {
        return RemovePointer();
    }
    return this;
}

TypeSymbol* TypeSymbol::DirectType()
{
    if (IsCompoundTypeSymbol())
    {
        SymbolTable* symbolTable = GetSymbolTable();
        CompoundTypeSymbol* compoundType = static_cast<CompoundTypeSymbol*>(this);
        return symbolTable->MakeCompoundType(GetBaseType()->DirectType(), compoundType->GetDerivations());
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
    if (left->IsCompoundTypeSymbol() && right->IsCompoundTypeSymbol())
    {
        CompoundTypeSymbol* leftCompound = static_cast<CompoundTypeSymbol*>(left);
        CompoundTypeSymbol* rightCompound = static_cast<CompoundTypeSymbol*>(right);
        if (TypesEqual(leftCompound->BaseType(), rightCompound->BaseType()) && leftCompound->GetDerivations() == rightCompound->GetDerivations()) return true;
    }
    return false;
}

} // namespace otava::symbols
