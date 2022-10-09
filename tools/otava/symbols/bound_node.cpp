// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.symbols.bound.node;

import otava.symbols.bound.tree;
import otava.symbols.exception;
import otava.symbols.type.symbol;
import otava.symbols.type.resolver;

namespace otava::symbols {

BoundNode::BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) : kind(kind_), sourcePos(sourcePos_)
{
}

BoundNode::~BoundNode()
{
}

BoundExpressionNode::BoundExpressionNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) : BoundNode(kind_, sourcePos_), type(type_)
{
}

void BoundExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("LOAD not implemented", sourcePos, context);
}

void BoundExpressionNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("STORE not implemented", sourcePos, context);
}

Scope* BoundExpressionNode::GetMemberScope(otava::ast::Node* op, const soul::ast::SourcePos& sourcePos, Context* context) const
{
    if (type)
    {
        if (op->IsDotNode())
        {
            TypeSymbol* baseType = ResolveFwdDeclaredType(type->DirectType()->GetBaseType(), sourcePos, context);
            return baseType->GetScope();
        }
        else if (op->IsArrowNode() && type->IsPointerType())
        {
            TypeSymbol* baseType = ResolveFwdDeclaredType(type->DirectType()->RemovePointer()->GetBaseType(), sourcePos, context);
            return baseType->GetScope();
        }
    }
    return nullptr;
}

} // namespace otava::symbols
