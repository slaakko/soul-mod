// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.punctuation;

import otava.ast.visitor;

namespace otava::ast {

SemicolonNode::SemicolonNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::semicolonNode, sourcePos_)
{
}

std::expected<Node*, int> SemicolonNode::Clone() const
{
    SemicolonNode* clone = new SemicolonNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void SemicolonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CommaNode::CommaNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::commaNode, sourcePos_)
{
}

std::expected<Node*, int> CommaNode::Clone() const
{
    CommaNode* clone = new CommaNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void CommaNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

QuestNode::QuestNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::questNode, sourcePos_)
{
}

std::expected<Node*, int> QuestNode::Clone() const
{
    QuestNode* clone = new QuestNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void QuestNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ColonNode::ColonNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::colonNode, sourcePos_)
{
}

std::expected<Node*, int> ColonNode::Clone() const
{
    ColonNode* clone = new ColonNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ColonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EllipsisNode::EllipsisNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::ellipsisNode, sourcePos_)
{
}

std::expected<Node*, int> EllipsisNode::Clone() const
{
    EllipsisNode* clone = new EllipsisNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void EllipsisNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LParenNode::LParenNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lparenNode, sourcePos_)
{
}

std::expected<Node*, int> LParenNode::Clone() const
{
    LParenNode* clone = new LParenNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void LParenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RParenNode::RParenNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rparenNode, sourcePos_)
{
}

std::expected<Node*, int> RParenNode::Clone() const
{
    RParenNode* clone = new RParenNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void RParenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LBracketNode::LBracketNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lbracketNode, sourcePos_)
{
}

std::expected<Node*, int> LBracketNode::Clone() const
{
    LBracketNode* clone = new LBracketNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void LBracketNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RBracketNode::RBracketNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rbracketNode, sourcePos_)
{
}

std::expected<Node*, int> RBracketNode::Clone() const
{
    RBracketNode* clone = new RBracketNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void RBracketNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LBraceNode::LBraceNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lbraceNode, sourcePos_)
{
}

std::expected<Node*, int> LBraceNode::Clone() const
{
    LBraceNode* clone = new LBraceNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void LBraceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RBraceNode::RBraceNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rbraceNode, sourcePos_)
{
}

std::expected<Node*, int> RBraceNode::Clone() const
{
    RBraceNode* clone = new RBraceNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void RBraceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
