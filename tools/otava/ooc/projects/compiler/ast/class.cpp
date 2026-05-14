module otava.ast.classes;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;
import otava.ast.function;

namespace otava::ast {

ClassSpecifierNode::ClassSpecifierNode(const soul::ast::Span& span_) noexcept :
    SequenceNode(NodeKind::classSpecifierNode, span_), complete(false)
{
}

ClassSpecifierNode::ClassSpecifierNode(const soul::ast::Span& span_, Node* classHead_) noexcept :
    SequenceNode(NodeKind::classSpecifierNode, span_), classHead(classHead_), complete(false)
{
}

Node* ClassSpecifierNode::Clone() const
{
    ClassSpecifierNode* clone = new ClassSpecifierNode(GetSpan(), classHead->Clone());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetLBraceSpan(lbSpan);
    clone->SetRBraceSpan(rbSpan);
    clone->SetId(Id());
    return clone;
}

void ClassSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ClassSpecifierNode::Write(Writer& writer)
{
    SequenceNode::Write(writer);
    writer.Write(classHead.get());
    writer.Write(lbSpan);
    writer.Write(rbSpan);
    writer.GetBinaryStreamWriter().Write(complete);
}

void ClassSpecifierNode::Read(Reader& reader)
{
    SequenceNode::Read(reader);
    classHead.reset(reader.ReadNode());
    lbSpan = reader.ReadSpan();
    rbSpan = reader.ReadSpan();
    complete = reader.GetBinaryStreamReader().ReadBool();
}

ClassHeadNode::ClassHeadNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::classHeadNode, span_)
{
}

ClassHeadNode::ClassHeadNode(const soul::ast::Span& span_, Node* classKey_, Node* classHeadName_, Node* classVirtSpecifier_, Node* baseClause_,
    Node* attributes_) noexcept :
    CompoundNode(NodeKind::classHeadNode, span_), classKey(classKey_), classHeadName(classHeadName_), classVirtSpecifier(classVirtSpecifier_),
    baseClause(baseClause_), attributes(attributes_)
{
}

Node* ClassHeadNode::Clone() const
{
    Node* clonedClassVirtSpecifiers = nullptr;
    if (classVirtSpecifier)
    {
        clonedClassVirtSpecifiers = classVirtSpecifier->Clone();
    }
    Node* clonedBaseClause = nullptr;
    if (baseClause)
    {
        clonedBaseClause = baseClause->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ClassHeadNode* clone = new ClassHeadNode(GetSpan(), classKey->Clone(), classHeadName->Clone(), clonedClassVirtSpecifiers, clonedBaseClause, clonedAttributes);
    clone->SetId(Id());
    return clone;
}

void ClassHeadNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ClassHeadNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(classKey.get());
    writer.Write(classHeadName.get());
    writer.Write(classVirtSpecifier.get());
    writer.Write(baseClause.get());
    writer.Write(attributes.get());
}

void ClassHeadNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    classKey.reset(reader.ReadNode());
    classHeadName.reset(reader.ReadNode());
    classVirtSpecifier.reset(reader.ReadNode());
    baseClause.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

BaseClauseNode::BaseClauseNode(const soul::ast::Span& span_) noexcept : UnaryNode(NodeKind::baseClauseNode, span_, nullptr)
{
}

BaseClauseNode::BaseClauseNode(const soul::ast::Span& span_, Node* baseSpecifierList_) noexcept :
    UnaryNode(NodeKind::baseClauseNode, span_, baseSpecifierList_)
{
}

Node* BaseClauseNode::Clone() const
{
    BaseClauseNode* clone = new BaseClauseNode(GetSpan(), Child()->Clone());
    clone->SetId(Id());
    return clone;
}

void BaseClauseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BaseSpecifierListNode::BaseSpecifierListNode(const soul::ast::Span& span_) noexcept : ListNode(NodeKind::baseSpecifierListNode, span_)
{
}

Node* BaseSpecifierListNode::Clone() const
{
    BaseSpecifierListNode* clone = new BaseSpecifierListNode(GetSpan());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetId(Id());
    return clone;
}

void BaseSpecifierListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BaseSpecifierNode::BaseSpecifierNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::baseSpecifierNode, span_), virtualFirst(false)
{
}

BaseSpecifierNode::BaseSpecifierNode(const soul::ast::Span& span_, Node* classOrDeclType_, Node* accessSpecifier_, Node* virtualSpecifier_,
    Node* attributes_, bool virtualFirst_) noexcept :
    CompoundNode(NodeKind::baseSpecifierNode, span_), classOrDeclType(classOrDeclType_), accessSpecifier(accessSpecifier_),
    virtualSpecifier(virtualSpecifier_), attributes(attributes_), virtualFirst(virtualFirst_)
{
}

Node* BaseSpecifierNode::Clone() const
{
    Node* clonedAccessSpecifier = nullptr;
    if (accessSpecifier)
    {
        clonedAccessSpecifier = accessSpecifier->Clone();
    }
    Node* clonedVirtualSpecifier = nullptr;
    if (virtualSpecifier)
    {
        clonedVirtualSpecifier = virtualSpecifier->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    BaseSpecifierNode* clone = new BaseSpecifierNode(GetSpan(), classOrDeclType->Clone(), clonedAccessSpecifier, clonedVirtualSpecifier,
        clonedAttributes, virtualFirst);
    clone->SetId(Id());
    return clone;
}

void BaseSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BaseSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(classOrDeclType.get());
    writer.Write(accessSpecifier.get());
    writer.Write(virtualSpecifier.get());
    writer.Write(attributes.get());
    writer.Write(virtualFirst);
}

void BaseSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    classOrDeclType.reset(reader.ReadNode());
    accessSpecifier.reset(reader.ReadNode());
    virtualSpecifier.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    virtualFirst = reader.ReadBool();
}

BeginAccessGroupNode::BeginAccessGroupNode(const soul::ast::Span& span_) noexcept : UnaryNode(NodeKind::beginAccessGroupNode, span_, nullptr)
{
}

BeginAccessGroupNode::BeginAccessGroupNode(const soul::ast::Span& span_, Node* accessSpecifier_, const soul::ast::Span& colonSpan_) noexcept :
    UnaryNode(NodeKind::beginAccessGroupNode, span_, accessSpecifier_), colonSpan(colonSpan_)
{
}

Node* BeginAccessGroupNode::Clone() const
{
    BeginAccessGroupNode* clone = new BeginAccessGroupNode(GetSpan(), Child()->Clone(), colonSpan);
    clone->SetId(Id());
    return clone;
}

void BeginAccessGroupNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BeginAccessGroupNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(colonSpan);
}

void BeginAccessGroupNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    colonSpan = reader.ReadSpan();
}

MemberDeclarationNode::MemberDeclarationNode(const soul::ast::Span& span_) noexcept : CompoundNode(NodeKind::memberDeclarationNode, span_)
{
}

MemberDeclarationNode::MemberDeclarationNode(const soul::ast::Span& span_, Node* attributes_, Node* declSpecifiers_, Node* memberDeclarators_, Node* semicolon_)
    noexcept :
    CompoundNode(NodeKind::memberDeclarationNode, span_), attributes(attributes_), declSpecifiers(declSpecifiers_),
    memberDeclarators(memberDeclarators_), semicolon(semicolon_)
{
}

Node* MemberDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    Node* clonedDeclSpecifiers = nullptr;
    if (declSpecifiers)
    {
        clonedDeclSpecifiers = declSpecifiers->Clone();
    }
    Node* clonedMemberDeclarators = nullptr;
    if (memberDeclarators)
    {
        clonedMemberDeclarators = memberDeclarators->Clone();
    }
    MemberDeclarationNode* clone = new MemberDeclarationNode(GetSpan(), clonedAttributes, clonedDeclSpecifiers, clonedMemberDeclarators, semicolon->Clone());
    clone->SetId(Id());
    return clone;
}

void MemberDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void MemberDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(declSpecifiers.get());
    writer.Write(memberDeclarators.get());
    writer.Write(semicolon.get());
}

void MemberDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    attributes.reset(reader.ReadNode());
    declSpecifiers.reset(reader.ReadNode());
    memberDeclarators.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

MemberDeclaratorListNode::MemberDeclaratorListNode(const soul::ast::Span& span_) noexcept : ListNode(NodeKind::memberDeclaratorListNode, span_)
{
}

Node* MemberDeclaratorListNode::Clone() const
{
    MemberDeclaratorListNode* clone = new MemberDeclaratorListNode(GetSpan());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetId(Id());
    return clone;
}

void MemberDeclaratorListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstructorNode::ConstructorNode(const soul::ast::Span& span_) noexcept : BinaryNode(NodeKind::constructorNode, span_, nullptr, nullptr)
{
}

ConstructorNode::ConstructorNode(const soul::ast::Span& span_, Node* constructorInitializer_, Node* compoundStatement_) noexcept :
    BinaryNode(NodeKind::constructorNode, span_, constructorInitializer_, compoundStatement_)
{
}

Node* ConstructorNode::Clone() const
{
    ConstructorNode* clone = new ConstructorNode(GetSpan(), Left()->Clone(), Right()->Clone());
    clone->SetId(Id());
    return clone;
}

void ConstructorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstructorInitializerNode::ConstructorInitializerNode(const soul::ast::Span& span_) noexcept :
    CompoundNode(NodeKind::constructorInitializerNode, span_), functionScope(nullptr)
{
}

ConstructorInitializerNode::ConstructorInitializerNode(const soul::ast::Span& span_, Node* memberInitializerList_) noexcept :
    CompoundNode(NodeKind::constructorInitializerNode, span_), memberInitializerListNode(memberInitializerList_), functionScope(nullptr)
{
}

void ConstructorInitializerNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(memberInitializerListNode.get());
}

void ConstructorInitializerNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    memberInitializerListNode.reset(reader.ReadNode());
}

Node* ConstructorInitializerNode::Clone() const
{
    ConstructorInitializerNode* clone = new ConstructorInitializerNode(GetSpan(), memberInitializerListNode->Clone());
    clone->SetId(Id());
    return clone;
}

void ConstructorInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConstructorInitializerNode::SetLexerPosPair(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair_) noexcept
{
    lexerPosPair = lexerPosPair_;
}

void ConstructorInitializerNode::SetMemberInitializerListNode(Node* memberInitializerListNode_) noexcept
{
    memberInitializerListNode.reset(memberInitializerListNode_);
}

MemberInitializerListNode::MemberInitializerListNode(const soul::ast::Span& span_) noexcept : ListNode(NodeKind::memberInitializerListNode, span_)
{
}

Node* MemberInitializerListNode::Clone() const
{
    MemberInitializerListNode* clone = new MemberInitializerListNode(GetSpan());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetId(Id());
    return clone;
}

void MemberInitializerListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MemberInitializerNode::MemberInitializerNode(const soul::ast::Span& span_) noexcept :
    BinaryNode(NodeKind::memberInitializerNode, span_, nullptr, nullptr)
{
}

MemberInitializerNode::MemberInitializerNode(const soul::ast::Span& span_, Node* id_, Node* initializer_) noexcept :
    BinaryNode(NodeKind::memberInitializerNode, span_, id_, initializer_)
{
}

Node* MemberInitializerNode::Clone() const
{
    MemberInitializerNode* clone = new MemberInitializerNode(GetSpan(), Left()->Clone(), Right()->Clone());
    clone->SetId(Id());
    return clone;
}

void MemberInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VirtSpecifierSequenceNode::VirtSpecifierSequenceNode(const soul::ast::Span& span_) noexcept : SequenceNode(NodeKind::virtSpecifierSequenceNode, span_)
{
}

Node* VirtSpecifierSequenceNode::Clone() const
{
    VirtSpecifierSequenceNode* clone = new VirtSpecifierSequenceNode(GetSpan());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetId(Id());
    return clone;
}

void VirtSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ClassNode::ClassNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::classNode, span_)
{
}

Node* ClassNode::Clone() const
{
    ClassNode* clone = new ClassNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void ClassNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StructNode::StructNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::structNode, span_)
{
}

Node* StructNode::Clone() const
{
    StructNode* clone = new StructNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void StructNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UnionNode::UnionNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::unionNode, span_)
{
}

Node* UnionNode::Clone() const
{
    UnionNode* clone = new UnionNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void UnionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PublicNode::PublicNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::publicNode, span_)
{
}

Node* PublicNode::Clone() const
{
    PublicNode* clone = new PublicNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void PublicNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ProtectedNode::ProtectedNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::protectedNode, span_)
{
}

Node* ProtectedNode::Clone() const
{
    ProtectedNode* clone = new ProtectedNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void ProtectedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PrivateNode::PrivateNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::privateNode, span_)
{
}

Node* PrivateNode::Clone() const
{
    PrivateNode* clone = new PrivateNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void PrivateNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VirtualNode::VirtualNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::virtualNode, span_)
{
}

Node* VirtualNode::Clone() const
{
    VirtualNode* clone = new VirtualNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void VirtualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OverrideNode::OverrideNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::overrideNode, span_)
{
}

Node* OverrideNode::Clone() const
{
    OverrideNode* clone = new OverrideNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void OverrideNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FinalNode::FinalNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::finalNode, span_)
{
}

Node* FinalNode::Clone() const
{
    FinalNode* clone = new FinalNode(GetSpan());
    clone->SetId(Id());
    return clone;
}

void FinalNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PureSpecifierNode::PureSpecifierNode(const soul::ast::Span& span_) noexcept : Node(NodeKind::pureSpecifierNode, span_)
{
}

PureSpecifierNode::PureSpecifierNode(const soul::ast::Span& span_, const soul::ast::Span& zeroSpan_) noexcept :
    Node(NodeKind::pureSpecifierNode, span_), zeroSpan(zeroSpan_)
{
}

Node* PureSpecifierNode::Clone() const
{
    PureSpecifierNode* clone = new PureSpecifierNode(GetSpan(), zeroSpan);
    clone->SetId(Id());
    return clone;
}

void PureSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PureSpecifierNode::Write(Writer& writer)
{
    Node::Write(writer);
    writer.Write(zeroSpan);
}

void PureSpecifierNode::Read(Reader& reader)
{
    Node::Read(reader);
    zeroSpan = reader.ReadSpan();
}

} // namespace otava::ast
