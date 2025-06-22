// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.function_definition_symbol_set;

import std.core;

export namespace otava::symbols {

class FunctionDefinitionSymbol;
class Context;

class FunctionDefinitionSymbolSet
{
public:
    bool FunctionDefinitionSymbolFound(FunctionDefinitionSymbol* symbol) const;
    void AddFunctionDefinitionSymbol(FunctionDefinitionSymbol* symbol);
private:
    std::set<std::string> functionDefinitionSymbols;
};

} // namespace otava::symbols
