// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.enums;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

EnumSpecifierNode::EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::enumSpecifierNode, sourcePos_)
{
}

EnumSpecifierNode::EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumHead_) : ListNode(NodeKind::enumSpecifierNode, sourcePos_), enumHead(enumHead_)
{
}

void EnumSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumSpecifierNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(enumHead.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void EnumSpecifierNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    enumHead.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

EnumHeadNode::EnumHeadNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumHeadNode, sourcePos_)
{
}

EnumHeadNode::EnumHeadNode(const soul::ast::SourcePos& sourcePos_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_) :
    CompoundNode(NodeKind::enumHeadNode, sourcePos_), enumKey(enumKey_), enumHeadName(enumHeadName_), enumBase(enumBase_), attributes(attributes_)
{
}

void EnumHeadNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumHeadNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(enumKey.get());
    writer.Write(enumHeadName.get());
    writer.Write(enumBase.get());
    writer.Write(attributes.get());
}

void EnumHeadNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    enumKey.reset(reader.ReadNode());
    enumHeadName.reset(reader.ReadNode());
    enumBase.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

EnumBaseNode::EnumBaseNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::enumBaseNode, sourcePos_, nullptr)
{
}

EnumBaseNode::EnumBaseNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_) : UnaryNode(NodeKind::enumBaseNode, sourcePos_, typeSpecifiers_)
{
}

void EnumBaseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EnumClassNode::EnumClassNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumClassNode, sourcePos_)
{
}

EnumClassNode::EnumClassNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& classPos_) : CompoundNode(NodeKind::enumClassNode, sourcePos_), classPos(classPos_)
{
}

void EnumClassNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumClassNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(classPos);
}

void EnumClassNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    classPos = reader.ReadSourcePos();
}

EnumStructNode::EnumStructNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumStructNode, sourcePos_)
{
}

EnumStructNode::EnumStructNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& structPos_) : 
    CompoundNode(NodeKind::enumStructNode, sourcePos_), structPos(structPos_)
{
}

void EnumStructNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumStructNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(structPos);
}

void EnumStructNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    structPos = reader.ReadSourcePos();
}

EnumNode::EnumNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::enumNode, sourcePos_)
{
}

void EnumNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EnumeratorDefinitionNode::EnumeratorDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumeratorDefinitionNode, sourcePos_)
{
}

EnumeratorDefinitionNode::EnumeratorDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* enumerator_, Node* value_, const soul::ast::SourcePos& assignPos_) :
    CompoundNode(NodeKind::enumeratorDefinitionNode, sourcePos_), enumerator(enumerator_), value(value_), assignPos(assignPos_)
{
}

void EnumeratorDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumeratorDefinitionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(enumerator.get());
    writer.Write(value.get());
    writer.Write(assignPos);
}

void EnumeratorDefinitionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    enumerator.reset(reader.ReadNode());
    value.reset(reader.ReadNode());
    assignPos = reader.ReadSourcePos();
}

EnumeratorNode::EnumeratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumeratorNode, sourcePos_)
{
}

EnumeratorNode::EnumeratorNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* attributes_) :
    CompoundNode(NodeKind::enumeratorNode, sourcePos_), identifier(identifier_), attributes(attributes_)
{
}

void EnumeratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumeratorNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(identifier.get());
    writer.Write(attributes.get());
}

void EnumeratorNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    identifier.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

ElaboratedEnumSpecifierNode::ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::elaboratedEnumSpecifierNode, sourcePos_, nullptr)
{
}

ElaboratedEnumSpecifierNode::ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumName_) :
    UnaryNode(NodeKind::elaboratedEnumSpecifierNode, sourcePos_, enumName_)
{
}

void ElaboratedEnumSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OpaqueEnumDeclarationNode::OpaqueEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::opaqueEnumDeclarationNode, sourcePos_)
{
}

OpaqueEnumDeclarationNode::OpaqueEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::opaqueEnumDeclarationNode, sourcePos_), enumKey(enumKey_), enumHeadName(enumHeadName_), enumBase(enumBase_), attributes(attributes_), semicolon(semicolon_)
{
}

void OpaqueEnumDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void OpaqueEnumDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(enumKey.get());
    writer.Write(enumHeadName.get());
    writer.Write(enumBase.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

void OpaqueEnumDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    enumKey.reset(reader.ReadNode());
    enumHeadName.reset(reader.ReadNode());
    enumBase.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

} // namespace soul::cpp20::ast
