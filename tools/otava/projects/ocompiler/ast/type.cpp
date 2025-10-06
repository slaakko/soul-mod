// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.type;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

TypeSpecifierSequenceNode::TypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::typeSpecifierSequenceNode, sourcePos_)
{
}

Node* TypeSpecifierSequenceNode::Clone() const
{
    TypeSpecifierSequenceNode* clone = new TypeSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* TypenameSpecifierNode::Clone() const
{
    Node* clonedTemplateNode = nullptr;
    if (templateNode)
    {
        clonedTemplateNode = templateNode->Clone();
    }
    TypenameSpecifierNode* clone = new TypenameSpecifierNode(GetSourcePos(), nns->Clone(), id->Clone(), clonedTemplateNode);
    return clone;
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

std::expected<bool, int> TypenameSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    nns.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    id.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateNode.reset(*nrv);
    return std::expected<bool, int>(true);
}

TypeIdNode::TypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::typeIdNode, sourcePos_)
{
}

TypeIdNode::TypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_) :
    CompoundNode(NodeKind::typeIdNode, sourcePos_), typeSpecifiers(typeSpecifiers_), declarator(declarator_)
{
}

Node* TypeIdNode::Clone() const
{
    Node* clonedDeclarator = nullptr;
    if (declarator)
    {
        clonedDeclarator = declarator->Clone();
    }
    TypeIdNode* clone = new TypeIdNode(GetSourcePos(), typeSpecifiers->Clone(), clonedDeclarator);
    return clone;
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

std::expected<bool, int> TypeIdNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    return std::expected<bool, int>(true);
}

DefiningTypeIdNode::DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::definingTypeIdNode, sourcePos_)
{
}

DefiningTypeIdNode::DefiningTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* definingTypeSpecifiers_, Node* abstractDeclarator_) :
    CompoundNode(NodeKind::definingTypeIdNode, sourcePos_), definingTypeSpecifiers(definingTypeSpecifiers_), abstractDeclarator(abstractDeclarator_)
{
}

Node* DefiningTypeIdNode::Clone() const
{
    Node* clonedDeclarator = nullptr;
    if (abstractDeclarator)
    {
        clonedDeclarator = abstractDeclarator->Clone();
    }
    DefiningTypeIdNode* clone = new DefiningTypeIdNode(GetSourcePos(), definingTypeSpecifiers->Clone(), clonedDeclarator);
    return clone;
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

std::expected<bool, int> DefiningTypeIdNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    definingTypeSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    abstractDeclarator.reset(*nrv);
    return std::expected<bool, int>(true);
}

DefiningTypeSpecifierSequenceNode::DefiningTypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) :
    SequenceNode(NodeKind::definingTypeSpecifierSequenceNode, sourcePos_)
{
}

Node* DefiningTypeSpecifierSequenceNode::Clone() const
{
    DefiningTypeSpecifierSequenceNode* clone = new DefiningTypeSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* TrailingReturnTypeNode::Clone() const
{
    TrailingReturnTypeNode* clone = new TrailingReturnTypeNode(GetSourcePos(), Child()->Clone());
    return clone;
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

Node* ElaboratedTypeSpecifierNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ElaboratedTypeSpecifierNode* clone = new ElaboratedTypeSpecifierNode(GetSourcePos(), classKey->Clone(), id->Clone(), clonedAttributes);
    return clone;
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

std::expected<bool, int> ElaboratedTypeSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    classKey.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    id.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

DeclTypeSpecifierNode::DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::declTypeSpecifierNode, sourcePos_)
{
}

DeclTypeSpecifierNode::DeclTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::declTypeSpecifierNode, sourcePos_), expr(expr_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* DeclTypeSpecifierNode::Clone() const
{
    DeclTypeSpecifierNode* clone = new DeclTypeSpecifierNode(GetSourcePos(), expr->Clone(), lpPos, rpPos);
    return clone;
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

std::expected<bool, int> DeclTypeSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    expr.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

PlaceholderTypeSpecifierNode::PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::placeholderTypeSpecifierNode, sourcePos_)
{
}

PlaceholderTypeSpecifierNode::PlaceholderTypeSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_,
    const soul::ast::SourcePos& dtPos_, const soul::ast::SourcePos& autoPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::placeholderTypeSpecifierNode, sourcePos_), typeConstraint(typeConstraint_), dtPos(dtPos_), autoPos(autoPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* PlaceholderTypeSpecifierNode::Clone() const
{
    Node* clonedTypeConstraint = nullptr;
    if (typeConstraint)
    {
        clonedTypeConstraint = typeConstraint->Clone();
    }
    return new PlaceholderTypeSpecifierNode(GetSourcePos(), clonedTypeConstraint, dtPos, autoPos, lpPos, rpPos);
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

std::expected<bool, int> PlaceholderTypeSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeConstraint.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    dtPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    autoPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
