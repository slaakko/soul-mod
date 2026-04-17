// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.reader;

import std;
import util;

export namespace otava::symbols {

class Symbol;
class Context;
class SymbolTable;
class SymbolMap;
class FunctionDefinitionSymbolSet;

class Reader
{
public:
    Reader(const std::string& fileName);
    inline util::BinaryStreamReader& GetBinaryStreamReader() { return binaryStreamReader; }
    Symbol* ReadSymbol();
    inline Context* GetContext() noexcept { return context; }
    inline void SetContext(Context* context_) noexcept { context = context_; }
    inline void SetSymbolTable(SymbolTable* symbolTable_) noexcept { symbolTable = symbolTable_; }
    inline SymbolTable* GetSymbolTable() const noexcept { return symbolTable; }
    void SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_) noexcept;
    FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() const noexcept;
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamReader binaryStreamReader;
    Context* context;
    SymbolTable* symbolTable;
    FunctionDefinitionSymbolSet* functionDefinitionSymbolSet;
};

} // namespace otava::symbols
