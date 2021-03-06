// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.class_group.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.match;

export namespace soul::cpp20::symbols {

class ClassTypeSymbol;
class TypeSymbol;

class ClassGroupSymbol : public Symbol
{
public:
    ClassGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "class group symbol"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddClass(ClassTypeSymbol* classTypeSymbol);
    ClassTypeSymbol* GetClass(int arity) const;
private:
    std::vector<ClassTypeSymbol*> classes;
};

} // namespace soul::cpp20::symbols
