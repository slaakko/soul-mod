// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.writer;

namespace otava::ast {

Writer::Writer(const std::string& fileName) : 
    fileStream(new util::FileStream(fileName, util::OpenMode::binary | util::OpenMode::write)),
    bufferedStream(new util::BufferedStream(*fileStream)), 
    binaryStreamWriter(new util::BinaryStreamWriter(*bufferedStream)),
    writerPtr(binaryStreamWriter.get())
{
}

Writer::Writer(util::BinaryStreamWriter* writerPtr_) : writerPtr(writerPtr_)
{
}

void Writer::Write(const soul::ast::SourcePos& sourcePos)
{
    if (sourcePos.IsValid())
    {
        writerPtr->WriteULEB128UInt(sourcePos.line);
        writerPtr->WriteULEB128UInt(sourcePos.col);
        writerPtr->WriteULEB128UInt(sourcePos.file);
    }
    else
    {
        writerPtr->WriteULEB128UInt(0);
    }
}

void Writer::Write(NodeKind nodeKind)
{
    writerPtr->WriteULEB128UInt(static_cast<std::uint32_t>(nodeKind));
}

void Writer::Write(const std::u32string& str)
{
    writerPtr->Write(str);
}

void Writer::Write(bool value)
{
    writerPtr->Write(value);
}

void Writer::Write(Node* node)
{
    if (!node)
    {
        Write(NodeKind::nullNode);
    }
    else
    {
        Write(node->Kind());
        Write(node->GetSourcePos());
        node->Write(*this);
    }
}

} // namespace otava::ast
