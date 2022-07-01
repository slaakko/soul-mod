// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.function.group.symbol;

import std.core;
import soul.cpp20.symbols.symbol;

export namespace soul::cpp20::symbols {

class FunctionSymbol;
class ParameterSymbol;
class TypeSymbol;

class FunctionGroupSymbol : public Symbol
{
public:
    FunctionGroupSymbol(const std::u32string& name_);
    std::string SymbolKindStr() const override { return "function group symbol"; }
    bool IsValidDeclarationScope(ScopeKind scopeKind) const override;
    Symbol* GetSingleSymbol() override;
    void AddFunction(FunctionSymbol* function);
    void RemoveFunction(FunctionSymbol* function);
    FunctionSymbol* GetFunction(const std::vector<TypeSymbol*>& parameterTypes) const;
private:
    std::vector<FunctionSymbol*> functions;
};

} // namespace soul::cpp20::symbols
