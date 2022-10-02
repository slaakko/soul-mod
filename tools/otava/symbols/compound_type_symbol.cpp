// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.compound.type.symbol;

import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.visitor;
import otava.symbols.symbol.table;

namespace otava::symbols {

CompoundTypeSymbol::CompoundTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::compoundTypeSymbol, name_), baseType(nullptr), derivations(), baseTypeId(util::nil_uuid()), symbolTable(nullptr)
{
}

CompoundTypeSymbol::CompoundTypeSymbol(TypeSymbol* baseType_, const Derivations& derivations_) : 
    TypeSymbol(SymbolKind::compoundTypeSymbol, MakeCompoundTypeName(baseType_, derivations_)), baseType(baseType_), derivations(derivations_), baseTypeId(util::nil_uuid()),
    symbolTable(nullptr)
{
}
    
void CompoundTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
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
    SetSymbolTable(&symbolTable);
}

void CompoundTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
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
