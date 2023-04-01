// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.type.symbol;

import otava.symbols.symbol.table;
import otava.symbols.visitor;
import otava.symbols.compound.type.symbol;
import otava.symbols.fundamental.type.symbol;
import otava.symbols.function.group.symbol;
import otava.symbols.exception;
import otava.symbols.context;
import otava.symbols.writer;
import otava.symbols.reader;

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
    return Kind() == SymbolKind::arrayTypeSymbol;
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

FunctionGroupTypeSymbol::FunctionGroupTypeSymbol(FunctionGroupSymbol* functionGroupSymbol_) :
    TypeSymbol(SymbolKind::functionGroupTypeSymbol, U"@function_group_type"), functionGroupSymbol(functionGroupSymbol_)
{
}

FunctionGroupTypeSymbol::FunctionGroupTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::functionGroupTypeSymbol, name_), functionGroupSymbol(nullptr)
{
}

void FunctionGroupTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(functionGroupSymbol->Id());
}

void FunctionGroupTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(functionGroupSymbolId);
}

void FunctionGroupTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    functionGroupSymbol = symbolTable.GetFunctionGroup(functionGroupSymbolId);
}

void FunctionGroupTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeSymbol* GenericTypeSymbol::Instance()
{
    static GenericTypeSymbol instance;
    return &instance;
}

GenericTypeSymbol::GenericTypeSymbol() : TypeSymbol(SymbolKind::genericTypeSymbol, U"@generic_type")
{
}

void GenericTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::symbols
