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
    std::expected<bool, int> Write(const soul::ast::SourcePos& sourcePos);
    std::expected<bool, int> Write(NodeKind nodeKind);
    std::expected<bool, int> Write(const std::u32string& str);
    std::expected<bool, int> Write(bool value);
    std::expected<bool, int> Write(Node* node);
    inline bool Valid() const { return error == 0; }
    inline explicit operator bool() const { return Valid(); }
    inline int Error() const { return error; }
    inline void SetError(int error_) { error = error_; }
private:
    std::unique_ptr<util::FileStream> fileStream;
    std::unique_ptr<util::BufferedStream> bufferedStream;
    std::unique_ptr<util::BinaryStreamWriter> binaryStreamWriter;
    util::BinaryStreamWriter* writerPtr;
    int error;
};

} // namespace otava::ast
