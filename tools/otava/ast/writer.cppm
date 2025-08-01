// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.writer;

import std;
import util;
import soul.ast.source.pos;
import otava.ast.node;

export namespace otava::ast {

class Writer
{
public:
    Writer(const std::string& fileName);
    Writer(util::BinaryStreamWriter* writerPtr_);
    inline util::BinaryStreamWriter& GetBinaryStreamWriter() { return *writerPtr; }
    void Write(const soul::ast::SourcePos& sourcePos);
    void Write(NodeKind nodeKind);
    void Write(const std::u32string& str);
    void Write(bool value);
    void Write(Node* node);
private:
    std::unique_ptr<util::FileStream> fileStream;
    std::unique_ptr<util::BufferedStream> bufferedStream;
    std::unique_ptr<util::BinaryStreamWriter> binaryStreamWriter;
    util::BinaryStreamWriter* writerPtr;
};

} // namespace otava::ast
