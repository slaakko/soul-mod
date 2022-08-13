// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.concepts;

import soul.cpp20.symbols.visitor;

namespace soul::cpp20::symbols {

ConceptSymbol::ConceptSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptSymbol, name_)
{
}

void ConceptSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::symbols
