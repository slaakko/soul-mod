// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.exception;

import std.core;
import soul.cpp20.symbols.context;
import soul.ast.source.pos;

export namespace soul::cpp20::symbols {

class Context;

bool ExceptionThrown();

class Exception : public std::runtime_error
{
public:
    Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context);
    Exception(const std::string& title, const std::string& message_, const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context);
};

[[noreturn]]
void ThrowException(const std::string& message, const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context);

void PrintWarning(const std::string& message, const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context);

} // namespace soul::cpp20::symbols
