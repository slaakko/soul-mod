// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.concepts;

import soul.cpp20.symbols.visitor;
import soul.cpp20.symbols.templates;

namespace soul::cpp20::symbols {

ConceptSymbol::ConceptSymbol(const std::u32string& name_) : Symbol(SymbolKind::conceptSymbol, name_)
{
}

void ConceptSymbol::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TemplateDeclarationSymbol* ConceptSymbol::ParentTemplateDeclaration()
{
    Symbol* parentSymbol = Parent();
    if (parentSymbol->IsTemplateDeclarationSymbol())
    {
        return static_cast<TemplateDeclarationSymbol*>(parentSymbol);
    }
    return nullptr;
}

bool ConceptLess::operator()(ConceptSymbol* left, ConceptSymbol* right) const
{
    return left->Name() < right->Name();
}

} // namespace soul::cpp20::symbols
