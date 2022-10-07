// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.tree.util;

import std.core;
import soul.ast.source.pos;

export namespace otava::symbols {

class Context;
class Emitter;
class BoundExpressionNode;

enum class OperationFlags : int32_t
{
    none = 0, addr = 1 << 0, deref = 1 << 1, derefCount = 0xFF << 8
};

void Load(Emitter& emitter, BoundExpressionNode* arg, OperationFlags operationFlags, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);

} // namespace otava::symbols
