// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.variable.symbol;

namespace soul::cpp20::symbols {

VariableSymbol::VariableSymbol(const std::u32string& name_) : Symbol(SymbolKind::variableSymbol, name_)
{
}

} // namespace soul::cpp20::symbols
