// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.scope.resolver;

import std.core;
import soul.cpp20.ast;

export namespace soul::cpp20::symbols {

class Scope;
class Context;

Scope* ResolveScope(soul::cpp20::ast::Node* nnsNode, Context* context);

void BeginScope(soul::cpp20::ast::Node* nnsNode, Context* context);
void EndScope(Context* context);

} // namespace soul::cpp20::symbols
