// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.intermediate.error;

import soul.ast.span;
import std;

export namespace otava::intermediate {

namespace error {}

class IntermediateError : public std::runtime_error
{
public:
    IntermediateError(const std::string& message_);
    inline const std::string& Message() const { return message; }
private:
    std::string message;
};

class Context;

bool ExceptionThrown();
[[noreturn]] void Error(const std::string& message, const soul::ast::Span& span, Context* context);
[[noreturn]] void Error(const std::string& message, const soul::ast::Span& span, Context* context, const soul::ast::Span& refSpan);
void Warning(const std::string& message, const soul::ast::Span& span, Context* context);

} // otava::intermediate
