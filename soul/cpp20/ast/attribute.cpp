// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.attribute;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

AttributeSpecifierSequenceNode::AttributeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::attributeSpecifierSequenceNode, sourcePos_)
{
}

void AttributeSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AttributeSpecifierNode::AttributeSpecifierNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::attributeSpecifierNode, sourcePos_)
{
}

void AttributeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AttributeSpecifierNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(usingPrefix.get());
    writer.Write(lbPos1);
    writer.Write(lbPos2);
    writer.Write(rbPos1);
    writer.Write(rbPos2);
}

void AttributeSpecifierNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    usingPrefix.reset(reader.ReadNode());
    lbPos1 = reader.ReadSourcePos();
    lbPos2 = reader.ReadSourcePos();
    rbPos1 = reader.ReadSourcePos();
    rbPos2 = reader.ReadSourcePos();
}

void AttributeSpecifierNode::SetBracketPositions(const soul::ast::SourcePos& lbPos1_, const soul::ast::SourcePos& lbPos2_, 
    const soul::ast::SourcePos& rbPos1_, const soul::ast::SourcePos& rbPos2_)
{
    lbPos1 = lbPos1_;
    lbPos2 = lbPos2_;
    rbPos1 = rbPos1_;
    rbPos2 = rbPos2_;
}

AttributeUsingPrefixNode::AttributeUsingPrefixNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::attributeUsingPrefixNode, sourcePos_, nullptr)
{
}

AttributeUsingPrefixNode::AttributeUsingPrefixNode(const soul::ast::SourcePos& sourcePos_, Node* atttributeNamespace_, const soul::ast::SourcePos& colonPos_) :
    UnaryNode(NodeKind::attributeUsingPrefixNode, sourcePos_, atttributeNamespace_), colonPos(colonPos_)
{
}

void AttributeUsingPrefixNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AttributeUsingPrefixNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(colonPos);
}

void AttributeUsingPrefixNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    colonPos = reader.ReadSourcePos();
}

AttributeNode::AttributeNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::attrbuteNode, sourcePos_)
{
}

AttributeNode::AttributeNode(const soul::ast::SourcePos& sourcePos_, Node* attributeToken_, Node* attributeArgs_) :
    CompoundNode(NodeKind::attrbuteNode, sourcePos_), attributeToken(attributeToken_), attributeArgs(attributeArgs_)
{
}

void AttributeNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AttributeNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributeToken.get());
    writer.Write(attributeArgs.get());
}

void AttributeNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    attributeToken.reset(reader.ReadNode());
    attributeArgs.reset(reader.ReadNode());
}

AttributeScopedTokenNode::AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::attributeScopedTokenNode, sourcePos_)
{
}

AttributeScopedTokenNode::AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_, Node* ns_, Node* colonColon_, Node* identifier_) :
    CompoundNode(NodeKind::attributeScopedTokenNode, sourcePos_), ns(ns_), colonColon(colonColon_), identifier(identifier_)
{
}

void AttributeScopedTokenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AttributeScopedTokenNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(ns.get());
    writer.Write(colonColon.get());
    writer.Write(identifier.get());
}

void AttributeScopedTokenNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    ns.reset(reader.ReadNode());
    colonColon.reset(reader.ReadNode());
    identifier.reset(reader.ReadNode());
}

AttributeArgumentsNode::AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::attributeArgumentsNode, sourcePos_)
{
}

AttributeArgumentsNode::AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_, Node* balancedTokenSequence_, 
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::attributeArgumentsNode, sourcePos_), balancedTokenSequence(balancedTokenSequence_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void AttributeArgumentsNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AttributeArgumentsNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(balancedTokenSequence.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void AttributeArgumentsNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    balancedTokenSequence.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

BalancedTokenSequenceNode::BalancedTokenSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::balancedTokenSequenceNode, sourcePos_)
{
}

void BalancedTokenSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TokenNode::TokenNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::tokenNode, sourcePos_)
{
}

TokenNode::TokenNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_) : CompoundNode(NodeKind::tokenNode, sourcePos_), str(str_)
{
}

void TokenNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TokenNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(str);
}

void TokenNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    str = reader.ReadStr();
}

AlignmentSpecifierNode::AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::alignmentSpecifierNode, sourcePos_)
{
}

AlignmentSpecifierNode::AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* alignment_, Node* ellipsis_, 
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::alignmentSpecifierNode, sourcePos_), alignment(alignment_), ellipsis(ellipsis_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void AlignmentSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AlignmentSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(alignment.get());
    writer.Write(ellipsis.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void AlignmentSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    alignment.reset(reader.ReadNode());
    ellipsis.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

} // namespace soul::cpp20::ast
