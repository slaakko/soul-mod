// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.qualifier;

import soul.cpp20.ast.visitor;

namespace soul::cpp20::ast {

ConstNode::ConstNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constNode, sourcePos_)
{
}

void ConstNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VolatileNode::VolatileNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::volatileNode, sourcePos_)
{
}

void VolatileNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LvalueRefNode::LvalueRefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lvalueRefNode, sourcePos_)
{
}

void LvalueRefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RvalueRefNode::RvalueRefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rvalueRefNode, sourcePos_)
{
}

void RvalueRefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PtrNode::PtrNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::ptrNode, sourcePos_)
{
}

void PtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CVQualifierSequenceNode::CVQualifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::cvQualifierSequenceNode, sourcePos_)
{
}

void CVQualifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::ast
