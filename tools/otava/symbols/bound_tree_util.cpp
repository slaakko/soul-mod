// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.tree.util;

import otava.symbols.bound.node;
import otava.symbols.type.symbol;

namespace otava::symbols {

void Load(Emitter& emitter, BoundExpressionNode* arg, OperationFlags operationFlags, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    arg->Load(emitter, operationFlags, sourcePos, context);
}

void* GetIrType(Emitter& emitter, TypeSymbol* type, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    return type->IrType(emitter, sourcePos, context);
}

util::uuid GetTypeId(TypeSymbol* type)
{
    return type->Id();
}

} // namespace otava::symbols
