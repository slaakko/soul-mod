// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

Writer::Writer(const std::string& fileName) : fileStream(fileName, util::OpenMode::binary | util::OpenMode::write), bufferedStream(fileStream), binaryStreamWriter(bufferedStream)
{
}

void Writer::Write(const soul::ast::SourcePos& sourcePos)
{
    if (sourcePos.IsValid())
    {
        binaryStreamWriter.WriteULEB128UInt(sourcePos.line);
        binaryStreamWriter.WriteULEB128UInt(sourcePos.col);
    }
    else
    {
        binaryStreamWriter.WriteULEB128UInt(0);
    }
}

void Writer::Write(NodeKind nodeKind)
{
    binaryStreamWriter.WriteULEB128UInt(static_cast<uint32_t>(nodeKind));
}

void Writer::Write(const std::u32string& str)
{
    binaryStreamWriter.Write(str);
}

void Writer::Write(bool value)
{
    binaryStreamWriter.Write(value);
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

} // namespace soul::cpp20::ast
