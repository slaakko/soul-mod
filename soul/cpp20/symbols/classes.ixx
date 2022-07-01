// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.classes;

import soul.cpp20.symbols.type.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class TemplateDeclarationSymbol;
class TemplateParameterSymbol;

class ClassTypeSymbol : public TypeSymbol
{
public:
    ClassTypeSymbol(const std::u32string& name_);
    virtual int Arity() const { return 0; }
    std::string SymbolKindStr() const override { return "class type symbol"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    const std::vector<Symbol*>& BaseClasses() const { return baseClasses; }
    void AddBaseClass(Symbol* baseClass, const soul::ast::SourcePos& sourcePos, Context* context);
private:
    std::vector<Symbol*> baseClasses;
};

void BeginClass(soul::cpp20::ast::Node* node, soul::cpp20::symbols::Context* context);
void EndClass(soul::cpp20::symbols::Context* context);

} // namespace soul::cpp20::symbols
