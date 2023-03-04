// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.compound.type.symbol;

import otava.symbols.emitter;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.classes;
import otava.symbols.context;

namespace otava::symbols {

CompoundTypeSymbol::CompoundTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::compoundTypeSymbol, name_), baseType(nullptr), derivations(), baseTypeId(util::nil_uuid())
{
}

CompoundTypeSymbol::CompoundTypeSymbol(TypeSymbol* baseType_, const Derivations& derivations_) :
    TypeSymbol(SymbolKind::compoundTypeSymbol, MakeCompoundTypeName(baseType_, derivations_)), baseType(baseType_), derivations(derivations_), baseTypeId(util::nil_uuid())
{
}

TypeSymbol* CompoundTypeSymbol::PlainType(Context* context)
{
    Derivations plainDerivations = Plain(derivations);
    return context->GetSymbolTable()->MakeCompoundType(BaseType(), plainDerivations);
}

void CompoundTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    if (baseType->IsForwardClassDeclarationSymbol())
    {
        ForwardClassDeclarationSymbol* fwdSymbol = static_cast<ForwardClassDeclarationSymbol*>(baseType);
        if (fwdSymbol->GetClassTypeSymbol())
        {
            baseType = fwdSymbol->GetClassTypeSymbol();
        }
    }
    writer.GetBinaryStreamWriter().Write(baseType->Id());
    otava::symbols::Write(writer, derivations);
}

void CompoundTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(baseTypeId);
    otava::symbols::Read(reader, derivations);
}

void CompoundTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    baseType = symbolTable.GetType(baseTypeId);
}

void CompoundTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

int CompoundTypeSymbol::PointerCount() const
{
    return otava::symbols::PointerCount(GetDerivations());
}

std::string CompoundTypeSymbol::IrName(Context* context) const
{
    std::string irName = baseType->IrName(context);
    irName.append(1, '_');
    for (const auto& derivation : derivations.vec)
    {
        switch (derivation)
        {
            case Derivation::constDerivation:
            {
                irName.append(1, 'C');
                break;
            }
            case Derivation::volatileDerivation:
            {
                irName.append(1, 'V');
                break;
            }
            case Derivation::lvalueRefDerivation:
            {
                irName.append(1, 'L');
                break;
            }
            case Derivation::rvalueRefDerivation:
            {
                irName.append(1, 'R');
                break;
            }
            case Derivation::pointerDerivation:
            {
                irName.append(1, 'P');
                break;
            }
        }
    }
    return irName;
}

TypeSymbol* CompoundTypeSymbol::RemoveDerivations(const Derivations& sourceDerivations, Context* context) 
{
    Derivations resultDerivations;
    if (!HasDerivation(sourceDerivations, Derivation::constDerivation) && HasDerivation(derivations, Derivation::constDerivation))
    {
        resultDerivations.vec.push_back(Derivation::constDerivation);
    }
    int pointerDiff = otava::symbols::PointerCount(derivations) - otava::symbols::PointerCount(sourceDerivations);
    if (pointerDiff != 0)
    {
        for (int i = 0; i < pointerDiff; ++i)
        {
            resultDerivations.vec.push_back(Derivation::pointerDerivation);
        }
    }
    if (!HasDerivation(sourceDerivations, Derivation::lvalueRefDerivation) && HasDerivation(derivations, Derivation::lvalueRefDerivation))
    {
        resultDerivations.vec.push_back(Derivation::lvalueRefDerivation);
    }
    else if (!HasDerivation(sourceDerivations, Derivation::rvalueRefDerivation) && HasDerivation(derivations, Derivation::rvalueRefDerivation))
    {
        resultDerivations.vec.push_back(Derivation::rvalueRefDerivation);
    }
    return context->GetSymbolTable()->MakeCompoundType(baseType, resultDerivations);
}

TypeSymbol* CompoundTypeSymbol::Unify(TypeSymbol* argType, Context* context)
{
    TypeSymbol* newBaseType = baseType->Unify(argType->GetBaseType(), context);
    return context->GetSymbolTable()->MakeCompoundType(newBaseType, UnifyDerivations(derivations, argType->GetDerivations()));
}

otava::intermediate::Type* CompoundTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        type = baseType->IrType(emitter, sourcePos, context);
        for (const auto& derivation : derivations.vec)
        {
            switch (derivation)
            {
                case Derivation::pointerDerivation:
                case Derivation::lvalueRefDerivation:
                case Derivation::rvalueRefDerivation:
                {
                    type = emitter.MakePtrType(type);
                    break;
                }
            }
        }
        emitter.SetType(Id(), type);
    }
    return type;
}

TypeSymbol* CompoundTypeSymbol::FinalType(const soul::ast::SourcePos& sourcePos, Context* context)
{
    TypeSymbol* finalBaseType = baseType->FinalType(sourcePos, context);
    return context->GetSymbolTable()->MakeCompoundType(finalBaseType, derivations);
}

TypeSymbol* CompoundTypeSymbol::DirectType(Context* context)
{
    TypeSymbol* directBaseType = baseType->DirectType(context);
    return context->GetSymbolTable()->MakeCompoundType(directBaseType, derivations);
}

std::u32string MakeCompoundTypeName(TypeSymbol* baseType, const Derivations& derivations)
{
    std::u32string name;
    if (HasDerivation(derivations, Derivation::constDerivation))
    {
        name.append(U"const ");
    }
    if (HasDerivation(derivations, Derivation::volatileDerivation))
    {
        name.append(U"volatile ");
    }
    name.append(baseType->Name());
    int pointerCount = PointerCount(derivations);
    if (pointerCount > 0)
    {
        if (baseType->PtrIndex() == -1)
        {
            name.append(pointerCount, '*');
        }
        else
        {
            std::u32string ptrStr(pointerCount, '*');
            name.insert(baseType->PtrIndex(), ptrStr);
        }
    }
    if (HasDerivation(derivations, Derivation::lvalueRefDerivation))
    {
        if (baseType->PtrIndex() == -1)
        {
            name.append(U"&");
        }
        else
        {
            name.insert(baseType->PtrIndex(), U"&");
        }
    }
    else if (HasDerivation(derivations, Derivation::rvalueRefDerivation))
    {
        if (baseType->PtrIndex() == -1)
        {
            name.append(U"&&");
        }
        else
        {
            name.insert(baseType->PtrIndex(), U"&&");
        }
    }
    return name;
}

} // namespace otava::symbols
