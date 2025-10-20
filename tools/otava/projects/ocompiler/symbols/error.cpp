// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.error;

import otava.symbols.context;
import util;

namespace otava::symbols {

std::expected<std::string, int> ErrorLine(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (sourcePos.IsValid())
    {
        soul::lexer::FileMap* fileMap = context->GetFileMap();
        if (fileMap)
        {
            std::expected<std::u32string, int> frv = fileMap->GetFileLine(sourcePos.file, sourcePos.line);
            if (!frv) return std::unexpected<int>(frv.error());
            std::expected<std::string, int> rv = util::ToUtf8(*frv);
            if (!rv) return std::unexpected<int>(rv.error());
            std::string errorLine = *rv;
            std::string caretLine = std::string(sourcePos.col - 1, ' ') + "^";
            return std::expected<std::string, int>(":\n" + errorLine + "\n" + caretLine);
        }
    }
    return std::expected<std::string, int>(std::string());
}

std::string SourceFilePath(const soul::ast::SourcePos& sourcePos, Context* context)
{
    if (sourcePos.IsValid())
    {
        soul::lexer::FileMap* fileMap = context->GetFileMap();
        if (fileMap)
        {
            return fileMap->GetFilePath(sourcePos.file);
        }
    }
    return std::string();
}

std::expected<std::string, int> ReferenceInfo(const soul::ast::SourcePos& refSourcePos, Context* context)
{
    if (refSourcePos.IsValid())
    {
        std::expected<std::string, int> rv = ErrorLine(refSourcePos, context);
        if (!rv) return std::unexpected<int>(rv.error());
        std::string errorLine = *rv;
        std::string message = "\nSee reference file " + SourceFilePath(refSourcePos, context) + ", line " + std::to_string(refSourcePos.line) + errorLine;
        return std::expected<std::string, int>(message);
    }
    return std::string();
}

std::unexpected<int> Error(const std::string& message, const soul::ast::SourcePos& sourcePos, Context* context)
{
    return Error(message, sourcePos, soul::ast::SourcePos(), context);
}

std::unexpected<int> Error(const std::string& message, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, Context* context)
{
    std::expected<std::string, int> rv = ErrorLine(sourcePos, context);
    if (!rv) return std::unexpected<int>(rv.error());
    std::string errorLine = *rv;
    std::expected<std::string, int> rrv = ReferenceInfo(refSourcePos, context);
    if (!rrv) return std::unexpected<int>(rrv.error());
    std::string referenceInfo = *rrv;
    std::string errorMessage = "error: " + message + ", file '" + SourceFilePath(sourcePos, context) + "', line " + std::to_string(sourcePos.line) +
        errorLine + referenceInfo;
    return std::unexpected<int>(util::AllocateError(errorMessage));
}

} // namespace otava::symbols

