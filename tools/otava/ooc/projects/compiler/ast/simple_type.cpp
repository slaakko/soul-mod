module otava.ast.simple.type;

import otava.ast.visitor;

namespace otava::ast {

CharNode::CharNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::charNode, span_)
{
}

Node* CharNode::Clone() const
{
    CharNode* clone = new CharNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void CharNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char8Node::Char8Node(const soul::ast::Span& span_) noexcept : Node(NodeKind::char8Node, span_)
{
}

Node* Char8Node::Clone() const
{
    Char8Node* clone = new Char8Node(GetSpan());
    clone->SetId(Id());
    return clone;
}

void Char8Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char16Node::Char16Node(const soul::ast::Span& span_) noexcept : Node(NodeKind::char16Node, span_)
{
}

Node* Char16Node::Clone() const
{
    Char16Node* clone = new Char16Node(GetSpan());
    clone->SetId(Id());
    return clone;
}

void Char16Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

Char32Node::Char32Node(const soul::ast::Span& span_) noexcept : Node(NodeKind::char32Node, span_)
{
}

Node* Char32Node::Clone() const
{
    Char32Node* clone = new Char32Node(GetSpan());
    clone->SetId(Id());
    return clone;
}

void Char32Node::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

WCharNode::WCharNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::wcharNode, span_)
{
}

Node* WCharNode::Clone() const
{
    WCharNode* clone = new WCharNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void WCharNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BoolNode::BoolNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::boolNode, span_)
{
}

Node* BoolNode::Clone() const
{
    BoolNode* clone = new BoolNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void BoolNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShortNode::ShortNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::shortNode, span_)
{
}

Node* ShortNode::Clone() const
{
    ShortNode* clone = new ShortNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void ShortNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IntNode::IntNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::intNode, span_)
{
}

Node* IntNode::Clone() const
{
    IntNode* clone = new IntNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void IntNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LongNode::LongNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::longNode, span_)
{
}

Node* LongNode::Clone() const
{
    LongNode* clone = new LongNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void LongNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SignedNode::SignedNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::signedNode, span_)
{
}

Node* SignedNode::Clone() const
{
    SignedNode* clone = new SignedNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void SignedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UnsignedNode::UnsignedNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::unsignedNode, span_)
{
}

Node* UnsignedNode::Clone() const
{
    UnsignedNode* clone = new UnsignedNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void UnsignedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FloatNode::FloatNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::floatNode, span_)
{
}

Node* FloatNode::Clone() const
{
    FloatNode* clone = new FloatNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void FloatNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DoubleNode::DoubleNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::doubleNode, span_)
{
}

Node* DoubleNode::Clone() const
{
    DoubleNode* clone = new DoubleNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void DoubleNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VoidNode::VoidNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::voidNode, span_)
{
}

Node* VoidNode::Clone() const
{
    VoidNode* clone = new VoidNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void VoidNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
