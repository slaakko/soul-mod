// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.compound.type.symbol;

import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.symbols.symbol.table;
import otava.symbols.classes;
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

std::string CompoundTypeSymbol::SymbolKindStr() const 
{
    return "compound type symbol"; 
}

std::string CompoundTypeSymbol::SymbolDocKindStr() const 
{ 
    return "compound_type"; 
}

std::expected<std::u32string, int> CompoundTypeSymbol::FullName() const
{
    std::u32string fullName;;
    if (HasDerivation(derivations, Derivations::constDerivation))
    {
        fullName.append(U"const ");
    }
    if (HasDerivation(derivations, Derivations::volatileDerivation))
    {
        fullName.append(U"volatile ");
    }
    auto baseFname = baseType->FullName();
    if (!baseFname) return baseFname;
    fullName.append(*baseFname);
    int pointerCount = PointerCount();
    if (pointerCount > 0)
    {
        if (baseType->PtrIndex() == -1)
        {
            fullName.append(pointerCount, '*');
        }
        else
        {
            std::u32string ptrStr(pointerCount, '*');
            fullName.insert(baseType->PtrIndex(), ptrStr);
        }
    }
    if (HasDerivation(derivations, Derivations::lvalueRefDerivation))
    {
        if (baseType->PtrIndex() == -1)
        {
            fullName.append(U"&");
        }
        else
        {
            fullName.insert(baseType->PtrIndex(), U"&");
        }
    }
    else if (HasDerivation(derivations, Derivations::rvalueRefDerivation))
    {
        if (baseType->PtrIndex() == -1)
        {
            fullName.append(U"&&");
        }
        else
        {
            fullName.insert(baseType->PtrIndex(), U"&&");
        }
    }
    return std::expected<std::u32string, int>(fullName);
}

std::expected<TypeSymbol*, int> CompoundTypeSymbol::PlainType(Context* context)
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
        std::expected<std::u32string, int> fname = FullName();
        if (!fname) return std::unexpected<int>(fname.error());
        std::expected<std::string, int> sfname = util::ToUtf8(*fname);
        if (!sfname) return std::unexpected<int>(sfname.error());
        std::cout << "CompoundTypeSymbol::Resolve(): warning: type of '" + *sfname + "' not resolved" << "\n";
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

std::expected<TypeSymbol*, int> CompoundTypeSymbol::RemoveDerivations(Derivations sourceDerivations, Context* context)
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

std::expected<TypeSymbol*, int> CompoundTypeSymbol::Unify(TypeSymbol* argType, Context* context)
{
    std::expected<TypeSymbol*, int> n = baseType->Unify(argType->GetBaseType(), context);
    if (!n) return n;
    TypeSymbol* newBaseType = *n;
    return context->GetSymbolTable()->MakeCompoundType(newBaseType, UnifyDerivations(derivations, argType->GetDerivations()));
}

std::expected<TypeSymbol*, int> CompoundTypeSymbol::UnifyTemplateArgumentType(
    const std::map<TemplateParameterSymbol*, TypeSymbol*, TemplateParamLess>& templateParameterMap, Context* context)
{
    std::expected<TypeSymbol*, int> n = baseType->UnifyTemplateArgumentType(templateParameterMap, context);
    if (!n) return n;
    TypeSymbol* newBaseType = *n;
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

std::expected<TypeSymbol*, int> CompoundTypeSymbol::DirectType(Context* context)
{
    std::expected<TypeSymbol*, int> dt = baseType->DirectType(context);
    if (!dt) return dt;
    TypeSymbol* directBaseType = *dt;
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

bool CompoundTypeSymbol::IsBasicStringCharType(Context* context)
{
    if (PointerCount() == 0)
    {
        std::expected<TypeSymbol*, int> pt = PlainType(context);
        if (!pt) return false;
        TypeSymbol* plainType = *pt;
        return plainType->IsBasicStringCharType(context);
    }
    return false;
}

bool CompoundTypeSymbol::IsBasicStringChar16Type(Context* context)
{
    if (PointerCount() == 0)
    {
        std::expected<TypeSymbol*, int> pt = PlainType(context);
        if (!pt) return false;
        TypeSymbol* plainType = *pt;
        return plainType->IsBasicStringChar16Type(context);
    }
    return false;
}

bool CompoundTypeSymbol::IsBasicStringChar32Type(Context* context)
{
    if (PointerCount() == 0)
    {
        std::expected<TypeSymbol*, int> pt = PlainType(context);
        if (!pt) return false;
        TypeSymbol* plainType = *pt;
        return plainType->IsBasicStringChar32Type(context);
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

std::expected<util::uuid, int> MakeCompoundTypeId(TypeSymbol* baseType, Derivations derivations, SymbolTable& symbolTable)
{
    util::uuid id = baseType->Id();
    std::expected<util::uuid, int> i = symbolTable.GetCompoundTypeId(static_cast<int>(static_cast<std::uint8_t>(derivations)));
    if (!i) return i;
    util::uuid derivationsId = *i;
    util::Xor(id, derivationsId);
    return std::expected<util::uuid, int>(id);
}

} // namespace otava::symbols
