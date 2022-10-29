// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.exception;

import otava.symbols.context;
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
    soul::lexer::FileMap* fileMap = context->GetFileMap();
    if (fileMap)
    {
        std::string errorLine = util::ToUtf8(fileMap->GetFileLine(sourcePos.file, sourcePos.line));
        std::string caretLine = std::string(sourcePos.col - 1, ' ') + "^";
        return ":\n" + errorLine + "\n" + caretLine;
    }
    return std::string();
}

Exception::Exception() : std::runtime_error("empty")
{
}

Exception::Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) : Exception("error: ", message_, sourcePos, context)
{
}

Exception::Exception(const std::string& title_, const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    std::runtime_error(title_ + message_ + " in file '" + context->FileName() + "' at line " + std::to_string(sourcePos.line) + ErrorLine(sourcePos, context))
{
}

void ThrowException(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    exception_thrown = true;
    throw Exception(message, sourcePos, context);
}

void ThrowException(const Exception& ex)
{
    exception_thrown = true;
    throw ex;
}

void PrintWarning(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    Exception exception("warning: ", message, sourcePos, context);
    std::cout << exception.what() << std::endl;
}

} // namespace otava::symbols
