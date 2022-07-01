// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.writer;

import std.core;
import util;

export namespace soul::cpp20::symbols {

class Symbol;

class Writer
{
public:
    Writer(const std::string& fileName);
    util::BinaryStreamWriter& GetBinaryStreamWriter() { return binaryStreamWriter; }
    void Write(Symbol* symbol);
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamWriter binaryStreamWriter;
};

} // namespace soul::cpp20::symbols
