// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol.factory;

import otava.symbols.symbol;
import std;

export namespace otava::symbols {

class SymbolTable;

std::expected<Symbol*, int> CreateSymbol(SymbolKind symbolKind, const std::u32string& name, SymbolTable* symbolTable);

} // namespace otava::symbols
