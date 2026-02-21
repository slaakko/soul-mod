// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.writer;

import std;
import util;

export namespace otava::symbols {

class Symbol;
class Context;

class Writer
{
public:
    Writer(const std::string& fileName);
    inline util::BinaryStreamWriter& GetBinaryStreamWriter() { return binaryStreamWriter; }
    void Write(Symbol* symbol);
    inline Context* GetContext() { return context; }
    inline void SetContext(Context* context_) { context = context_; }
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamWriter binaryStreamWriter;
    Context* context;
};

} // namespace otava::symbols
