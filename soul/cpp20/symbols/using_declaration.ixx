// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.using_declaration;

import std.core;
import soul.cpp20.ast;

export namespace soul::cpp20::symbols {

class Context;

void AddUsingDeclaration(soul::cpp20::ast::Node* node, Context* context);

} // namespace soul::cpp20::symbols
