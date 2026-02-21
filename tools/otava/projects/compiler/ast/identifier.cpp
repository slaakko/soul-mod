// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.identifier;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

IdentifierNode::IdentifierNode(const soul::ast::SourcePos& sourcePos_) noexcept : CompoundNode(NodeKind::identifierNode, sourcePos_)
{
}

IdentifierNode::IdentifierNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_) noexcept :
    CompoundNode(NodeKind::identifierNode, sourcePos_), str(str_)
{
}

Node* IdentifierNode::Clone() const
{
    IdentifierNode* clone = new IdentifierNode(GetSourcePos(), str);
    return clone;
}

void IdentifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void IdentifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(str);
}

void IdentifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    str = reader.ReadStr();
}

UnnamedNode::UnnamedNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::unnamedNode, sourcePos_)
{
}

Node* UnnamedNode::Clone() const
{
    UnnamedNode* clone = new UnnamedNode(GetSourcePos());
    return clone;
}

void UnnamedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ColonColonNode::ColonColonNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::colonColonNode, sourcePos_)
{
}

Node* ColonColonNode::Clone() const
{
    ColonColonNode* clone = new ColonColonNode(GetSourcePos());
    return clone;
}

void ColonColonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NestedNameSpecifierNode::NestedNameSpecifierNode(const soul::ast::SourcePos& sourcePos_) noexcept : SequenceNode(NodeKind::nestedNameSpecifierNode, sourcePos_)
{
}

Node* NestedNameSpecifierNode::Clone() const
{
    NestedNameSpecifierNode* clone = new NestedNameSpecifierNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void NestedNameSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

QualifiedIdNode::QualifiedIdNode(const soul::ast::SourcePos& sourcePos_) noexcept : BinaryNode(NodeKind::qualifiedIdNode, sourcePos_, nullptr, nullptr)
{
}

QualifiedIdNode::QualifiedIdNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* unqualifiedId_) noexcept :
    BinaryNode(NodeKind::qualifiedIdNode, sourcePos_, nns_, unqualifiedId_)
{
}

Node* QualifiedIdNode::Clone() const
{
    QualifiedIdNode* clone = new QualifiedIdNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void QualifiedIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IdentifierListNode::IdentifierListNode(const soul::ast::SourcePos& sourcePos_) noexcept : ListNode(NodeKind::identifierListNode, sourcePos_)
{
}

Node* IdentifierListNode::Clone() const
{
    IdentifierListNode* clone = new IdentifierListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void IdentifierListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModuleNameNode::ModuleNameNode(const soul::ast::SourcePos& sourcePos_) noexcept : Node(NodeKind::moduleNameNode, sourcePos_)
{
}

ModuleNameNode::ModuleNameNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_) : Node(NodeKind::moduleNameNode, sourcePos_), str(str_)
{
}

Node* ModuleNameNode::Clone() const
{
    ModuleNameNode* clone = new ModuleNameNode(GetSourcePos(), str);
    return clone;
}

void ModuleNameNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ModuleNameNode::Write(Writer& writer)
{
    Node::Write(writer);
    writer.Write(str);
}

void ModuleNameNode::Read(Reader& reader)
{
    Node::Read(reader);
    str = reader.ReadStr();
}

} // namespace otava::ast
