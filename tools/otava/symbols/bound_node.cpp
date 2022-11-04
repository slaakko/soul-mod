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

std::string BoundNodeKindStr(BoundNodeKind nodeKind)
{
    switch (nodeKind)
    {
        case BoundNodeKind::boundCompileUnitNode:
        {
            return "boundCompileUnitNode";
        }
        case BoundNodeKind::boundFunctionNode:
        {
            return "boundFunctionNode";
        }
        case BoundNodeKind::boundCompoundStatementNode:
        {
            return "boundCompoundStatementNode";
        }
        case BoundNodeKind::boundIfStatementNode:
        {
            return "boundIfStatementNode";
        }
        case BoundNodeKind::boundSwitchStatementNode:
        {
            return "boundSwitchStatementNode";
        }
        case BoundNodeKind::boundCaseStatementNode:
        {
            return "boundCaseStatementNode";
        }
        case BoundNodeKind::boundDefaultStatementNode:
        {
            return "boundDefaultStatementNode";
        }
        case BoundNodeKind::boundWhileStatementNode:
        {
            return "boundWhileStatementNode";
        }
        case BoundNodeKind::boundDoStatementNode:
        {
            return "boundDoStatementNode";
        }
        case BoundNodeKind::boundForStatementNode:
        {
            return "boundForStatementNode";
        }
        case BoundNodeKind::boundBreakStatementNode:
        {
            return "boundBreakStatementNode";
        }
        case BoundNodeKind::boundContinueStatementNode:
        {
            return "boundContinueStatementNode";
        }
        case BoundNodeKind::boundReturnStatementNode:
        {
            return "boundReturnStatementNode";
        }
        case BoundNodeKind::boundGotoStatementNode:
        {
            return "boundGotoStatementNode";
        }
        case BoundNodeKind::boundConstructionStatementNode:
        {
            return "boundConstructionStatementNode";
        }
        case BoundNodeKind::boundExpressionStatementNode:
        {
            return "boundExpressionStatementNode";
        }
        case BoundNodeKind::boundSequenceStatementNode:
        {
            return "boundSequenceStatementNode";
        }
        case BoundNodeKind::boundLiteralNode:
        {
            return "boundLiteralNode";
        }
        case BoundNodeKind::boundVariableNode:
        {
            return "boundVariableNode";
        }
        case BoundNodeKind::boundParameterNode:
        {
            return "boundParameterNode";
        }
        case BoundNodeKind::boundEnumConstantNode:
        {
            return "boundEnumConstantNode";
        }
        case BoundNodeKind::boundFunctionGroupNode:
        {
            return "boundFunctionGroupNode";
        }
        case BoundNodeKind::boundTypeNode:
        {
            return "boundTypeNode";
        }
        case BoundNodeKind::boundMemberExprNode:
        {
            return "boundMemberExprNode";
        }
        case BoundNodeKind::boundFunctionCallNode:
        {
            return "boundFunctionCallNode";
        }
        case BoundNodeKind::boundDisjunctionNode:
        {
            return "boundDisjunctionNode";
        }
        case BoundNodeKind::boundConjunctionNode:
        {
            return "boundConjunctionNode";
        }
        case BoundNodeKind::boundConversionNode:
        {
            return "boundConversionNode";
        }
        case BoundNodeKind::boundAddressOfNode:
        {
            return "boundAddressOfNode";
        }
        case BoundNodeKind::boundDereferenceNode:
        {
            return "boundDereferenceNode";
        }
    }
    return "<unknown bound node>";
}

BoundNode::BoundNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_) : kind(kind_), sourcePos(sourcePos_)
{
}

BoundNode::~BoundNode()
{
}

BoundExpressionNode::BoundExpressionNode(BoundNodeKind kind_, const soul::ast::SourcePos& sourcePos_, TypeSymbol* type_) : 
    BoundNode(kind_, sourcePos_), flags(BoundExpressionFlags::none), type(type_)
{
}

void BoundExpressionNode::Load(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("LOAD not implemented for " + BoundNodeKindStr(Kind()), sourcePos, context);
}

void BoundExpressionNode::Store(Emitter& emitter, OperationFlags flags, const soul::ast::SourcePos& sourcePos, Context* context)
{
    ThrowException("STORE not implemented for " + BoundNodeKindStr(Kind()), sourcePos, context);
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

bool BoundExpressionNode::GetFlag(BoundExpressionFlags flag) const
{
    return (flags & flag) != BoundExpressionFlags::none;
}

void BoundExpressionNode::SetFlag(BoundExpressionFlags flag)
{
    flags = flags | flag;
}

} // namespace otava::symbols
