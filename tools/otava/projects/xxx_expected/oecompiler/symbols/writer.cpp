// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.writer;

import otava.symbols.symbol;
import otava.symbols.value;
import otava.symbols.compound.type.symbol;

namespace otava::symbols {

Writer::Writer(const std::string& fileName) :
    fileStream(fileName, util::OpenMode::binary | util::OpenMode::write), bufferedStream(fileStream), binaryStreamWriter(bufferedStream), context(nullptr)
{
}

std::expected<bool, int> Writer::Write(Symbol* symbol)
{
    if (symbol)
    {
        std::uint8_t kindByte = static_cast<std::uint8_t>(symbol->Kind());
        std::expected<bool, int> rv = binaryStreamWriter.Write(kindByte);
        if (!rv) return rv;
        rv = binaryStreamWriter.Write(symbol->Name());
        if (!rv) return rv;
        rv = symbol->Write(*this);
        if (!rv) return rv;
    }
    else
    {
        std::uint8_t kindByte = static_cast<std::uint8_t>(SymbolKind::null);
        std::expected<bool, int> rv = binaryStreamWriter.Write(kindByte);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::symbols
