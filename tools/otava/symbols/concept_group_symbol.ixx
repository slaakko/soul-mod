// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.concept_group.symbol;

import std.core;
import otava.symbols.symbol;
import otava.symbols.match;

export namespace otava::symbols {

class ConceptSymbol;

class ConceptGroupSymbol : public Symbol
{
public:
    ConceptGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "concept group symbol"; }
    std::string SymbolDocKindStr() const override { return "concept_group"; }
    Symbol* GetSingleSymbol() override;
    void AddConcept(ConceptSymbol* conceptSymbol);
    const std::vector<ConceptSymbol*>& Concepts() const { return concepts; }
    void Accept(Visitor& visitor) override;
private:
    std::vector<ConceptSymbol*> concepts;
};

} // namespace otava::symbols
