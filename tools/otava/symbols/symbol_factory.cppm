// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol.factory;

import std;

export namespace otava::symbols {

enum class SymbolKind : std::int32_t;

class Symbol;
class SymbolTable;

Symbol* CreateSymbol(SymbolKind symbolKind, const std::u32string& name, SymbolTable* symbolTable);

} // namespace otava::symbols
