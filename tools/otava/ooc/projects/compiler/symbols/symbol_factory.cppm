// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol.factory;

import std;
import otava.symbols.symbol;
import otava.symbols.symbol.table;

export namespace otava::symbols {

class SymbolTable;

Symbol* CreateSymbol(SymbolKind symbolKind, const std::u32string& name, SymbolTable* symbolTable);

} // namespace otava::symbols
