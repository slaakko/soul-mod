// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.reader;

import std.core;
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
    util::BinaryStreamReader& GetBinaryStreamReader() { return binaryStreamReader; }
    Symbol* ReadSymbol();
    Context* GetContext() { return context; }
    void SetContext(Context* context_) { context = context_; }
    void SetSymbolTable(SymbolTable* symbolTable_) { symbolTable = symbolTable_; }
    SymbolTable* GetSymbolTable() const { return symbolTable; }
    void SetSymbolMap(SymbolMap* symbolMap_) { symbolMap = symbolMap_; }
    void SetFunctionDefinitionSymbolSet(FunctionDefinitionSymbolSet* functionDefinitionSymbolSet_);
    FunctionDefinitionSymbolSet* GetFunctionDefinitionSymbolSet() const;
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamReader binaryStreamReader;
    Context* context;
    SymbolTable* symbolTable;
    SymbolMap* symbolMap;
    FunctionDefinitionSymbolSet* functionDefinitionSymbolSet;
};

} // namespace otava::symbols
