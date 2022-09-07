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

} // namespace soul::cpp20::ast
