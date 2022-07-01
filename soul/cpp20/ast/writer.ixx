// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.writer;

import std.core;
import util;
import soul.ast.source.pos;
import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

class Writer
{
public:
    Writer(const std::string& fileName);
    util::BinaryStreamWriter& GetBinaryStreamWriter() { return binaryStreamWriter; }
    void Write(const soul::ast::SourcePos& sourcePos);
    void Write(NodeKind nodeKind);
    void Write(const std::u32string& str);
    void Write(bool value);
    void Write(Node* node);
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamWriter binaryStreamWriter;
};

} // namespace soul::cpp20::ast
