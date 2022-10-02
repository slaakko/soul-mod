// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.concept_group.symbol;

import otava.symbols.concepts;
import otava.symbols.visitor;

namespace otava::symbols {

ConceptGroupSymbol::ConceptGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptGroupSymbol, name_)
{
}

void ConceptGroupSymbol::AddConcept(ConceptSymbol* conceptSymbol)
{
    concepts.push_back(conceptSymbol);
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

} // namespace otava::symbols
