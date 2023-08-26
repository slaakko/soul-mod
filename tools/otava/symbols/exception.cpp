// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.exception;

import otava.symbols.context;
import soul.lexer;
import util.unicode;

namespace otava::symbols {

bool exception_thrown = false;

bool ExceptionThrown()
{
    return exception_thrown;
}

void SetExceptionThrown()
{
    exception_thrown = true;
}

std::string ErrorLine(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    if (sourcePos.IsValid())
    {
        soul::lexer::FileMap* fileMap = context->GetFileMap();
        if (fileMap)
        {
            std::string errorLine = util::ToUtf8(fileMap->GetFileLine(sourcePos.file, sourcePos.line));
            std::string caretLine = std::string(sourcePos.col - 1, ' ') + "^";
            return ":\n" + errorLine + "\n" + caretLine;
        }
    }
    return std::string();
}

std::string SourceFilePath(const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
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

std::string ReferenceInfo(const soul::ast::SourcePos& refSourcePos, otava::symbols::Context* context)
{
    if (refSourcePos.IsValid())
    {
        std::string message = "\nSee reference file " + SourceFilePath(refSourcePos, context) + ", line " + std::to_string(refSourcePos.line) + ErrorLine(refSourcePos, context);
        return message;
    }
    return std::string();
}

Exception::Exception() : std::runtime_error("empty")
{
}

Exception::Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    Exception(message_, sourcePos, soul::ast::SourcePos(), context)
{
}

Exception::Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, otava::symbols::Context* context) : 
    Exception("error: ", message_, sourcePos, refSourcePos, context)
{
}

Exception::Exception(const std::string& title, const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    Exception(title, message_, sourcePos, soul::ast::SourcePos(), context)
{
}

Exception::Exception(const std::string& title_, const std::string& message_, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, 
    otava::symbols::Context* context) :
    std::runtime_error(title_ + message_ + ", file '" + SourceFilePath(sourcePos, context) +
        "', line " + std::to_string(sourcePos.line) + ErrorLine(sourcePos, context) + ReferenceInfo(refSourcePos, context))
{
}

[[noreturn]]
void ThrowException(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    ThrowException(message, sourcePos, soul::ast::SourcePos(), context);
}

[[noreturn]]
void ThrowException(const std::string& message, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, otava::symbols::Context* context)
{
    exception_thrown = true;
    throw Exception(message, sourcePos, refSourcePos, context);
}

[[noreturn]]
void ThrowException(const Exception& ex)
{
    exception_thrown = true;
    throw ex;
}

void PrintWarning(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    PrintWarning(message, sourcePos, soul::ast::SourcePos(), context);
}

void PrintWarning(const std::string& message, const soul::ast::SourcePos& sourcePos, const soul::ast::SourcePos& refSourcePos, otava::symbols::Context* context)
{
    Exception exception("warning: ", message, sourcePos, refSourcePos, context);
    std::cout << exception.what() << std::endl;
}

} // namespace otava::symbols
