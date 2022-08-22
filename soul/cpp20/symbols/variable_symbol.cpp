// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module;
#include <boost/uuid/uuid.hpp>

module soul.cpp20.symbols.variable.symbol;

import soul.cpp20.symbols.modules;
import soul.cpp20.symbols.symbol.table;
import soul.cpp20.symbols.type.symbol;
import soul.cpp20.symbols.reader;
import soul.cpp20.symbols.writer;
import soul.cpp20.symbols.value;
import soul.cpp20.symbols.visitor;

namespace soul::cpp20::symbols {

VariableSymbol::VariableSymbol(const std::u32string& name_) : Symbol(SymbolKind::variableSymbol, name_), type(nullptr), typeId(util::nil_uuid()), value(nullptr), valueId(util::nil_uuid())
{
}

void VariableSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    writer.GetBinaryStreamWriter().Write(type->Id());
    bool hasValue = value != nullptr;
    writer.GetBinaryStreamWriter().Write(hasValue);
    if (hasValue)
    {
        writer.GetBinaryStreamWriter().Write(value->Id());
    }
}

void VariableSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    reader.GetBinaryStreamReader().ReadUuid(typeId);
    bool hasValue = reader.GetBinaryStreamReader().ReadBool();
    if (hasValue)
    {
        reader.GetBinaryStreamReader().ReadUuid(valueId);
    }
}

void VariableSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    type = symbolTable.GetType(typeId);
    if (valueId != util::nil_uuid())
    {
        EvaluationContext* evaluationContext = symbolTable.GetModule()->GetEvaluationContext();
        value = evaluationContext->GetValue(valueId);
    }
}

void VariableSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

bool VariableLess::operator()(VariableSymbol* left, VariableSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace soul::cpp20::symbols
