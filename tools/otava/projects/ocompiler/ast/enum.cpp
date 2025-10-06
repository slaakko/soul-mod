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

Node* EnumSpecifierNode::Clone() const
{
    EnumSpecifierNode* clone = new EnumSpecifierNode(GetSourcePos(), enumHead->Clone());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* EnumHeadNode::Clone() const
{
    Node* clonedEnumBase = nullptr;
    if (enumBase)
    {
        clonedEnumBase = enumBase->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    EnumHeadNode* clone = new EnumHeadNode(GetSourcePos(), enumKey->Clone(), enumHeadName->Clone(), clonedEnumBase, clonedAttributes);
    return clone;
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

Node* EnumBaseNode::Clone() const
{
    EnumBaseNode* clone = new EnumBaseNode(GetSourcePos(), Child()->Clone());
    return clone;
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

Node* EnumClassNode::Clone() const
{
    EnumClassNode* clone = new EnumClassNode(GetSourcePos(), classPos);
    return clone;
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

Node* EnumStructNode::Clone() const
{
    EnumStructNode* clone = new EnumStructNode(GetSourcePos(), structPos);
    return clone;
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

Node* EnumNode::Clone() const
{
    EnumNode* clone = new EnumNode(GetSourcePos());
    return clone;
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

Node* EnumeratorDefinitionNode::Clone() const
{
    Node* clonedValue = nullptr;
    if (value)
    {
        clonedValue = value->Clone();
    }
    EnumeratorDefinitionNode* clone = new EnumeratorDefinitionNode(GetSourcePos(), enumerator->Clone(), clonedValue, assignPos);
    return clone;
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

Node* EnumeratorNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    EnumeratorNode* clone = new EnumeratorNode(GetSourcePos(), identifier->Clone(), clonedAttributes);
    return clone;
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

Node* ElaboratedEnumSpecifierNode::Clone() const
{
    ElaboratedEnumSpecifierNode* clone = new ElaboratedEnumSpecifierNode(GetSourcePos(), Child()->Clone());
    return clone;
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

Node* OpaqueEnumDeclarationNode::Clone() const
{
    Node* clonedEnumBase = nullptr;
    if (enumBase)
    {
        clonedEnumBase = enumBase->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    OpaqueEnumDeclarationNode* clone = new OpaqueEnumDeclarationNode(GetSourcePos(), enumKey->Clone(), enumHeadName->Clone(), clonedEnumBase, clonedAttributes, semicolon->Clone());
    return clone;
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
