// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.qualifier;

import otava.ast.visitor;

namespace otava::ast {

ConstNode::ConstNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constNode, sourcePos_)
{
}

std::expected<Node*, int> ConstNode::Clone() const
{
    ConstNode* clone = new ConstNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ConstNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VolatileNode::VolatileNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::volatileNode, sourcePos_)
{
}

std::expected<Node*, int> VolatileNode::Clone() const
{
    VolatileNode* clone = new VolatileNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void VolatileNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LvalueRefNode::LvalueRefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lvalueRefNode, sourcePos_)
{
}

std::expected<Node*, int> LvalueRefNode::Clone() const
{
    LvalueRefNode* clone = new LvalueRefNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void LvalueRefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RvalueRefNode::RvalueRefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rvalueRefNode, sourcePos_)
{
}

std::expected<Node*, int> RvalueRefNode::Clone() const
{
    RvalueRefNode* clone = new RvalueRefNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void RvalueRefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PtrNode::PtrNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::ptrNode, sourcePos_)
{
}

std::expected<Node*, int> PtrNode::Clone() const
{
    PtrNode* clone = new PtrNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void PtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CVQualifierSequenceNode::CVQualifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::cvQualifierSequenceNode, sourcePos_)
{
}

std::expected<Node*, int> CVQualifierSequenceNode::Clone() const
{
    CVQualifierSequenceNode* clone = new CVQualifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void CVQualifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
