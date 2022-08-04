// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.compound.type.symbol;

import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

CompoundTypeSymbol::CompoundTypeSymbol(const std::u32string& name_) :
    TypeSymbol(SymbolKind::compoundTypeSymbol, name_), baseType(nullptr), derivations(), baseTypeId(util::nil_uuid())
{
}

CompoundTypeSymbol::CompoundTypeSymbol(TypeSymbol* baseType_, const Derivations& derivations_) : 
    TypeSymbol(SymbolKind::compoundTypeSymbol, MakeCompoundTypeName(baseType_, derivations_)), baseType(baseType_), derivations(derivations_), baseTypeId(util::nil_uuid())
{
}

void CompoundTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(baseType->Id());
    soul::cpp20::symbols::Write(writer, derivations);
}

void CompoundTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(baseTypeId);
    soul::cpp20::symbols::Read(reader, derivations);
}

void CompoundTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    baseType = symbolTable.GetType(baseTypeId);
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
        name.append(pointerCount, '*');
    }
    if (HasDerivation(derivations, Derivation::lvalueRefDerivation))
    {
        name.append(U"&");
    }
    else if (HasDerivation(derivations, Derivation::rvalueRefDerivation))
    {
        name.append(U"&&");
    }
    return name;
}

} // namespace soul::cpp20::symbols
