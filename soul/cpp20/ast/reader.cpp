// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.reader;

namespace soul::cpp20::ast {

Reader::Reader(const std::string& fileName) : fileStream(fileName, util::OpenMode::binary | util::OpenMode::read), bufferedStream(fileStream), binaryStreamReader(bufferedStream)
{
}

soul::ast::SourcePos Reader::ReadSourcePos()
{
    int line = binaryStreamReader.ReadULEB128UInt();
    if (line == 0) return soul::ast::SourcePos();
    int col = binaryStreamReader.ReadULEB128UInt();
    return soul::ast::SourcePos(-1, line, col);
}

NodeKind Reader::ReadNodeKind()
{
    uint32_t kind = binaryStreamReader.ReadULEB128UInt();
    return static_cast<NodeKind>(kind);
}

std::u32string Reader::ReadStr()
{
    return binaryStreamReader.ReadUtf32String();
}

bool Reader::ReadBool()
{
    return binaryStreamReader.ReadBool();
}

Node* Reader::ReadNode()
{
    NodeKind kind = ReadNodeKind();
    if (kind == NodeKind::nullNode)
    {
        return nullptr;
    }
    else
    {
        soul::ast::SourcePos sourcePos = ReadSourcePos();
        Node* node = CreateNode(kind, sourcePos);
        node->Read(*this);
        return node;
    }
}

} // namespace soul::cpp20::ast
