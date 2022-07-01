// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.function.symbol;

import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;

namespace soul::cpp20::symbols {

ParameterSymbol::ParameterSymbol(const std::u32string& name_) : Symbol(SymbolKind::parameterSymbol, name_), type(nullptr)
{
}

ParameterSymbol::ParameterSymbol(const std::u32string& name_, TypeSymbol* type_) : Symbol(SymbolKind::parameterSymbol, name_), type(type_)
{
}

FunctionSymbol::FunctionSymbol(const std::u32string& name_) : ContainerSymbol(SymbolKind::functionSymbol, name_), returnType(nullptr)
{
}

void FunctionSymbol::AddParameter(ParameterSymbol* parameter, const soul::ast::SourcePos& sourcePos, Context* context)
{
    parameters.push_back(parameter);
    AddSymbol(parameter, sourcePos, context);
}

void FunctionSymbol::Write(Writer& writer)
{
    ContainerSymbol::Write(writer);
    if (returnType)
    {
        writer.GetBinaryStreamWriter().Write(returnType->Id());
    }
    else
    {
        writer.GetBinaryStreamWriter().Write(util::nil_uuid());
    }
}

void FunctionSymbol::Read(Reader& reader)
{
    ContainerSymbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(returnTypeId);
}

void FunctionSymbol::Resolve(SymbolTable& symbolTable)
{
    ContainerSymbol::Resolve(symbolTable);
    if (returnTypeId != util::nil_uuid())
    {
        returnType = symbolTable.GetType(returnTypeId);
    }
}

} // namespace soul::cpp20::symbols
