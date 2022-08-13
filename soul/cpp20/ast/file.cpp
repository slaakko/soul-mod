// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.file;

import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

File::File() : filePath(), content()
{
}

File::File(const std::string& filePath_, Node* content_) : filePath(filePath_), content(content_)
{
}

void File::Write(Writer& writer)
{
    writer.GetBinaryStreamWriter().Write(filePath);
    writer.Write(content.get());
}

void File::Read(Reader& reader)
{
    filePath = reader.GetBinaryStreamReader().ReadUtf8String();
    content.reset(reader.ReadNode());
}

void Files::AddFile(File* file)
{
    files.push_back(std::unique_ptr<File>(file));
}

void Files::Write(Writer& writer)
{
    uint32_t n = files.size();
    writer.GetBinaryStreamWriter().WriteULEB128UInt(n);
    for (const auto& file : files)
    {
        file->Write(writer);
    }
}

void Files::Read(Reader& reader)
{
    uint32_t n = reader.GetBinaryStreamReader().ReadULEB128UInt();
    for (uint32_t i = 0; i < n; ++i)
    {
        File* file = new File();
        file->Read(reader);
        AddFile(file);
    }
}

} // namespace soul::cpp20::ast
