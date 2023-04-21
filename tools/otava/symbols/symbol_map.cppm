// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol_map;

import std.core;
import util.uuid;

export namespace otava::symbols {

class Symbol;

class SymbolMap
{
public:
    Symbol* GetSymbol(const util::uuid& symbolId) const;
    void AddSymbol(Symbol* symbol);
private:
    std::map<util::uuid, Symbol*> symbolMap;
};

} // namespace otava::symbols
