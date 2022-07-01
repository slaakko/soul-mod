// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.simple.type;

import soul.cpp20.ast.visitor;

namespace soul::cpp20::ast {

CharNode::CharNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::charNode, sourcePos_)
{
}

void CharNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char8Node::Char8Node(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::char8Node, sourcePos_)
{
}

void Char8Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char16Node::Char16Node(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::char16Node, sourcePos_)
{
}

void Char16Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char32Node::Char32Node(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::char32Node, sourcePos_)
{
}

void Char32Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

WCharNode::WCharNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::wcharNode, sourcePos_)
{
}

void WCharNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BoolNode::BoolNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::boolNode, sourcePos_)
{
}

void BoolNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShortNode::ShortNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shortNode, sourcePos_)
{
}

void ShortNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IntNode::IntNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::intNode, sourcePos_)
{
}

void IntNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LongNode::LongNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::longNode, sourcePos_)
{
}

void LongNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SignedNode::SignedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::signedNode, sourcePos_)
{
}

void SignedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UnsignedNode::UnsignedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::unsignedNode, sourcePos_)
{
}

void UnsignedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FloatNode::FloatNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::floatNode, sourcePos_)
{
}

void FloatNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DoubleNode::DoubleNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::doubleNode, sourcePos_)
{
}

void DoubleNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VoidNode::VoidNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::voidNode, sourcePos_)
{
}

void VoidNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::ast
