// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.concepts;

import soul.cpp20.symbols.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class ConceptSymbol : public Symbol
{
public:
    ConceptSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "concept symbol"; }
    void Accept(Visitor& visitor) override;
};

} // namespace soul::cpp20::symbols
