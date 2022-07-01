// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.variable.symbol;

import soul.cpp20.symbols.symbol;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class VariableSymbol : public Symbol
{
public:
    VariableSymbol(const std::u32string& name_);
    virtual int Arity() const { return 0; }
    std::string SymbolKindStr() const override { return "variable symbol"; }
};

} // namespace soul::cpp20::symbols
