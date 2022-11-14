// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function.type.symbol;

import otava.symbols.symbol.table;
import otava.symbols.reader;
import otava.symbols.writer;
import otava.symbols.visitor;

namespace otava::symbols {

FunctionTypeSymbol::FunctionTypeSymbol() : TypeSymbol(SymbolKind::functionTypeSymbol, std::u32string()), ptrIndex(-1), returnType(), returnTypeId()
{
}

FunctionTypeSymbol::FunctionTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::functionTypeSymbol, name_), ptrIndex(-1), returnType(), returnTypeId()
{
}

void FunctionTypeSymbol::MakeName()
{
    std::u32string name = returnType->Name();
    name.append(U" (");
    ptrIndex = name.length();
    name.append(U")(");
    bool first = true;
    for (const auto& parameterType : parameterTypes)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            name.append(U", ");
        }
        name.append(parameterType->Name());
    }
    name.append(U")");
    SetName(name);
}

void FunctionTypeSymbol::AddParameterType(TypeSymbol* parameterType)
{
    parameterTypes.push_back(parameterType);
}

void FunctionTypeSymbol::Write(Writer& writer)
{
    TypeSymbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(returnType->Id());
    uint32_t paramTypeCount = parameterTypes.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(paramTypeCount);
    for (const auto& paramType : parameterTypes)
    {
        writer.GetBinaryStreamWriter().Write(paramType->Id());
    }
}

void FunctionTypeSymbol::Read(Reader& reader)
{
    TypeSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
    uint32_t paramTypeCount = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < paramTypeCount; ++i)
    {
        util::uuid paramTypeId;
        reader.GetBinaryStreamReader().ReadUuid(paramTypeId);
        parameterTypeIds.push_back(paramTypeId);
    }
}

void FunctionTypeSymbol::Resolve(SymbolTable& symbolTable)
{
    TypeSymbol::Resolve(symbolTable);
    returnType = symbolTable.GetType(returnTypeId);
    for (const auto& parameterTypeId : parameterTypeIds)
    {
        TypeSymbol* parameterType = symbolTable.GetType(parameterTypeId);
        parameterTypes.push_back(parameterType);
    }
}

void FunctionTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::symbols
