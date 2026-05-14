// =================================
// Copyright (c) 2026 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.type;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

TypeSpecifierSequenceNode::TypeSpecifierSequenceNode(const soul::ast::Span& span_) noexcept : SequenceNode(NodeKind::typeSpecifierSequenceNode, span_)
{
}

Node* TypeSpecifierSequenceNode::Clone() const
{
    TypeSpecifierSequenceNode* clone = new TypeSpecifierSequenceNode(GetSpan());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetId(Id());
    return clone;
}

void TypeSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::u32string TypeSpecifierSequenceNode::Str() const
{
    std::u32string str;
    bool first = true;
    for (const auto& typeSpecifier : Nodes())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(1, ' ');
        }
        str.append(typeSpecifier->Str());
    }
    return str;
}

TypenameSpecifierNode::TypenameSpecifierNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::typenameSpecifierNode, span_)
{
}

TypenameSpecifierNode::TypenameSpecifierNode(const soul::ast::Span& span_, Node* nns_, Node* id_, Node* templateNode_) noexcept :
    CompoundNode(NodeKind::typenameSpecifierNode, span_), nns(nns_), id(id_), templateNode(templateNode_)
{
}

Node* TypenameSpecifierNode::Clone() const
{
    Node* clonedTemplateNode = nullptr;
    if (templateNode)
    {
        clonedTemplateNode = templateNode->Clone();
    }
    TypenameSpecifierNode* clone = new TypenameSpecifierNode(GetSpan(), nns->Clone(), id->Clone(), clonedTemplateNode);
    clone->SetId(Id());
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

void TypenameSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    nns.reset(reader.ReadNode());
    id.reset(reader.ReadNode());
    templateNode.reset(reader.ReadNode());
}

TypeIdNode::TypeIdNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::typeIdNode, span_)
{
}

TypeIdNode::TypeIdNode(const soul::ast::Span& span_, Node* typeSpecifiers_, Node* declarator_) noexcept :
    CompoundNode(NodeKind::typeIdNode, span_), typeSpecifiers(typeSpecifiers_), declarator(declarator_)
{
}

Node* TypeIdNode::Clone() const
{
    Node* clonedDeclarator = nullptr;
    if (declarator)
    {
        clonedDeclarator = declarator->Clone();
    }
    TypeIdNode* clone = new TypeIdNode(GetSpan(), typeSpecifiers->Clone(), clonedDeclarator);
    clone->SetId(Id());
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

void TypeIdNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeSpecifiers.reset(reader.ReadNode());
    declarator.reset(reader.ReadNode());
}

std::u32string TypeIdNode::Str() const
{
    std::u32string str = typeSpecifiers->Str();
    str.append(declarator->Str());
    return str;
}

DefiningTypeIdNode::DefiningTypeIdNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::definingTypeIdNode, span_)
{
}

DefiningTypeIdNode::DefiningTypeIdNode(const soul::ast::Span& span_, Node* definingTypeSpecifiers_, Node* abstractDeclarator_) noexcept :
    CompoundNode(NodeKind::definingTypeIdNode, span_), definingTypeSpecifiers(definingTypeSpecifiers_), abstractDeclarator(abstractDeclarator_)
{
}

Node* DefiningTypeIdNode::Clone() const
{
    Node* clonedDeclarator = nullptr;
    if (abstractDeclarator)
    {
        clonedDeclarator = abstractDeclarator->Clone();
    }
    DefiningTypeIdNode* clone = new DefiningTypeIdNode(GetSpan(), definingTypeSpecifiers->Clone(), clonedDeclarator);
    clone->SetId(Id());
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

void DefiningTypeIdNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    definingTypeSpecifiers.reset(reader.ReadNode());
    abstractDeclarator.reset(reader.ReadNode());
}

std::u32string DefiningTypeIdNode::Str() const
{
    std::u32string str = definingTypeSpecifiers->Str();
    str.append(abstractDeclarator->Str());
    return str;
}

DefiningTypeSpecifierSequenceNode::DefiningTypeSpecifierSequenceNode(const soul::ast::Span& span_) noexcept :
    SequenceNode(NodeKind::definingTypeSpecifierSequenceNode, span_)
{
}

Node* DefiningTypeSpecifierSequenceNode::Clone() const
{
    DefiningTypeSpecifierSequenceNode* clone = new DefiningTypeSpecifierSequenceNode(GetSpan());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetId(Id());
    return clone;
}

void DefiningTypeSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::u32string DefiningTypeSpecifierSequenceNode::Str() const
{
    std::u32string str;
    bool first = true;
    for (const auto& typeSpecifier : Nodes())
    {
        if (first)
        {
            first = false;
        }
        else
        {
            str.append(1, ' ');
        }
        str.append(typeSpecifier->Str());
    }
    return str;
}

TrailingReturnTypeNode::TrailingReturnTypeNode(const soul::ast::Span& span_) noexcept : UnaryNode(NodeKind::trailingReturnTypeNode, span_, nullptr)
{
}

TrailingReturnTypeNode::TrailingReturnTypeNode(const soul::ast::Span& span_, Node* typeId_) noexcept :
    UnaryNode(NodeKind::trailingReturnTypeNode, span_, typeId_)
{
}

Node* TrailingReturnTypeNode::Clone() const
{
    TrailingReturnTypeNode* clone = new TrailingReturnTypeNode(GetSpan(), Child()->Clone());
    clone->SetId(Id());
    return clone;
}

void TrailingReturnTypeNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ElaboratedTypeSpecifierNode::ElaboratedTypeSpecifierNode(const soul::ast::Span& span_) noexcept :
    CompoundNode(NodeKind::elaboratedTypeSpecifierNode, span_)
{
}

ElaboratedTypeSpecifierNode::ElaboratedTypeSpecifierNode(const soul::ast::Span& span_, Node* classKey_, Node* id_, Node* attributes_) noexcept :
    CompoundNode(NodeKind::elaboratedTypeSpecifierNode, span_), classKey(classKey_), id(id_), attributes(attributes_)
{
}

Node* ElaboratedTypeSpecifierNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ElaboratedTypeSpecifierNode* clone = new ElaboratedTypeSpecifierNode(GetSpan(), classKey->Clone(), id->Clone(), clonedAttributes);
    clone->SetId(Id());
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

void ElaboratedTypeSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    classKey.reset(reader.ReadNode());
    id.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

std::u32string ElaboratedTypeSpecifierNode::Str() const
{
    std::u32string str = classKey->Str();
    str.append(id->Str());
    return str;
}

DeclTypeSpecifierNode::DeclTypeSpecifierNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::declTypeSpecifierNode, span_)
{
}

DeclTypeSpecifierNode::DeclTypeSpecifierNode(const soul::ast::Span& span_, Node* expr_,
    const soul::ast::Span& lpSpan_, const soul::ast::Span& rpSpan_) noexcept :
    CompoundNode(NodeKind::declTypeSpecifierNode, span_), expr(expr_), lpSpan(lpSpan_), rpSpan(rpSpan_)
{
}

Node* DeclTypeSpecifierNode::Clone() const
{
    DeclTypeSpecifierNode* clone = new DeclTypeSpecifierNode(GetSpan(), expr->Clone(), lpSpan, rpSpan);
    clone->SetId(Id());
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
    writer.Write(lpSpan);
    writer.Write(rpSpan);
}

void DeclTypeSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    expr.reset(reader.ReadNode());
    lpSpan = reader.ReadSpan();
    rpSpan = reader.ReadSpan();
}

PlaceholderTypeSpecifierNode::PlaceholderTypeSpecifierNode(const soul::ast::Span& span_) noexcept :
    CompoundNode(NodeKind::placeholderTypeSpecifierNode, span_)
{
}

PlaceholderTypeSpecifierNode::PlaceholderTypeSpecifierNode(const soul::ast::Span& span_, Node* typeConstraint_,
    const soul::ast::Span& dtSpan_, const soul::ast::Span& autoSpan_, const soul::ast::Span& lpSpan_, const soul::ast::Span& rpSpan_) noexcept :
    CompoundNode(NodeKind::placeholderTypeSpecifierNode, span_), typeConstraint(typeConstraint_), dtSpan(dtSpan_), autoSpan(autoSpan_), lpSpan(lpSpan_), rpSpan(rpSpan_)
{
}

Node* PlaceholderTypeSpecifierNode::Clone() const
{
    Node* clonedTypeConstraint = nullptr;
    if (typeConstraint)
    {
        clonedTypeConstraint = typeConstraint->Clone();
    }
    PlaceholderTypeSpecifierNode* clone = new PlaceholderTypeSpecifierNode(GetSpan(), clonedTypeConstraint, dtSpan, autoSpan, lpSpan, rpSpan);
    clone->SetId(Id());
    return clone;
}

void PlaceholderTypeSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PlaceholderTypeSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeConstraint.get());
    writer.Write(dtSpan);
    writer.Write(autoSpan);
    writer.Write(lpSpan);
    writer.Write(rpSpan);
}

void PlaceholderTypeSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeConstraint.reset(reader.ReadNode());
    dtSpan = reader.ReadSpan();
    autoSpan = reader.ReadSpan();
    lpSpan = reader.ReadSpan();
    rpSpan = reader.ReadSpan();
}

} // namespace otava::ast
