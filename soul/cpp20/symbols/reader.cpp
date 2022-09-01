// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.reader;

import soul.cpp20.symbols.symbol;
import soul.cpp20.symbols.symbol.table;

namespace soul::cpp20::symbols {

Reader::Reader(const std::string& fileName) : 
    fileStream(fileName, util::OpenMode::binary | util::OpenMode::read), bufferedStream(fileStream), binaryStreamReader(bufferedStream), context(nullptr), symbolTable(nullptr)
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
        soul::cpp20::symbols::AddSymbol(symbol);
        return symbol;
    }
}

} // namespace soul::cpp20::symbols
