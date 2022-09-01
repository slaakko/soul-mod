// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.reader;

import std.core;
import util;

export namespace soul::cpp20::symbols {

class Symbol;
class Context;
class SymbolTable;

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
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamReader binaryStreamReader;
    Context* context;
    SymbolTable* symbolTable;
};

} // namespace soul::cpp20::symbols
