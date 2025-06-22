// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.concept_group.symbol;

import std;
import otava.symbols.symbol;

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
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void Resolve(SymbolTable& symbolTable) override;
    void Merge(ConceptGroupSymbol* that);
private:
    std::vector<ConceptSymbol*> concepts;
    std::vector<util::uuid> conceptIds;
};

} // namespace otava::symbols
