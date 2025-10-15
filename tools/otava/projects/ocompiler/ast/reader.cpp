// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.reader;

import otava.ast.node.map;

namespace otava::ast {

Reader::Reader(const std::string& fileName) :
    fileStream(new util::FileStream(fileName, util::OpenMode::binary | util::OpenMode::read)),
    bufferedStream(new util::BufferedStream(*fileStream)),
    binaryStreamReader(new util::BinaryStreamReader(*bufferedStream)),
    readerPtr(binaryStreamReader.get())
{
}

Reader::Reader(util::BinaryStreamReader* readerPtr_) : readerPtr(readerPtr_)
{
}

std::expected<soul::ast::SourcePos, int> Reader::ReadSourcePos()
{
    std::expected<std::uint32_t, int> lineRv = readerPtr->ReadULEB128UInt();
    if (!lineRv) return std::unexpected<int>(lineRv.error());
    std::uint32_t ln = *lineRv;
    int line = static_cast<int>(ln);
    if (line == 0) return std::expected<soul::ast::SourcePos, int>(soul::ast::SourcePos());
    std::expected<std::uint32_t, int> colRv = readerPtr->ReadULEB128UInt();
    if (!colRv) return std::unexpected<int>(colRv.error());
    std::uint32_t cl = *colRv;
    int col = static_cast<int>(cl);
    std::expected<std::uint32_t, int> fileRv = readerPtr->ReadULEB128UInt();
    if (!fileRv) return std::unexpected<int>(fileRv.error());
    std::uint32_t f = *fileRv;
    int file = static_cast<int>(f);
    return std::expected<soul::ast::SourcePos, int>(soul::ast::SourcePos(file, line, col));
}

std::expected<NodeKind, int> Reader::ReadNodeKind()
{
    std::expected<std::uint32_t, int> rv = readerPtr->ReadULEB128UInt();
    if (!rv) return std::unexpected<int>(rv.error());
    std::uint32_t kind = *rv;
    return static_cast<NodeKind>(static_cast<std::uint16_t>(kind));
}

std::expected<std::u32string, int> Reader::ReadStr()
{
    return readerPtr->ReadUtf32String();
}

std::expected<bool, int> Reader::ReadBool()
{
    return readerPtr->ReadBool();
}

std::expected<Node*, int> Reader::ReadNode()
{
    std::expected<NodeKind, int> kindRv = ReadNodeKind();
    if (!kindRv) return std::unexpected<int>(kindRv.error());
    NodeKind kind = *kindRv;
    if (kind == NodeKind::nullNode)
    {
        return nullptr;
    }
    else
    {
        std::expected<soul::ast::SourcePos, int> sourcePosRv = ReadSourcePos();
        if (!sourcePosRv) return std::unexpected<int>(sourcePosRv.error());
        soul::ast::SourcePos sourcePos = *sourcePosRv;
        std::expected<Node*, int> rv = CreateNode(kind, sourcePos);
        if (!rv) return rv;
        Node* node = *rv;
        node->SetId(-1);
        std::expected<bool, int> rrv = node->Read(*this);
        if (!rrv) return std::unexpected<int>(rrv.error());
        if (node->InternalId() == -1)
        {
            return std::unexpected<int>(util::AllocateError("otava.ast.Reader: node id not set"));
        }
        nodeMap->AddNode(node);
        return std::expected<Node*, int>(node);
    }
}

} // namespace otava::ast
