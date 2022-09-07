// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.ast.error;

import std.core;

export namespace soul::cpp20::ast {

void SetExceptionThrown();
bool ExceptionThrown();

} // namespace soul::cpp20::ast
