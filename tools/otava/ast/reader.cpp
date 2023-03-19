// =================================
// Copyright (c) 2022 Seppo Laakko
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

soul::ast::SourcePos Reader::ReadSourcePos()
{
    int line = readerPtr->ReadULEB128UInt();
    if (line == 0) return soul::ast::SourcePos();
    int col = readerPtr->ReadULEB128UInt();
    int file = readerPtr->ReadULEB128UInt();
    return soul::ast::SourcePos(file, line, col);
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
            throw std::runtime_error("otava.ast.Reader: node id not set");
        }
        nodeMap->AddNode(node);
        return node;
    }
}

} // namespace otava::ast
