// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.identifier;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

IdentifierNode::IdentifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::identifierNode, sourcePos_)
{
}

IdentifierNode::IdentifierNode(const soul::ast::SourcePos& sourcePos_, const std::u32string& str_) : CompoundNode(NodeKind::identifierNode, sourcePos_), str(str_)
{
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

UnnamedNode::UnnamedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::unnamedNode, sourcePos_)
{
}

void UnnamedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ColonColonNode::ColonColonNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::colonColonNode, sourcePos_)
{
}

void ColonColonNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NestedNameSpecifierNode::NestedNameSpecifierNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::nestedNameSpecifierNode, sourcePos_)
{
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

void QualifiedIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

IdentifierListNode::IdentifierListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::identifierListNode, sourcePos_)
{
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

} // namespace soul::cpp20::ast
