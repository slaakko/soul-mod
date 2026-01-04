// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.symbol_map;

import otava.symbols.error;
import otava.symbols.symbol;
import otava.symbols.modules;
import util;

namespace otava::symbols {

SymbolMap::SymbolMap()
{
}

void SymbolMap::Import(SymbolMap& that)
{
    for (const auto& symbol : that.symbolMap)
    {
        symbolMap.insert(symbol);
    }
}

Symbol* SymbolMap::GetSymbol(const util::uuid& symbolId) const
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

std::expected<Symbol*, int> SymbolMap::GetSymbol(Module* module, SymbolKind symbolKind, const util::uuid& symbolId) const
{
    Symbol* symbol = GetSymbol(symbolId);
    if (symbol)
    {
        return std::expected<Symbol*, int>(symbol);
    }
    else
    {
        std::string kindStr;
        if (symbolKind != SymbolKind::null)
        {
            kindStr = "symbol kind is '" + SymbolKindToString(symbolKind) + "', ";
        }
        return std::unexpected<int>(util::AllocateError("symbol id '" + util::ToString(symbolId) + "' not found: note: " + kindStr + "requesting module is '" + 
            module->Name() + "'"));
    }
}

void SymbolMap::AddSymbol(Symbol* symbol)
{
    symbolMap[symbol->Id()] = symbol;
}

} // namespace otava::symbols
