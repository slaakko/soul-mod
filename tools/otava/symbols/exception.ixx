// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.exception;

import std.core;
import otava.symbols.context;
import soul.ast.source.pos;

export namespace otava::symbols {

class Context;

bool ExceptionThrown();
void SetExceptionThrown();

class Exception : public std::runtime_error
{
public:
    Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
    Exception(const std::string& title, const std::string& message_, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
};

[[noreturn]]
void ThrowException(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);

void PrintWarning(const std::string& message, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);

} // namespace otava::symbols
