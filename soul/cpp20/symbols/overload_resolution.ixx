// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.cpp20.symbols.overload.resolution;

import std.core;
import soul.ast.source.pos;

export namespace soul::cpp20::symbols {

class BoundFunctionCallNode;
class BoundExpressionNode;
class Context;
class Scope;

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace soul::cpp20::symbols
