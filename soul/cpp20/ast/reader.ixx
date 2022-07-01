// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.reader;

import std.core;
import util;
import soul.ast.source.pos;
import soul.cpp20.ast.node;

export namespace soul::cpp20::ast {

class Reader
{
public:
    Reader(const std::string& fileName);
    util::BinaryStreamReader& GetBinaryStreamReader() { return binaryStreamReader; }
    soul::ast::SourcePos ReadSourcePos();
    NodeKind ReadNodeKind();
    std::u32string ReadStr();
    bool ReadBool();
    Node* ReadNode();
private:
    util::FileStream fileStream;
    util::BufferedStream bufferedStream;
    util::BinaryStreamReader binaryStreamReader;
};

} // namespace soul::cpp20::ast
