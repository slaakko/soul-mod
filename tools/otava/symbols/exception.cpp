// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.exception;

import otava.symbols.context;

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

Exception::Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) : Exception("error: ", message_, sourcePos, context)
{
}

Exception::Exception(const std::string& title_, const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context) :
    std::runtime_error(title_ + message_ + " in file '" + context->FileName() + "' at line " + std::to_string(sourcePos.line))
{
}

void ThrowException(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    exception_thrown = true;
    throw Exception(message, sourcePos, context);
}

void PrintWarning(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    Exception exception("warning: ", message, sourcePos, context);
    std::cout << exception.what() << std::endl;
}

} // namespace otava::symbols
