// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.concept_group.symbol;

import otava.symbols.concepts;
import otava.symbols.visitor;
import otava.symbols.writer;
import otava.symbols.reader;
import otava.symbols.symbol.table;

namespace otava::symbols {

ConceptGroupSymbol::ConceptGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptGroupSymbol, name_)
{
}

void ConceptGroupSymbol::AddConcept(ConceptSymbol* conceptSymbol)
{
    if (std::find(concepts.begin(), concepts.end(), conceptSymbol) == concepts.end())
    {
        concepts.push_back(conceptSymbol);
    }
}

Symbol* ConceptGroupSymbol::GetSingleSymbol() 
{
    if (concepts.size() == 1)
    {
        return concepts.front();
    }
    else
    {
        return this;
    }
}

void ConceptGroupSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConceptGroupSymbol::Write(Writer& writer)
{
    Symbol::Write(writer);
    std::uint32_t count = concepts.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    for (ConceptSymbol* cncp : concepts)
    {
        writer.GetBinaryStreamWriter().Write(cncp->Id());
    }
}

void ConceptGroupSymbol::Read(Reader& reader)
{
    Symbol::Read(reader);
    std::uint32_t count = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (std::uint32_t i = 0; i < count; ++i)
    {
        util::uuid conceptId;
        reader.GetBinaryStreamReader().ReadUuid(conceptId);
        conceptIds.push_back(conceptId);
    }
}

void ConceptGroupSymbol::Resolve(SymbolTable& symbolTable)
{
    Symbol::Resolve(symbolTable);
    for (const auto& conceptId : conceptIds)
    {
        ConceptSymbol* cncp = symbolTable.GetConcept(conceptId);
        if (std::find(concepts.begin(), concepts.end(), cncp) == concepts.end())
        {
            concepts.push_back(cncp);
        }
    }
}

void ConceptGroupSymbol::Merge(ConceptGroupSymbol* that)
{
    for (const auto& cncp : that->concepts)
    {
        if (std::find(concepts.cbegin(), concepts.cend(), cncp) == concepts.end())
        {
            concepts.push_back(cncp);
        }
    }
}

} // namespace otava::symbols
