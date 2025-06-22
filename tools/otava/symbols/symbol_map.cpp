// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.symbol_map;

import otava.symbols.exception;
import otava.symbols.symbol;

namespace otava::symbols {

Symbol* SymbolMap::GetSymbol(const util::uuid& symbolId) const
{
    auto it = symbolMap.find(symbolId);
    if (it != symbolMap.cend())
    {
        return it->second;
    }
    else
    {
        SetExceptionThrown();
        throw std::runtime_error("symbol id " + util::ToString(symbolId) + " not found");
    }
}

void SymbolMap::AddSymbol(Symbol* symbol)
{
    symbolMap[symbol->Id()] = symbol;
}

} // namespace otava::symbols
