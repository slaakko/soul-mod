// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.reader;

import otava.symbols.modules;
import otava.symbols.symbol;
import otava.symbols.symbol.table;
import otava.symbols.symbol.factory;

namespace otava::symbols {

Reader::Reader(const std::string& fileName) : 
    fileStream(fileName, util::OpenMode::binary | util::OpenMode::read), 
    bufferedStream(fileStream), 
    binaryStreamReader(bufferedStream), 
    context(nullptr), 
    symbolTable(nullptr),
    symbolMap(nullptr)
{
}

Symbol* Reader::ReadSymbol()
{
    SymbolKind kind = static_cast<SymbolKind>(binaryStreamReader.ReadByte());
    if (kind == SymbolKind::null)
    {
        return nullptr;
    }
    else
    {
        std::u32string name = binaryStreamReader.ReadUtf32String();
        Symbol* symbol = CreateSymbol(kind, name, symbolTable);
        symbol->Read(*this);
        symbolMap->AddSymbol(symbol);
        return symbol;
    }
}

} // namespace otava::symbols
