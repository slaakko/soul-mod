// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.type.symbol;

import soul.cpp20.symbols.visitor;

namespace soul::cpp20::symbols {

TypeSymbol::TypeSymbol(SymbolKind kind_, const std::u32string& name_) : ContainerSymbol(kind_, name_)
{
}

NestedTypeSymbol::NestedTypeSymbol(const std::u32string& name_) : TypeSymbol(SymbolKind::nestedTypeSymbol, name_)
{
}

void NestedTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ErrorTypeSymbol::ErrorTypeSymbol() : TypeSymbol(SymbolKind::errorSymbol, U"<error_type>")
{
}

void ErrorTypeSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::symbols
