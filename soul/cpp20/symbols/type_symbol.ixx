// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.type.symbol;

import soul.cpp20.symbols.container.symbol;

export namespace soul::cpp20::symbols {

class TypeSymbol : public ContainerSymbol
{
public:
    TypeSymbol(SymbolKind kind_, const std::u32string& name_);
};

} // namespace soul::cpp20::symbols
