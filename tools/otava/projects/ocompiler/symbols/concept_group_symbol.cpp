// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.concept_group.symbol;

import otava.symbols.visitor;
import otava.symbols.writer;
import otava.symbols.reader;

namespace otava::symbols {

ConceptGroupSymbol::ConceptGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptGroupSymbol, name_)
{
}

std::string ConceptGroupSymbol::SymbolKindStr() const 
{ 
    return "concept group symbol"; 
}

std::string ConceptGroupSymbol::SymbolDocKindStr() const 
{ 
    return "concept_group"; 
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

std::expected<bool, int> ConceptGroupSymbol::Write(Writer& writer)
{
    std::expected<bool, int> rv = Symbol::Write(writer);
    if (!rv) return rv;
    std::uint32_t count = concepts.size();
    rv = writer.GetBinaryStreamWriter().WriteULEB128UInt(count);
    if (!rv) return rv;
    for (ConceptSymbol* cncp : concepts)
    {
        rv = writer.GetBinaryStreamWriter().Write(cncp->Id());
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConceptGroupSymbol::Read(Reader& reader)
{
    std::expected<bool, int> rv = Symbol::Read(reader);
    if (!rv) return rv;
    std::expected<std::uint32_t, int> urv = reader.GetBinaryStreamReader().ReadULEB128UInt();
    if (!urv) return std::unexpected<int>(urv.error());
    std::int32_t count = static_cast<std::int32_t>(*urv);
    for (std::int32_t i = 0; i < count; ++i)
    {
        util::uuid conceptId;
        rv = reader.GetBinaryStreamReader().ReadUuid(conceptId);
        if (!rv) return rv;
        conceptIds.push_back(conceptId);
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConceptGroupSymbol::Resolve(SymbolTable& symbolTable, Context* context)
{
    std::expected<bool, int> rv = Symbol::Resolve(symbolTable, context);
    if (!rv) return rv;
    for (const auto& conceptId : conceptIds)
    {
        std::expected<ConceptSymbol*, int> c = symbolTable.GetConcept(conceptId);
        if (!c) return std::unexpected<int>(c.error());
        ConceptSymbol* cncp = *c;
        if (std::find(concepts.begin(), concepts.end(), cncp) == concepts.end())
        {
            concepts.push_back(cncp);
        }
    }
    return std::expected<bool, int>(true);
}

void ConceptGroupSymbol::Merge(ConceptGroupSymbol* that)
{
    for (ConceptSymbol* cncp : that->concepts)
    {
        if (std::find(concepts.cbegin(), concepts.cend(), cncp) == concepts.end())
        {
            concepts.push_back(cncp);
        }
    }
}

} // namespace otava::symbols
