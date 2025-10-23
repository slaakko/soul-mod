// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.type;

import otava.ast.visitor;

namespace otava::ast {

TypeSpecifierSequenceNode::TypeSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::typeSpecifierSequenceNode, sourcePos_)
{
}

std::expected<Node*, int> TypeSpecifierSequenceNode::Clone() const
{
    TypeSpecifierSequenceNode* clone = new TypeSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> TypenameSpecifierNode::Clone() const
{
    Node* clonedTemplateNode = nullptr;
    if (templateNode)
    {
        std::expected<Node*, int> t = templateNode->Clone();
        if (!t) return t;
        clonedTemplateNode = *t;
    }
    std::expected<Node*, int> n = nns->Clone();
    if (!n) return n;
    std::expected<Node*, int> i = id->Clone();
    if (!i) return i;
    TypenameSpecifierNode* clone = new TypenameSpecifierNode(GetSourcePos(), *n, *i, clonedTemplateNode);
    return std::expected<Node*, int>(clone);
}

void TypenameSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypenameSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(nns.get());
    if (!rv) return rv;
    rv = writer.Write(id.get());
    if (!rv) return rv;
    rv = writer.Write(templateNode.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> TypeIdNode::Clone() const
{
    Node* clonedDeclarator = nullptr;
    if (declarator)
    {
        std::expected<Node*, int> d = declarator->Clone();
        if (!d) return d;
        clonedDeclarator = *d;
    }
    std::expected<Node*, int> t = typeSpecifiers->Clone();
    if (!t) return t;
    TypeIdNode* clone = new TypeIdNode(GetSourcePos(), *t, clonedDeclarator);
    return std::expected<Node*, int>(clone);
}

void TypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeIdNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> DefiningTypeIdNode::Clone() const
{
    Node* clonedDeclarator = nullptr;
    if (abstractDeclarator)
    {
        std::expected<Node*, int> d = abstractDeclarator->Clone();
        if (!d) return d;
        clonedDeclarator = *d;
    }
    std::expected<Node*, int> d = definingTypeSpecifiers->Clone();
    if (!d) return d;
    DefiningTypeIdNode* clone = new DefiningTypeIdNode(GetSourcePos(), *d, clonedDeclarator);
    return std::expected<Node*, int>(clone);
}

void DefiningTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DefiningTypeIdNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(definingTypeSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(abstractDeclarator.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> DefiningTypeSpecifierSequenceNode::Clone() const
{
    DefiningTypeSpecifierSequenceNode* clone = new DefiningTypeSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> TrailingReturnTypeNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    TrailingReturnTypeNode* clone = new TrailingReturnTypeNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> ElaboratedTypeSpecifierNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> k = classKey->Clone();
    if (!k) return k;
    std::expected<Node*, int> i = id->Clone();
    if (!i) return i;
    ElaboratedTypeSpecifierNode* clone = new ElaboratedTypeSpecifierNode(GetSourcePos(), *k, *i, clonedAttributes);
    return std::expected<Node*, int>(clone);
}

void ElaboratedTypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ElaboratedTypeSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(classKey.get());
    if (!rv) return rv;
    rv = writer.Write(id.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> DeclTypeSpecifierNode::Clone() const
{
    std::expected<Node*, int> e = expr->Clone();
    if (!e) return e;
    DeclTypeSpecifierNode* clone = new DeclTypeSpecifierNode(GetSourcePos(), *e, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void DeclTypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DeclTypeSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(expr.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> PlaceholderTypeSpecifierNode::Clone() const
{
    Node* clonedTypeConstraint = nullptr;
    if (typeConstraint)
    {
        std::expected<Node*, int> t = typeConstraint->Clone();
        if (!t) return t;
        clonedTypeConstraint = *t;
    }
    PlaceholderTypeSpecifierNode* clone = new PlaceholderTypeSpecifierNode(GetSourcePos(), clonedTypeConstraint, dtPos, autoPos, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void PlaceholderTypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PlaceholderTypeSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeConstraint.get());
    if (!rv) return rv;
    rv = writer.Write(dtPos);
    if (!rv) return rv;
    rv = writer.Write(autoPos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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
