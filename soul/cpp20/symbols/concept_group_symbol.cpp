// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.concept_group.symbol;

import soul.cpp20.symbols.concepts;

namespace soul::cpp20::symbols {

ConceptGroupSymbol::ConceptGroupSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptGroupSymbol, name_)
{
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

} // namespace soul::cpp20::symbols
