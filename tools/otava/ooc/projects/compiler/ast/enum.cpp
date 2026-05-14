module otava.ast.enums;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

EnumSpecifierNode::EnumSpecifierNode(const soul::ast::Span& span_) noexcept : ListNode(NodeKind::enumSpecifierNode, span_)
{
}

EnumSpecifierNode::EnumSpecifierNode(const soul::ast::Span& span_, Node* enumHead_) noexcept :
    ListNode(NodeKind::enumSpecifierNode, span_), enumHead(enumHead_)
{
}

Node* EnumSpecifierNode::Clone() const
{
    EnumSpecifierNode* clone = new EnumSpecifierNode(GetSpan(), enumHead->Clone());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetLBraceSpan(lbSpan);
    clone->SetRBraceSpan(rbSpan);
    clone->SetId(Id());
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
    writer.Write(lbSpan);
    writer.Write(rbSpan);
}

void EnumSpecifierNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    enumHead.reset(reader.ReadNode());
    lbSpan = reader.ReadSpan();
    rbSpan = reader.ReadSpan();
}

EnumHeadNode::EnumHeadNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::enumHeadNode, span_)
{
}

EnumHeadNode::EnumHeadNode(const soul::ast::Span& span_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_, Node* attributes_) noexcept :
    CompoundNode(NodeKind::enumHeadNode, span_), enumKey(enumKey_), enumHeadName(enumHeadName_), enumBase(enumBase_), attributes(attributes_)
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
    EnumHeadNode* clone = new EnumHeadNode(GetSpan(), enumKey->Clone(), enumHeadName->Clone(), clonedEnumBase, clonedAttributes);
    clone->SetId(Id());
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

void EnumHeadNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    enumKey.reset(reader.ReadNode());
    enumHeadName.reset(reader.ReadNode());
    enumBase.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

EnumBaseNode::EnumBaseNode(const soul::ast::Span& span_) noexcept : UnaryNode(NodeKind::enumBaseNode, span_, nullptr)
{
}

EnumBaseNode::EnumBaseNode(const soul::ast::Span& span_, Node* typeSpecifiers_) noexcept : UnaryNode(NodeKind::enumBaseNode, span_, typeSpecifiers_)
{
}

Node* EnumBaseNode::Clone() const
{
    EnumBaseNode* clone = new EnumBaseNode(GetSpan(), Child()->Clone());
    clone->SetId(Id());
    return clone;
}

void EnumBaseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EnumClassNode::EnumClassNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::enumClassNode, span_)
{
}

EnumClassNode::EnumClassNode(const soul::ast::Span& span_, const soul::ast::Span& classSpan_) noexcept :
    CompoundNode(NodeKind::enumClassNode, span_), classSpan(classSpan_)
{
}

Node* EnumClassNode::Clone() const
{
    EnumClassNode* clone = new EnumClassNode(GetSpan(), classSpan);
    clone->SetId(Id());
    return clone;
}

void EnumClassNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumClassNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(classSpan);
}

void EnumClassNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    classSpan = reader.ReadSpan();
}

EnumStructNode::EnumStructNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::enumStructNode, span_)
{
}

EnumStructNode::EnumStructNode(const soul::ast::Span& span_, const soul::ast::Span& structSpan_) noexcept :
    CompoundNode(NodeKind::enumStructNode, span_), structSpan(structSpan_)
{
}

Node* EnumStructNode::Clone() const
{
    EnumStructNode* clone = new EnumStructNode(GetSpan(), structSpan);
    clone->SetId(Id());
    return clone;
}

void EnumStructNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void EnumStructNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(structSpan);
}

void EnumStructNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    structSpan = reader.ReadSpan();
}

EnumNode::EnumNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::enumNode, span_)
{
}

Node* EnumNode::Clone() const
{
    EnumNode* clone = new EnumNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void EnumNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EnumeratorDefinitionNode::EnumeratorDefinitionNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::enumeratorDefinitionNode, span_)
{
}

EnumeratorDefinitionNode::EnumeratorDefinitionNode(const soul::ast::Span& span_, Node* enumerator_, Node* value_,
    const soul::ast::Span& assignSpan_) noexcept :
    CompoundNode(NodeKind::enumeratorDefinitionNode, span_), enumerator(enumerator_), value(value_), assignSpan(assignSpan_)
{
}

Node* EnumeratorDefinitionNode::Clone() const
{
    Node* clonedValue = nullptr;
    if (value)
    {
        clonedValue = value->Clone();
    }
    EnumeratorDefinitionNode* clone = new EnumeratorDefinitionNode(GetSpan(), enumerator->Clone(), clonedValue, assignSpan);
    clone->SetId(Id());
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
    writer.Write(assignSpan);
}

void EnumeratorDefinitionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    enumerator.reset(reader.ReadNode());
    value.reset(reader.ReadNode());
    assignSpan = reader.ReadSpan();
}

EnumeratorNode::EnumeratorNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::enumeratorNode, span_)
{
}

EnumeratorNode::EnumeratorNode(const soul::ast::Span& span_, Node* identifier_, Node* attributes_) noexcept :
    CompoundNode(NodeKind::enumeratorNode, span_), identifier(identifier_), attributes(attributes_)
{
}

Node* EnumeratorNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    EnumeratorNode* clone = new EnumeratorNode(GetSpan(), identifier->Clone(), clonedAttributes);
    clone->SetId(Id());
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

void EnumeratorNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    identifier.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

ElaboratedEnumSpecifierNode::ElaboratedEnumSpecifierNode(const soul::ast::Span& span_) noexcept :
    UnaryNode(NodeKind::elaboratedEnumSpecifierNode, span_, nullptr)
{
}

ElaboratedEnumSpecifierNode::ElaboratedEnumSpecifierNode(const soul::ast::Span& span_, Node* enumName_) noexcept :
    UnaryNode(NodeKind::elaboratedEnumSpecifierNode, span_, enumName_)
{
}

Node* ElaboratedEnumSpecifierNode::Clone() const
{
    ElaboratedEnumSpecifierNode* clone = new ElaboratedEnumSpecifierNode(GetSpan(), Child()->Clone());
    clone->SetId(Id());
    return clone;
}

void ElaboratedEnumSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OpaqueEnumDeclarationNode::OpaqueEnumDeclarationNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::opaqueEnumDeclarationNode, span_)
{
}

OpaqueEnumDeclarationNode::OpaqueEnumDeclarationNode(const soul::ast::Span& span_, Node* enumKey_, Node* enumHeadName_, Node* enumBase_,
    Node* attributes_, Node* semicolon_) noexcept :
    CompoundNode(NodeKind::opaqueEnumDeclarationNode, span_), enumKey(enumKey_), enumHeadName(enumHeadName_), enumBase(enumBase_),
    attributes(attributes_), semicolon(semicolon_)
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
    OpaqueEnumDeclarationNode* clone = new OpaqueEnumDeclarationNode(GetSpan(), enumKey->Clone(), enumHeadName->Clone(), clonedEnumBase, clonedAttributes,
        semicolon->Clone());
    clone->SetId(Id());
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

void OpaqueEnumDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    enumKey.reset(reader.ReadNode());
    enumHeadName.reset(reader.ReadNode());
    enumBase.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

} // namespace otava::ast
