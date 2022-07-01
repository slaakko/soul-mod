// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.type.symbol;

namespace soul::cpp20::symbols {

TypeSymbol::TypeSymbol(SymbolKind kind_, const std::u32string& name_) : ContainerSymbol(kind_, name_)
{
}

} // namespace soul::cpp20::symbols
