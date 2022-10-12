// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.symbols.bound.tree.util;

import std.core;
import soul.ast.source.pos;
import util.uuid;

export namespace otava::symbols {

class Context;
class Emitter;
class BoundExpressionNode;
class TypeSymbol;

enum class OperationFlags : int32_t
{
    none = 0, addr = 1 << 0, deref = 1 << 1, defaultInit = 1 << 2, derefCount = 0xFF << 8
};

constexpr OperationFlags operator|(OperationFlags left, OperationFlags right)
{
    return OperationFlags(int32_t(left) | int32_t(right));
}

constexpr OperationFlags operator&(OperationFlags left, OperationFlags right)
{
    return OperationFlags(int32_t(left) & int32_t(right));
}

constexpr OperationFlags operator~(OperationFlags flags)
{
    return OperationFlags(~int32_t(flags));
}

constexpr uint8_t GetDerefCount(OperationFlags flags)
{
    return uint8_t(uint16_t(flags & OperationFlags::derefCount) >> 8);
}

constexpr OperationFlags SetDerefCount(OperationFlags flags, uint8_t n)
{
    return OperationFlags(flags | OperationFlags(uint16_t(n) << 8));
}

void Load(Emitter& emitter, BoundExpressionNode* arg, OperationFlags operationFlags, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
void* GetIrType(Emitter& emitter, TypeSymbol* type, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context);
util::uuid GetTypeId(TypeSymbol* type);

} // namespace otava::symbols
