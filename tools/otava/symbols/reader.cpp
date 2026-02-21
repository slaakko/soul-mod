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
#ifdef DEBUG_SYMBOL_IO
        std::cout << ">reading " << SymbolKindToString(kind) << " '" << util::ToUtf8(name) << "'\n";
#endif 
        symbol->Read(*this);
        symbolTable->GetSymbolMap()->AddSymbol(symbol);
#ifdef DEBUG_SYMBOL_IO
        std::cout << "<read " << SymbolKindToString(kind) << " '" << util::ToUtf8(name) << "'\n";
#endif 
        return symbol;
    }
}

void Reader::SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_) noexcept
{
    functionDefinitionSymbolSet = functionDefinitionSymbolSet_;
}

FunctionDefinitionSymbolSet* Reader::GetFunctionDefinitionSymbolSet() const noexcept
{
    return functionDefinitionSymbolSet;
}

} // namespace otava::symbols
