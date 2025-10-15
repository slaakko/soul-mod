// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.symbol_map;

import std;
import util.uuid;
import otava.symbols.symbol;

export namespace otava::symbols {

class SymbolMap
{
public:
    SymbolMap();
    void Import(SymbolMap& that);
    Symbol* GetSymbolNoThrow(const util::uuid& symbolId) const;
    Symbol* GetSymbol(Module* module, SymbolKind symbolKind, const util::uuid& symbolId) const;
    void AddSymbol(Symbol* symbol);
private:
    std::map<util::uuid, Symbol*> symbolMap;
};

} // namespace otava::symbols
