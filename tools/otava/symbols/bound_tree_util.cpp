// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.tree.util;

import otava.symbols.bound.node;

namespace otava::symbols {

void Load(Emitter& emitter, BoundExpressionNode* arg, OperationFlags operationFlags, const soul::ast::SourcePos& sourcePos, otava::symbols::Context* context)
{
    arg->Load(emitter, operationFlags, sourcePos, context);
}

} // namespace otava::symbols
