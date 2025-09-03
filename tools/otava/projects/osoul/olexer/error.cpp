// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.lexer.error;

import util;

namespace soul::lexer {

std::expected<std::string, int> MakeMessage(const std::string& msgClass, const std::string& msg, const soul::ast::SourcePos& sourcePos, FileMap& fileMap)
{
    std::string message;
    std::expected<std::u32string, int> fmrv = fileMap.GetFileLine(sourcePos.file, sourcePos.line);
    if (!fmrv) return std::unexpected<int>(fmrv.error());
    std::expected<std::string, int> rv = util::ToUtf8(std::move(*fmrv));
    if (!rv) return rv;
    message.append(msgClass).append(": ").append(msg).append(" in file '").append(fileMap.GetFilePath(sourcePos.file)).
        append("' line ").append(std::to_string(sourcePos.line));
    message.append(":\n").append(std::move(*rv)).append("\n").append(sourcePos.col - 1, ' ').append(1, '^');
    return std::expected<std::string, int>(std::move(message));
}

} // namespace soul::lexer
