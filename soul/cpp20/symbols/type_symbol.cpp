// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.type.symbol;

import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.alias.type.symbol;
import soul.cpp20.symbols.compound.type.symbol;
import soul.cpp20.symbols.derivations;
import soul.cpp20.symbols.fundamental.type.symbol;

namespace soul::cpp20::symbols {

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
        return symbolTable->MakeCompoundType(GetBaseType(), soul::cpp20::symbols::RemoveConst(compoundTypeSymbol->GetDerivations()));
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
        return symbolTable->MakeCompoundType(GetBaseType(), soul::cpp20::symbols::RemovePointer(compoundTypeSymbol->GetDerivations()));
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
        return symbolTable->MakeCompoundType(GetBaseType(), soul::cpp20::symbols::RemoveLValueRef(compoundTypeSymbol->GetDerivations()));
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
        return symbolTable->MakeCompoundType(GetBaseType(), soul::cpp20::symbols::RemoveRValueRef(compoundTypeSymbol->GetDerivations()));
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

} // namespace soul::cpp20::symbols
