// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.file;

import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

File::File() : filePath(), content()
{
}

File::File(const std::string& filePath_, Node* content_) : filePath(filePath_), content(content_)
{
}

std::expected<bool, int> File::Write(Writer& writer)
{
    std::expected<bool, int> rv = writer.GetBinaryStreamWriter().Write(filePath);
    if (!rv) return rv;
    rv = writer.Write(content.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> File::Read(Reader& reader)
{
    auto rv = reader.GetBinaryStreamReader().ReadUtf8String();
    if (!rv)
    {
        return std::unexpected<int>(rv.error());
    }
    filePath = *rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    content.reset(*nrv);
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
