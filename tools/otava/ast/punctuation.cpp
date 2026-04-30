// =================================
// Copyright (c) 2026 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.punctuation;

import otava.ast.visitor;

namespace otava::ast {

SemicolonNode::SemicolonNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::semicolonNode, sourcePos_)
{
}

Node* SemicolonNode::Clone() const
{
    SemicolonNode* clone = new SemicolonNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void SemicolonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CommaNode::CommaNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::commaNode, sourcePos_)
{
}

Node* CommaNode::Clone() const
{
    CommaNode* clone = new CommaNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void CommaNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

QuestNode::QuestNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::questNode, sourcePos_)
{
}

Node* QuestNode::Clone() const
{
    QuestNode* clone = new QuestNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void QuestNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ColonNode::ColonNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::colonNode, sourcePos_)
{
}

Node* ColonNode::Clone() const
{
    ColonNode* clone = new ColonNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void ColonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EllipsisNode::EllipsisNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::ellipsisNode, sourcePos_)
{
}

Node* EllipsisNode::Clone() const
{
    EllipsisNode* clone = new EllipsisNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void EllipsisNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LParenNode::LParenNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::lparenNode, sourcePos_)
{
}

Node* LParenNode::Clone() const
{
    LParenNode* clone = new LParenNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void LParenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RParenNode::RParenNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::rparenNode, sourcePos_)
{
}

Node* RParenNode::Clone() const
{
    RParenNode* clone = new RParenNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void RParenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LBracketNode::LBracketNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::lbracketNode, sourcePos_)
{
}

Node* LBracketNode::Clone() const
{
    LBracketNode* clone = new LBracketNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void LBracketNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RBracketNode::RBracketNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::rbracketNode, sourcePos_)
{
}

Node* RBracketNode::Clone() const
{
    RBracketNode* clone = new RBracketNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void RBracketNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LBraceNode::LBraceNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::lbraceNode, sourcePos_)
{
}

Node* LBraceNode::Clone() const
{
    LBraceNode* clone = new LBraceNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void LBraceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RBraceNode::RBraceNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::rbraceNode, sourcePos_)
{
}

Node* RBraceNode::Clone() const
{
    RBraceNode* clone = new RBraceNode(GetSourcePos());
    clone->SetId(Id());
    return clone;
}

void RBraceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
