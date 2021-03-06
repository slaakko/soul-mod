// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.concept_group.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.match;

export namespace soul::cpp20::symbols {

class ConceptSymbol;

class ConceptGroupSymbol : public Symbol
{
public:
    ConceptGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "concept group symbol"; }
    Symbol* GetSingleSymbol() override;
    void AddConcept(ConceptSymbol* conceptSymbol);
    ConceptSymbol* GetConcept(const std::vector<Symbol*>& templateArguments, MatchKind matchKind, bool& exact) const;
private:
    std::vector<ConceptSymbol*> concepts;
};

} // namespace soul::cpp20::symbols
