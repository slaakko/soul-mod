// =================================
// Copyright (c) 2023 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.error;

import std.core;

export namespace otava::ast {

void SetExceptionThrown();
bool ExceptionThrown();

} // namespace otava::ast
