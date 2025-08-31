// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.symbol_map;

import otava.symbols.exception;
import otava.symbols.symbol;
import otava.symbols.modules;
import util;

namespace otava::symbols {

Symbol* SymbolMap::GetSymbolNoThrow(const util::uuid& symbolId) const
{
    auto it = symbolMap.find(symbolId);
    if (it != symbolMap.cend())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

Symbol* SymbolMap::GetSymbol(Module* module, SymbolKind symbolKind, const util::uuid& symbolId) const
{
    Symbol* symbol = GetSymbolNoThrow(symbolId);
    if (symbol)
    {
        return symbol;
    }
    else
    {
        SetExceptionThrown();
        std::string kindStr;
        if (symbolKind != SymbolKind::null)
        {
            kindStr = "symbol kind is '" + SymbolKindToString(symbolKind) + "', ";
        }
        throw std::runtime_error("symbol id '" + util::ToString(symbolId) + "' not found: note: " + kindStr + "requesting module is '" + module->Name() + "'");
    }
}

void SymbolMap::AddSymbol(Symbol* symbol)
{
    symbolMap[symbol->Id()] = symbol;
}

} // namespace otava::symbols
