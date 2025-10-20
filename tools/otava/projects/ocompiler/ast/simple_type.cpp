// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.simple.type;

import otava.ast.visitor;

namespace otava::ast {

CharNode::CharNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::charNode, sourcePos_)
{
}

std::expected<Node*, int> CharNode::Clone() const
{
    CharNode* clone = new CharNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void CharNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char8Node::Char8Node(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::char8Node, sourcePos_)
{
}

std::expected<Node*, int> Char8Node::Clone() const
{
    Char8Node* clone = new Char8Node(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void Char8Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char16Node::Char16Node(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::char16Node, sourcePos_)
{
}

std::expected<Node*, int> Char16Node::Clone() const
{
    Char16Node* clone = new Char16Node(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void Char16Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char32Node::Char32Node(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::char32Node, sourcePos_)
{
}

std::expected<Node*, int> Char32Node::Clone() const
{
    Char32Node* clone = new Char32Node(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void Char32Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

WCharNode::WCharNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::wcharNode, sourcePos_)
{
}

std::expected<Node*, int> WCharNode::Clone() const
{
    WCharNode* clone = new WCharNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void WCharNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BoolNode::BoolNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::boolNode, sourcePos_)
{
}

std::expected<Node*, int> BoolNode::Clone() const
{
    BoolNode* clone = new BoolNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void BoolNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShortNode::ShortNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shortNode, sourcePos_)
{
}

std::expected<Node*, int> ShortNode::Clone() const
{
    ShortNode* clone = new ShortNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ShortNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IntNode::IntNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::intNode, sourcePos_)
{
}

std::expected<Node*, int> IntNode::Clone() const
{
    IntNode* clone = new IntNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void IntNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LongNode::LongNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::longNode, sourcePos_)
{
}

std::expected<Node*, int> LongNode::Clone() const
{
    LongNode* clone = new LongNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void LongNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SignedNode::SignedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::signedNode, sourcePos_)
{
}

std::expected<Node*, int> SignedNode::Clone() const
{
    SignedNode* clone = new SignedNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void SignedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UnsignedNode::UnsignedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::unsignedNode, sourcePos_)
{
}

std::expected<Node*, int> UnsignedNode::Clone() const
{
    UnsignedNode* clone = new UnsignedNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void UnsignedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FloatNode::FloatNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::floatNode, sourcePos_)
{
}

std::expected<Node*, int> FloatNode::Clone() const
{
    FloatNode* clone = new FloatNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void FloatNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DoubleNode::DoubleNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::doubleNode, sourcePos_)
{
}

std::expected<Node*, int> DoubleNode::Clone() const
{
    DoubleNode* clone = new DoubleNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DoubleNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VoidNode::VoidNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::voidNode, sourcePos_)
{
}

std::expected<Node*, int> VoidNode::Clone() const
{
    VoidNode* clone = new VoidNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void VoidNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
