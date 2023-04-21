// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.writer;

import otava.symbols.symbol;

namespace otava::symbols {

Writer::Writer(const std::string& fileName) : fileStream(fileName, util::OpenMode::binary | util::OpenMode::write), bufferedStream(fileStream), binaryStreamWriter(bufferedStream)
{
}

void Writer::Write(Symbol* symbol)
{
    if (symbol)
    {
        static_assert(static_cast<int32_t>(SymbolKind::max) < 256);
        uint8_t kindByte = static_cast<uint8_t>(symbol->Kind());
        binaryStreamWriter.Write(kindByte);
        binaryStreamWriter.Write(symbol->Name());
        symbol->Write(*this);
    }
    else
    {
        uint8_t kindByte = static_cast<uint8_t>(SymbolKind::null);
        binaryStreamWriter.Write(kindByte);
    }
}

} // namespace otava::symbols

