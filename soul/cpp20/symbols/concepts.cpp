// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.concepts;

namespace soul::cpp20::symbols {

ConceptSymbol::ConceptSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptSymbol, name_)
{
}

} // namespace soul::cpp20::symbols
