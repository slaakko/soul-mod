// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.function_definition_symbol_set;

import otava.symbols.function.kind;
import otava.symbols.function.symbol;

namespace otava::symbols {

bool FunctionDefinitionSymbolSet::FunctionDefinitionSymbolFound(FunctionDefinitionSymbol* symbol) const
{
    return functionDefinitionSymbols.find(symbol->GetIrName()) != functionDefinitionSymbols.end();
}

void FunctionDefinitionSymbolSet::AddFunctionDefinitionSymbol(FunctionDefinitionSymbol* symbol)
{
    functionDefinitionSymbols.insert(symbol->GetIrName());
}

} // namespace otava::symbols
