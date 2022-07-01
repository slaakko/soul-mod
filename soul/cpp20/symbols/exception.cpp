// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.symbols.exception;

import soul.cpp20.symbols.context;

namespace soul::cpp20::symbols {

Exception::Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context) :
    std::runtime_error("error: " + message_ + " in file '" + context->FileName() + "' at line " + std::to_string(sourcePos.line))
{
}

} // namespace soul::cpp20::symbols
