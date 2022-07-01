// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.punctuation;

import soul.cpp20.ast.visitor;

namespace soul::cpp20::ast {

SemicolonNode::SemicolonNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::semicolonNode, sourcePos_)
{
}

void SemicolonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CommaNode::CommaNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::commaNode, sourcePos_)
{
}

void CommaNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

QuestNode::QuestNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::questNode, sourcePos_)
{
}

void QuestNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ColonNode::ColonNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::colonNode, sourcePos_)
{
}

void ColonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EllipsisNode::EllipsisNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::ellipsisNode, sourcePos_)
{
}

void EllipsisNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LParenNode::LParenNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lparenNode, sourcePos_)
{
}

void LParenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RParenNode::RParenNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rparenNode, sourcePos_)
{
}

void RParenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LBracketNode::LBracketNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lbracketNode, sourcePos_)
{
}

void LBracketNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RBracketNode::RBracketNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rbracketNode, sourcePos_)
{
}

void RBracketNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LBraceNode::LBraceNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lbraceNode, sourcePos_)
{
}

void LBraceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

RBraceNode::RBraceNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::rbraceNode, sourcePos_)
{
}

void RBraceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::ast
