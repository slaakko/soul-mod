// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.variable.symbol;

import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.visitor;

namespace soul::cpp20::symbols {

VariableSymbol::VariableSymbol(const std::u32string& name_) : Symbol(SymbolKind::variableSymbol, name_), type(nullptr), typeId(util::nil_uuid())
{
}

void VariableSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
}

void VariableSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
}

void VariableSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
}

void VariableSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::symbols
