// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.type;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

TypeSpecifierSequenceNode::TypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::typeSpecifierSequenceNode, sourcePos_)
{
}

void TypeSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypenameSpecifierNode::TypenameSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::typenameSpecifierNode, sourcePos_)
{
}

TypenameSpecifierNode::TypenameSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* id_, Node* templateNode_) :
    CompoundNode(NodeKind::typenameSpecifierNode, sourcePos_), nns(nns_), id(id_), templateNode(templateNode_)
{
}

void TypenameSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TypenameSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(nns.get());
    writer.Write(id.get());
    writer.Write(templateNode.get());
}

void TypenameSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    nns.reset(reader.ReadNode());
    id.reset(reader.ReadNode());
    templateNode.reset(reader.ReadNode());
}

TypeIdNode::TypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::typeIdNode, sourcePos_)
{
}

TypeIdNode::TypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_) :
    CompoundNode(NodeKind::typeIdNode, sourcePos_), typeSpecifiers(typeSpecifiers_), declarator(declarator_)
{
}

void TypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TypeIdNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeSpecifiers.get());
    writer.Write(declarator.get());
}

void TypeIdNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeSpecifiers.reset(reader.ReadNode());
    declarator.reset(reader.ReadNode());
}

DefiningTypeIdNode::DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::definingTypeIdNode, sourcePos_)
{
}

DefiningTypeIdNode::DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* definingTypeSpecifiers_, Node* abstractDeclarator_) :
    CompoundNode(NodeKind::definingTypeIdNode, sourcePos_), definingTypeSpecifiers(definingTypeSpecifiers_), abstractDeclarator(abstractDeclarator_)
{
}

void DefiningTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DefiningTypeIdNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(definingTypeSpecifiers.get());
    writer.Write(abstractDeclarator.get());
}

void DefiningTypeIdNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    definingTypeSpecifiers.reset(reader.ReadNode());
    abstractDeclarator.reset(reader.ReadNode());
}

DefiningTypeSpecifierSequenceNode::DefiningTypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) :
    SequenceNode(NodeKind::definingTypeSpecifierSequenceNode, sourcePos_)
{
}

void DefiningTypeSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TrailingReturnTypeNode::TrailingReturnTypeNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::trailingReturnTypeNode, sourcePos_, nullptr)
{
}

TrailingReturnTypeNode::TrailingReturnTypeNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_) : UnaryNode(NodeKind::trailingReturnTypeNode, sourcePos_, typeId_)
{
}

void TrailingReturnTypeNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ElaboratedTypeSpecifierNode::ElaboratedTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::elaboratedTypeSpecifierNode, sourcePos_)
{
}

ElaboratedTypeSpecifierNode::ElaboratedTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* classKey_, Node* id_, Node* attributes_) :
    CompoundNode(NodeKind::elaboratedTypeSpecifierNode, sourcePos_), classKey(classKey_), id(id_), attributes(attributes_)
{
}

void ElaboratedTypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ElaboratedTypeSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(classKey.get());
    writer.Write(id.get());
    writer.Write(attributes.get());
}

void ElaboratedTypeSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    classKey.reset(reader.ReadNode());
    id.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

DeclTypeSpecifierNode::DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::declTypeSpecifierNode, sourcePos_)
{
}

DeclTypeSpecifierNode::DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::declTypeSpecifierNode, sourcePos_), expr(expr_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void DeclTypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DeclTypeSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(expr.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void DeclTypeSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    expr.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

PlaceholderTypeSpecifierNode::PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::placeholderTypeSpecifierNode, sourcePos_)
{
}

PlaceholderTypeSpecifierNode::PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_,
    const soul::ast::SourcePos& dtPos_, const soul::ast::SourcePos& autoPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::placeholderTypeSpecifierNode, sourcePos_), typeConstraint(typeConstraint_), dtPos(dtPos_), autoPos(autoPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void PlaceholderTypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PlaceholderTypeSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeConstraint.get());
    writer.Write(dtPos);
    writer.Write(autoPos);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void PlaceholderTypeSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeConstraint.reset(reader.ReadNode());
    dtPos = reader.ReadSourcePos();
    autoPos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

} // namespace soul::cpp20::ast
