// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.reader;

import otava.symbols.modules;
import otava.symbols.symbol;
import otava.symbols.class_templates;
import otava.symbols.symbol.table;
import otava.symbols.symbol_map;
import otava.symbols.symbol.factory;

namespace otava::symbols {

Reader::Reader(const std::string& fileName) :
    fileStream(fileName, util::OpenMode::binary | util::OpenMode::read),
    bufferedStream(fileStream),
    binaryStreamReader(bufferedStream),
    context(nullptr),
    symbolTable(nullptr)
{
    if (!fileStream)
    {
        SetError(fileStream.Error());
    }
}

std::expected<Symbol*, int> Reader::ReadSymbol()
{
    std::expected<std::uint8_t, int> brv = binaryStreamReader.ReadByte();
    if (!brv) return std::unexpected<int>(brv.error());
    std::uint8_t b = *brv;
    SymbolKind kind = static_cast<SymbolKind>(b);
    if (kind == SymbolKind::null)
    {
        return std::expected<Symbol*, int>(nullptr);
    }
    else
    {
        std::expected<std::u32string, int> srv = binaryStreamReader.ReadUtf32String();
        if (!srv) return std::unexpected<int>(srv.error());
        std::u32string name = std::move(*srv);
        std::expected<Symbol*, int> crv = CreateSymbol(kind, name, symbolTable);
        if (!crv) return crv;
        Symbol* symbol = *crv;
#ifdef DEBUG_SYMBOL_IO
        std::expected<std::string, int> sname = util::ToUtf8(symbol->Name());
        if (!sname) return std::unexpected<int>(sname.error());
        std::cout << ">reading " << SymbolKindToString(kind) << " '" << *sname << "'\n";
#endif 
        std::expected<bool, int> rv = symbol->Read(*this);
        if (!rv) return std::unexpected<int>(rv.error());
        symbolTable->GetSymbolMap()->AddSymbol(symbol);
#ifdef DEBUG_SYMBOL_IO
        std::cout << "<read " << SymbolKindToString(kind) << " '" << *sname << "'\n";
#endif 
        return std::expected<Symbol*, int>(symbol);
    }
}

void Reader::SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_)
{
    functionDefinitionSymbolSet = functionDefinitionSymbolSet_;
}

FunctionDefinitionSymbolSet* Reader::GetFunctionDefinitionSymbolSet() const
{
    return functionDefinitionSymbolSet;
}

} // namespace otava::symbols
