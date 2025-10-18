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

std::expected<bool, int> CompoundTypeSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = TypeSymbol::Write(writer);
    if (!rv) return rv;
    if (baseType->IsForwardClassDeclarationSymbol())
    {
        ForwardClassDeclarationSymbol* fwdSymbol = static_cast<ForwardClassDeclarationSymbol*>(baseType);
        if (fwdSymbol->GetClassTypeSymbol())
        {
            baseType = fwdSymbol->GetClassTypeSymbol();
        }
    }
    rv = writer.GetBinaryStreamWriter().Write(baseType->Id());
    if (!rv) return rv;
    rv = otava::symbols::Write(writer, derivations);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CompoundTypeSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = TypeSymbol::Read(reader);
    if (!rv) return rv;
    rv = reader.GetBinaryStreamReader().ReadUuid(baseTypeId);
    if (!rv) return rv;
    rv = otava::symbols::Read(reader, derivations);
    if (!rv) return rv;
    reader.GetSymbolTable()->MapType(this);
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CompoundTypeSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = TypeSymbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    baseType = symbolTable.GetType(baseTypeId);
    if (!baseType)
    {
        std::expected<std::string, int> fname = util::ToUtf8(FullName());
        if (!fname) return std::unexpected<int>(rv.error());
        std::cout << "CompoundTypeSymbol::Resolve(): warning: type of '" + *fname + "' not resolved" << "\n";
    }
    return std::expected<bool, int>(true);
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

std::expected<std::string, int> CompoundTypeSymbol::IrName(Context* context) const
{
    std::expected<std::string, int> rv = baseType->IrName(context);
    if (!rv) return rv;
    std::string irName = std::move(*rv);
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
    return std::expected<std::string, int>(irName);
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

std::expected<otava::intermediate::Type*, int> CompoundTypeSymbol::IrType(Emitter& emitter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    otava::intermediate::Type* type = emitter.GetType(Id());
    if (!type)
    {
        std::expected<otava::intermediate::Type*, int> rv = baseType->IrType(emitter, sourcePos, context);
        if (!rv) return rv;
        type = *rv;
        int pointerCount = otava::symbols::PointerCount(derivations);
        for (int i = 0; i < pointerCount; ++i)
        {
            rv = emitter.MakePtrType(type);
            if (!rv) return rv;
            type = *rv;
        }
        if (otava::symbols::HasDerivation(derivations, Derivations::lvalueRefDerivation))
        {
            rv = emitter.MakePtrType(type);
            if (!rv) return rv;
            type = *rv;
        }
        if (otava::symbols::HasDerivation(derivations, Derivations::rvalueRefDerivation))
        {
            rv = emitter.MakePtrType(type);
            if (!rv) return rv;
            type = *rv;
        }
        emitter.SetType(Id(), type);
    }
    return std::expected<otava::intermediate::Type*, int>(type);
}

std::expected<TypeSymbol*, int> CompoundTypeSymbol::FinalType(const soul::ast::SourcePos& sourcePos, Context* context)
{
    std::expected<TypeSymbol*, int> rv = baseType->FinalType(sourcePos, context);
    if (!rv) return rv;
    TypeSymbol* finalBaseType = *rv;
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
    util::uuid derivationsId = symbolTable.GetCompoundTypeId(static_cast<int>(static_cast<std::uint8_t>(derivations)));
    util::Xor(id, derivationsId);
    return id;
}

} // namespace otava::symbols
