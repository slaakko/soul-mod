// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.overload.resolution;

import std.core;
import soul.ast.source.pos;

export namespace otava::symbols {

class BoundFunctionCallNode;
class BoundExpressionNode;
class Context;
class Scope;
class Exception;

enum class OverloadResolutionFlags : int32_t
{
    none = 0, dontInstantiate = 1 << 0, dontSearchArgumentScopes = 1 << 1
};

constexpr OverloadResolutionFlags operator|(OverloadResolutionFlags left, OverloadResolutionFlags right)
{
    return OverloadResolutionFlags(int32_t(left) | int32_t(right));
}

constexpr OverloadResolutionFlags operator&(OverloadResolutionFlags left, OverloadResolutionFlags right)
{
    return OverloadResolutionFlags(int32_t(left) & int32_t(right));
}

constexpr OverloadResolutionFlags operator~(OverloadResolutionFlags flags)
{
    return OverloadResolutionFlags(~int32_t(flags));
}

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex, OverloadResolutionFlags flags);

std::unique_ptr<BoundFunctionCallNode> ResolveOverload(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args, 
    const soul::ast::SourcePos& sourcePos, Context* context, Exception& ex);

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context, OverloadResolutionFlags flags);

std::unique_ptr<BoundFunctionCallNode> ResolveOverloadThrow(Scope* scope, const std::u32string& groupName, std::vector<std::unique_ptr<BoundExpressionNode>>& args,
    const soul::ast::SourcePos& sourcePos, Context* context);

} // namespace otava::symbols
