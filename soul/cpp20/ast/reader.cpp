// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.reader;

namespace soul::cpp20::ast {

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

soul::ast::SourcePos Reader::ReadSourcePos()
{
    int line = readerPtr->ReadULEB128UInt();
    if (line == 0) return soul::ast::SourcePos();
    int col = readerPtr->ReadULEB128UInt();
    return soul::ast::SourcePos(-1, line, col);
}

NodeKind Reader::ReadNodeKind()
{
    uint32_t kind = readerPtr->ReadULEB128UInt();
    return static_cast<NodeKind>(kind);
}

std::u32string Reader::ReadStr()
{
    return readerPtr->ReadUtf32String();
}

bool Reader::ReadBool()
{
    return readerPtr->ReadBool();
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
        node->SetId(-1);
        node->Read(*this);
        if (node->Id() == -1)
        {
            throw std::runtime_error("soul.cpp20.ast.Reader: node id not set");
        }
        nodeMap[node->Id()] = node;
        return node;
    }
}

Node* Reader::GetNode(int32_t nodeId) const
{
    auto it = nodeMap.find(nodeId);
    if (it != nodeMap.cend())
    {
        return it->second;
    }
    else
    {
        throw std::runtime_error("soul.cpp20.ast.Reader: node id " + std::to_string(nodeId) + " not found");
    }
}

} // namespace soul::cpp20::ast
