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

class Reader
{
public:
    Reader(const std::string& fileName);
    util::BinaryStreamReader& GetBinaryStreamReader() { return binaryStreamReader; }
    Symbol* ReadSymbol();
    Context* GetContext() { return context; }
    void SetContext(Context* context_) { context = context_; }
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamReader binaryStreamReader;
    Context* context;
};

} // namespace soul::cpp20::symbols
