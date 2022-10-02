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

Node* ConstNode::Clone() const
{
    ConstNode* clone = new ConstNode(GetSourcePos());
    return clone;
}

void ConstNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VolatileNode::VolatileNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::volatileNode, sourcePos_)
{
}

Node* VolatileNode::Clone() const
{
    VolatileNode* clone = new VolatileNode(GetSourcePos());
    return clone;
}

void VolatileNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LvalueRefNode::LvalueRefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lvalueRefNode, sourcePos_)
{
}

Node* LvalueRefNode::Clone() const
{
    LvalueRefNode* clone = new LvalueRefNode(GetSourcePos());
    return clone;
}

void LvalueRefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RvalueRefNode::RvalueRefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rvalueRefNode, sourcePos_)
{
}

Node* RvalueRefNode::Clone() const
{
    RvalueRefNode* clone = new RvalueRefNode(GetSourcePos());
    return clone;
}

void RvalueRefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PtrNode::PtrNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::ptrNode, sourcePos_)
{
}

Node* PtrNode::Clone() const
{
    PtrNode* clone = new PtrNode(GetSourcePos());
    return clone;
}

void PtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CVQualifierSequenceNode::CVQualifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::cvQualifierSequenceNode, sourcePos_)
{
}

Node* CVQualifierSequenceNode::Clone() const
{
    CVQualifierSequenceNode* clone = new CVQualifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void CVQualifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::ast
