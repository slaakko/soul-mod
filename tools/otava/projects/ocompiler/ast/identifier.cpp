// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.identifier;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

IdentifierNode::IdentifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::identifierNode, sourcePos_)
{
}

IdentifierNode::IdentifierNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_) : CompoundNode(NodeKind::identifierNode, sourcePos_), str(str_)
{
}

std::expected<Node*, int> IdentifierNode::Clone() const
{
    IdentifierNode* clone = new IdentifierNode(GetSourcePos(), str);
    return std::expected<Node*, int>(clone);
}

void IdentifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> IdentifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(str);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> IdentifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> srv = reader.ReadStr();
    if (!srv) return std::unexpected<int>(srv.error());
    str = *srv;
    return std::expected<bool, int>(true);
}

UnnamedNode::UnnamedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::unnamedNode, sourcePos_)
{
}

std::expected<Node*, int> UnnamedNode::Clone() const
{
    UnnamedNode* clone = new UnnamedNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void UnnamedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ColonColonNode::ColonColonNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::colonColonNode, sourcePos_)
{
}

std::expected<Node*, int> ColonColonNode::Clone() const
{
    ColonColonNode* clone = new ColonColonNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ColonColonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NestedNameSpecifierNode::NestedNameSpecifierNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::nestedNameSpecifierNode, sourcePos_)
{
}

std::expected<Node*, int> NestedNameSpecifierNode::Clone() const
{
    NestedNameSpecifierNode* clone = new NestedNameSpecifierNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void NestedNameSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

QualifiedIdNode::QualifiedIdNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::qualifiedIdNode, sourcePos_, nullptr, nullptr)
{
}

QualifiedIdNode::QualifiedIdNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* unqualifiedId_) : BinaryNode(NodeKind::qualifiedIdNode, sourcePos_, nns_, unqualifiedId_)
{
}

std::expected<Node*, int> QualifiedIdNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    QualifiedIdNode* clone = new QualifiedIdNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
}

void QualifiedIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IdentifierListNode::IdentifierListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::identifierListNode, sourcePos_)
{
}

std::expected<Node*, int> IdentifierListNode::Clone() const
{
    IdentifierListNode* clone = new IdentifierListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void IdentifierListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModuleNameNode::ModuleNameNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::moduleNameNode, sourcePos_)
{
}

ModuleNameNode::ModuleNameNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_) : Node(NodeKind::moduleNameNode, sourcePos_), str(str_)
{
}

std::expected<Node*, int> ModuleNameNode::Clone() const
{
    ModuleNameNode* clone = new ModuleNameNode(GetSourcePos(), str);
    return std::expected<Node*, int>(clone);
}

void ModuleNameNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ModuleNameNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = Node::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(str);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ModuleNameNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<std::u32string, int> srv = reader.ReadStr();
    if (!srv) return std::unexpected<int>(srv.error());
    str = *srv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
