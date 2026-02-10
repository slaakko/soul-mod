
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
    writerPtr(binaryStreamWriter.get()), error(0)
{
    if (!*fileStream)
    {
        SetError(fileStream->Error());
        return;
    }
}

Writer::Writer(util::BinaryStreamWriter* writerPtr_) : writerPtr(writerPtr_), error(0)
{
}

std::expected<bool, int> Writer::Write(const soul::ast::SourcePos& sourcePos)
{
    if (sourcePos.IsValid())
    {
        std::expected<bool, int> rv = writerPtr->WriteULEB128UInt(sourcePos.line);
        if (!rv) return rv;
        rv = writerPtr->WriteULEB128UInt(sourcePos.col);
        if (!rv) return rv;
        rv = writerPtr->WriteULEB128UInt(sourcePos.file);
        if (!rv) return rv;
    }
    else
    {
        std::expected<bool, int> rv = writerPtr->WriteULEB128UInt(0);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

std::expected<bool, int> Writer::Write(NodeKind nodeKind)
{
    return writerPtr->WriteULEB128UInt(static_cast<std::uint32_t>(static_cast<std::uint16_t>(nodeKind)));
}

std::expected<bool, int> Writer::Write(const std::u32string& str)
{
    return writerPtr->Write(str);
}

std::expected<bool, int> Writer::Write(bool value)
{
    return writerPtr->Write(value);
}

std::expected<bool, int> Writer::Write(Node* node)
{
    if (!node)
    {
        return Write(NodeKind::nullNode);
    }
    else
    {
        std::expected<bool, int> rv = Write(node->Kind());
        if (!rv) return rv;
        rv = Write(node->GetSourcePos());
        if (!rv) return rv;
        rv = node->Write(*this);
        if (!rv) return rv;
    }
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
