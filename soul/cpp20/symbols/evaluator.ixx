// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.evaluator;

import std.core;
import soul.cpp20.ast.node;

export namespace soul::cpp20::symbols {

class Value;
class Context;

Value* Evaluate(soul::cpp20::ast::Node* node, Context* context);

} // namespace soul::cpp20::symbols
