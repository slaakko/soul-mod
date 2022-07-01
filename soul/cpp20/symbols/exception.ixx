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

class Exception : public std::runtime_error
{
public:
    Exception(const std::string& message_, const soul::ast::SourcePos& sourcePos, soul::cpp20::symbols::Context* context);
};

} // namespace soul::cpp20::symbols
