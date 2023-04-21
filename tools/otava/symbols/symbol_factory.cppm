// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol.factory;

import std.core;

export namespace otava::symbols {

enum class SymbolKind : int32_t;

class Symbol;
class SymbolTable;

Symbol* CreateSymbol(SymbolKind symbolKind, const std::u32string& name, SymbolTable* symbolTable);

} // namespace otava::symbols
