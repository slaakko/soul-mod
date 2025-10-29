// =================================
// Copyright (c) 2025 Seppo Laakko
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
import otava.symbols.modules;
import util;

namespace otava::symbols {

CompoundTypeSymbol::CompoundTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::compoundTypeSymbol, util::nil_uuid(), name_), baseType(nullptr), derivations(), baseTypeId(util::nil_uuid())
{
}

CompoundTypeSymbol::CompoundTypeSymbol(TypeSymbol* baseType_, Derivations derivations_, const util::uuid& id_) :
    TypeSymbol(SymbolKind::compoundTypeSymbol, id_, MakeCompoundTypeName(baseType_, derivations_)), 
    baseType(baseType_), derivations(derivations_), baseTypeId(util::nil_uuid())
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
    reader.GetSymbolTable()->MapType(this);
}

void CompoundTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    TypeSymbol::Resolve(symbolTable, context);
    baseType = symbolTable.GetType(baseTypeId);
    if (!baseType)
    {
        std::string note;
        Module* requesterModule = context->GetRequesterModule();
        if (requesterModule)
        {
            note = ": note: requester module is " + requesterModule->Name();
        }
        std::cout << "CompoundTypeSymbol::Resolve(): warning: type of '" + util::ToUtf8(FullName()) + "' not resolved" << note << "\n";
    }
}

void CompoundTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

bool CompoundTypeSymbol::IsExportSymbol(Context* context) const
{
    return TypeSymbol::IsExportSymbol(context);
}

int CompoundTypeSymbol::PointerCount() const
{
    return otava::symbols::PointerCount(GetDerivations());
}

std::string CompoundTypeSymbol::IrName(Context* context) const
{
    std::string irName = baseType->IrName(context);
    irName.append(1, '_');
    if (HasDerivation(derivations, Derivations::constDerivation))
    {
        irName.append(1, 'C');
    }
    if (HasDerivation(derivations, Derivations::volatileDerivation))
    {
        irName.append(1, 'V');
    }
    if (HasDerivation(derivations, Derivations::lvalueRefDerivation))
    {
        irName.append(1, 'L');
    }
    if (HasDerivation(derivations, Derivations::rvalueRefDerivation))
    {
        irName.append(1, 'R');
    }
    int pointerCount = otava::symbols::PointerCount(derivations);
    if (pointerCount > 0)
    {
        irName.append(pointerCount, 'P');
    }
    return irName;
}

TypeSymbol* CompoundTypeSymbol::RemoveDerivations(Derivations sourceDerivations, Context* context) 
{
    Derivations resultDerivations = Derivations::none;
    if (!HasDerivation(sourceDerivations, Derivations::constDerivation) && HasDerivation(derivations, Derivations::constDerivation))
    {
        resultDerivations = resultDerivations | Derivations::constDerivation;
    }
    int pointerDiff = otava::symbols::PointerCount(derivations) - otava::symbols::PointerCount(sourceDerivations);
    if (pointerDiff != 0)
    {
        resultDerivations = otava::symbols::SetPointerCount(resultDerivations, pointerDiff);
    }
    if (!HasDerivation(sourceDerivations, Derivations::lvalueRefDerivation) && HasDerivation(derivations, Derivations::lvalueRefDerivation))
    {
        resultDerivations = resultDerivations | Derivations::lvalueRefDerivation;
    }
    else if (!HasDerivation(sourceDerivations, Derivations::rvalueRefDerivation) && HasDerivation(derivations, Derivations::rvalueRefDerivation))
    {
        resultDerivations = resultDerivations | Derivations::rvalueRefDerivation;
    }
    return context->GetSymbolTable()->MakeCompoundType(baseType, resultDerivations);
}

TypeSymbol* CompoundTypeSymbol::Unify(TypeSymbol* argType, Context* context)
{
    TypeSymbol* newBaseType = baseType->Unify(argType->GetBaseType(), context);
    return context->GetSymbolTable()->MakeCompoundType(newBaseType, UnifyDerivations(derivations, argType->GetDerivations()));
}

TypeSymbol* CompoundTypeSymbol::UnifyTemplateArgumentType(const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context)
{
    TypeSymbol* newBaseType = baseType->UnifyTemplateArgumentType(templateParameterMap, context);
    return context->GetSymbolTable()->MakeCompoundType(newBaseType, GetDerivations());
}

otava::intermediate::Type* CompoundTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        type = baseType->IrType(emitter, sourcePos, context);
        int pointerCount = otava::symbols::PointerCount(derivations);
        for (int i = 0; i < pointerCount; ++i)
        {
            type = emitter.MakePtrType(type);
        }
        if (otava::symbols::HasDerivation(derivations, Derivations::lvalueRefDerivation))
        {
            type = emitter.MakePtrType(type);
        }
        if (otava::symbols::HasDerivation(derivations, Derivations::rvalueRefDerivation))
        {
            type = emitter.MakePtrType(type);
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

bool CompoundTypeSymbol::IsComplete(std::set<const TypeSymbol*>& visited) const
{
    if (visited.find(this) != visited.end()) return true;
    visited.insert(this);
    return baseType->IsComplete(visited);
}

bool CompoundTypeSymbol::IsTemplateParameterInstantiation(Context* context, std::set<const Symbol*>& visited) const 
{ 
    if (visited.find(this) == visited.end())
    {
        visited.insert(this);
        return baseType->IsTemplateParameterInstantiation(context, visited);
    }
    return false;
}

std::u32string MakeCompoundTypeName(TypeSymbol* baseType, Derivations derivations)
{
    std::u32string name;
    if (HasDerivation(derivations, Derivations::constDerivation))
    {
        name.append(U"const ");
    }
    if (HasDerivation(derivations, Derivations::volatileDerivation))
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
    if (HasDerivation(derivations, Derivations::lvalueRefDerivation))
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
    else if (HasDerivation(derivations, Derivations::rvalueRefDerivation))
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

util::uuid MakeCompoundTypeId(TypeSymbol* baseType, Derivations derivations, SymbolTable& symbolTable)
{
    util::uuid id = baseType->Id();
    util::uuid derivationsId = symbolTable.GetCompoundTypeId(static_cast<int>(derivations));
    util::Xor(id, derivationsId);
    return id;
}

} // namespace otava::symbols
