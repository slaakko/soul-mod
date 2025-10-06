// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.attribute;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

AttributeSpecifierSequenceNode::AttributeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::attributeSpecifierSequenceNode, sourcePos_)
{
}

Node* AttributeSpecifierSequenceNode::Clone() const
{
    AttributeSpecifierSequenceNode* clone = new AttributeSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void AttributeSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AttributeSpecifierNode::AttributeSpecifierNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::attributeSpecifierNode, sourcePos_)
{
}

Node* AttributeSpecifierNode::Clone() const
{
    AttributeSpecifierNode* clone = new AttributeSpecifierNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

std::expected<bool, int> AttributeSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> brv = ListNode::Read(reader);
    if (!brv) return brv;
    std::expected<Node*, int> rv = reader.ReadNode();
    if (!rv) return std::unexpected<int>(rv.error());
    Node* node = *rv;
    usingPrefix.reset(node);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos1 = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos2 = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos1 = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos2 = *posRv;
    return std::expected<bool, int>(true);
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

Node* AttributeUsingPrefixNode::Clone() const
{
    AttributeUsingPrefixNode* clone = new AttributeUsingPrefixNode(GetSourcePos(), Child()->Clone(), colonPos);
    return clone;
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

std::expected<bool, int> AttributeUsingPrefixNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    colonPos = *posRv;
    return std::expected<bool, int>(true);
}

AttributeNode::AttributeNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::attrbuteNode, sourcePos_)
{
}

AttributeNode::AttributeNode(const soul::ast::SourcePos& sourcePos_, Node* attributeToken_, Node* attributeArgs_) :
    CompoundNode(NodeKind::attrbuteNode, sourcePos_), attributeToken(attributeToken_), attributeArgs(attributeArgs_)
{
}

Node* AttributeNode::Clone() const
{
    AttributeNode* clone = new AttributeNode(GetSourcePos(), attributeToken->Clone(), attributeArgs->Clone());
    return clone;
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

std::expected<bool, int> AttributeNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributeToken.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributeArgs.reset(*nrv);
    return std::expected<bool, int>(true);
}

AttributeScopedTokenNode::AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::attributeScopedTokenNode, sourcePos_)
{
}

AttributeScopedTokenNode::AttributeScopedTokenNode(const soul::ast::SourcePos& sourcePos_, Node* ns_, Node* colonColon_, Node* identifier_) :
    CompoundNode(NodeKind::attributeScopedTokenNode, sourcePos_), ns(ns_), colonColon(colonColon_), identifier(identifier_)
{
}

Node* AttributeScopedTokenNode::Clone() const
{
    AttributeScopedTokenNode* clone = new AttributeScopedTokenNode(GetSourcePos(), ns->Clone(), colonColon->Clone(), identifier->Clone());
    return clone;
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

std::expected<bool, int> AttributeScopedTokenNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ns.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    colonColon.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    identifier.reset(*nrv);
    return std::expected<bool, int>(true);
}

AttributeArgumentsNode::AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::attributeArgumentsNode, sourcePos_)
{
}

AttributeArgumentsNode::AttributeArgumentsNode(const soul::ast::SourcePos& sourcePos_, Node* balancedTokenSequence_,
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::attributeArgumentsNode, sourcePos_), balancedTokenSequence(balancedTokenSequence_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* AttributeArgumentsNode::Clone() const
{
    AttributeArgumentsNode* clone = new AttributeArgumentsNode(GetSourcePos(), balancedTokenSequence->Clone(), lpPos, rpPos);
    return clone;
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

std::expected<bool, int> AttributeArgumentsNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    balancedTokenSequence.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

BalancedTokenSequenceNode::BalancedTokenSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::balancedTokenSequenceNode, sourcePos_)
{
}

Node* BalancedTokenSequenceNode::Clone() const
{
    BalancedTokenSequenceNode* clone = new BalancedTokenSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* TokenNode::Clone() const
{
    TokenNode* clone = new TokenNode(GetSourcePos(), str);
    return clone;
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

std::expected<bool, int> TokenNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> strRv = reader.ReadStr();
    if (!strRv) return std::unexpected<int>(strRv.error());
    str = *strRv;
    return std::expected<bool, int>(true);
}

AlignmentSpecifierNode::AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::alignmentSpecifierNode, sourcePos_)
{
}

AlignmentSpecifierNode::AlignmentSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* alignment_, Node* ellipsis_,
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::alignmentSpecifierNode, sourcePos_), alignment(alignment_), ellipsis(ellipsis_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* AlignmentSpecifierNode::Clone() const
{
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        clonedEllipsis = ellipsis->Clone();
    }
    AlignmentSpecifierNode* clone = new AlignmentSpecifierNode(GetSourcePos(), alignment->Clone(), clonedEllipsis, lpPos, rpPos);
    return clone;
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

std::expected<bool, int> AlignmentSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    alignment.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ellipsis.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
