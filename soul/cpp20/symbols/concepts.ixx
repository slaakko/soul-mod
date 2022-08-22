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
    std::string SymbolDocKindStr() const override { return "concept"; }
    TemplateDeclarationSymbol* ParentTemplateDeclaration();
    void Accept(Visitor& visitor) override;
};

struct ConceptLess
{
    bool operator()(ConceptSymbol* left, ConceptSymbol* right) const;
};

} // namespace soul::cpp20::symbols
