// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.enums;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

EnumSpecifierNode::EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::enumSpecifierNode, sourcePos_)
{
}

EnumSpecifierNode::EnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumHead_) : ListNode(NodeKind::enumSpecifierNode, sourcePos_), enumHead(enumHead_)
{
}

std::expected<Node*, int> EnumSpecifierNode::Clone() const
{
    std::expected<Node*, int> h = enumHead->Clone();
    if (!h) return h;
    EnumSpecifierNode* clone = new EnumSpecifierNode(GetSourcePos(), *h);
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void EnumSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EnumSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(enumHead.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumHead.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

EnumHeadNode::EnumHeadNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumHeadNode, sourcePos_)
{
}

EnumHeadNode::EnumHeadNode(const soul::ast::SourcePos& sourcePos_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_) :
    CompoundNode(NodeKind::enumHeadNode, sourcePos_), enumKey(enumKey_), enumHeadName(enumHeadName_), enumBase(enumBase_), attributes(attributes_)
{
}

std::expected<Node*, int> EnumHeadNode::Clone() const
{
    Node* clonedEnumBase = nullptr;
    if (enumBase)
    {
        std::expected<Node*, int> b = enumBase->Clone();
        if (!b) return b;
        clonedEnumBase = *b;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> k = enumKey->Clone();
    if (!k) return k;
    std::expected<Node*, int> n = enumHeadName->Clone();
    if (!n) return n;
    EnumHeadNode* clone = new EnumHeadNode(GetSourcePos(), *k, *n, clonedEnumBase, clonedAttributes);
    return std::expected<Node*, int>(clone);
}

void EnumHeadNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EnumHeadNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(enumKey.get());
    if (!rv) return rv;
    rv = writer.Write(enumHeadName.get());
    if (!rv) return rv;
    rv = writer.Write(enumBase.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int>EnumHeadNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumKey.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumHeadName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumBase.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

EnumBaseNode::EnumBaseNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::enumBaseNode, sourcePos_, nullptr)
{
}

EnumBaseNode::EnumBaseNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_) : UnaryNode(NodeKind::enumBaseNode, sourcePos_, typeSpecifiers_)
{
}

std::expected<Node*, int> EnumBaseNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    EnumBaseNode* clone = new EnumBaseNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> EnumClassNode::Clone() const
{
    EnumClassNode* clone = new EnumClassNode(GetSourcePos(), classPos);
    return std::expected<Node*, int>(clone);
}

void EnumClassNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EnumClassNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(classPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumClassNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    classPos = *posRv;
    return std::expected<bool, int>(true);
}

EnumStructNode::EnumStructNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumStructNode, sourcePos_)
{
}

EnumStructNode::EnumStructNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& structPos_) :
    CompoundNode(NodeKind::enumStructNode, sourcePos_), structPos(structPos_)
{
}

std::expected<Node*, int> EnumStructNode::Clone() const
{
    EnumStructNode* clone = new EnumStructNode(GetSourcePos(), structPos);
    return std::expected<Node*, int>(clone);
}

void EnumStructNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EnumStructNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(structPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumStructNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    structPos = *posRv;
    return std::expected<bool, int>(true);
}

EnumNode::EnumNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::enumNode, sourcePos_)
{
}

std::expected<Node*, int> EnumNode::Clone() const
{
    EnumNode* clone = new EnumNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> EnumeratorDefinitionNode::Clone() const
{
    Node* clonedValue = nullptr;
    if (value)
    {
        std::expected<Node*, int> v = value->Clone();
        if (!v) return v;
        clonedValue = *v;
    }
    std::expected<Node*, int> e = enumerator->Clone();
    if (!e) return e;
    EnumeratorDefinitionNode* clone = new EnumeratorDefinitionNode(GetSourcePos(), *e, clonedValue, assignPos);
    return std::expected<Node*, int>(clone);
}

void EnumeratorDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EnumeratorDefinitionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(enumerator.get());
    if (!rv) return rv;
    rv = writer.Write(value.get());
    if (!rv) return rv;
    rv = writer.Write(assignPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumeratorDefinitionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumerator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    value.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    assignPos = *posRv;
    return std::expected<bool, int>(true);
}

EnumeratorNode::EnumeratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::enumeratorNode, sourcePos_)
{
}

EnumeratorNode::EnumeratorNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* attributes_) :
    CompoundNode(NodeKind::enumeratorNode, sourcePos_), identifier(identifier_), attributes(attributes_)
{
}

std::expected<Node*, int> EnumeratorNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> i = identifier->Clone();
    if (!i) return i;
    EnumeratorNode* clone = new EnumeratorNode(GetSourcePos(), *i, clonedAttributes);
    return clone;
}

void EnumeratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> EnumeratorNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(identifier.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> EnumeratorNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    identifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

ElaboratedEnumSpecifierNode::ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::elaboratedEnumSpecifierNode, sourcePos_, nullptr)
{
}

ElaboratedEnumSpecifierNode::ElaboratedEnumSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* enumName_) :
    UnaryNode(NodeKind::elaboratedEnumSpecifierNode, sourcePos_, enumName_)
{
}

std::expected<Node*, int> ElaboratedEnumSpecifierNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    ElaboratedEnumSpecifierNode* clone = new ElaboratedEnumSpecifierNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> OpaqueEnumDeclarationNode::Clone() const
{
    Node* clonedEnumBase = nullptr;
    if (enumBase)
    {
        std::expected<Node*, int> b = enumBase->Clone();
        if (!b) return b;
        clonedEnumBase = *b;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> k = enumKey->Clone();
    if (!k) return k;
    std::expected<Node*, int> n = enumHeadName->Clone();
    if (!n) return n;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    OpaqueEnumDeclarationNode* clone = new OpaqueEnumDeclarationNode(GetSourcePos(), *k, *n, clonedEnumBase, clonedAttributes, *sc);
    return std::expected<Node*, int>(clone);
}

void OpaqueEnumDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> OpaqueEnumDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(enumKey.get());
    if (!rv) return rv;
    rv = writer.Write(enumHeadName.get());
    if (!rv) return rv;
    rv = writer.Write(enumBase.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> OpaqueEnumDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumKey.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumHeadName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    enumBase.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
