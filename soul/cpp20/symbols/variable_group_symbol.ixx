// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.variable.group.symbol;

import std.core;
import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.match;

export namespace soul::cpp20::symbols {

class VariableSymbol;

class VariableGroupSymbol : public Symbol
{
public:
    VariableGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "variable group symbol"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddVariable(VariableSymbol* variableSymbol);
    VariableSymbol* GetVariable(int arity) const;
private:
    std::vector<VariableSymbol*> variables;
};

} // namespace soul::cpp20::symbols
