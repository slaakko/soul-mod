// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.reader;

import soul.cpp20.symbols.symbol;

namespace soul::cpp20::symbols {

Reader::Reader(const std::string& fileName) : 
    fileStream(fileName, util::OpenMode::binary | util::OpenMode::read), bufferedStream(fileStream), binaryStreamReader(bufferedStream), context(nullptr)
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
        Symbol* symbol = CreateSymbol(kind, name);
        symbol->Read(*this);
        return symbol;
    }
}

} // namespace soul::cpp20::symbols
