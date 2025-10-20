// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.classes;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;
import otava.ast.function;

namespace otava::ast {

ClassSpecifierNode::ClassSpecifierNode(const soul::ast::SourcePos& sourcePos_) :
    SequenceNode(NodeKind::classSpecifierNode, sourcePos_), complete(false)
{
}

ClassSpecifierNode::ClassSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* classHead_) :
    SequenceNode(NodeKind::classSpecifierNode, sourcePos_), classHead(classHead_), complete(false)
{
}

std::expected<Node*, int> ClassSpecifierNode::Clone() const
{
    ClassSpecifierNode* clone = new ClassSpecifierNode(GetSourcePos(), classHead->Clone());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> nrv = node->Clone();
        if (!nrv) return nrv;
        std::expected<bool, int> rv = clone->AddNode(*nrv);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return clone;
}

void ClassSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ClassSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = SequenceNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(classHead.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    rv = writer.GetBinaryStreamWriter().Write(complete);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = SequenceNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    classHead.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    std::expected<bool, int> brv = reader.GetBinaryStreamReader().ReadBool();
    if (!brv) return brv;
    complete = *brv;
    return std::expected<bool, int>(true);
}

ClassHeadNode::ClassHeadNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::classHeadNode, sourcePos_)
{
}

ClassHeadNode::ClassHeadNode(const soul::ast::SourcePos& sourcePos_, Node* classKey_, Node* classHeadName_, Node* classVirtSpecifier_, Node* baseClause_, Node* attributes_) :
    CompoundNode(NodeKind::classHeadNode, sourcePos_), classKey(classKey_), classHeadName(classHeadName_), classVirtSpecifier(classVirtSpecifier_), baseClause(baseClause_), attributes(attributes_)
{
}

std::expected<Node*, int> ClassHeadNode::Clone() const
{
    Node* clonedClassVirtSpecifiers = nullptr;
    if (classVirtSpecifier)
    {
        std::expected<Node*, int> crv = classVirtSpecifier->Clone();
        if (!crv) return crv;
        clonedClassVirtSpecifiers = *crv;
    }
    Node* clonedBaseClause = nullptr;
    if (baseClause)
    {
        std::expected<Node*, int> crv = baseClause->Clone();
        if (!crv) return crv;
        clonedBaseClause = *crv;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> crv = attributes->Clone();
        if (!crv) return crv;
        clonedAttributes = *crv;
    }
    ClassHeadNode* clone = new ClassHeadNode(GetSourcePos(), classKey->Clone(), classHeadName->Clone(), clonedClassVirtSpecifiers, clonedBaseClause, clonedAttributes);
    return clone;
}

void ClassHeadNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ClassHeadNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(classKey.get());
    if (!rv) return rv;
    rv = writer.Write(classHeadName.get());
    if (!rv) return rv;
    rv = writer.Write(classVirtSpecifier.get());
    if (!rv) return rv;
    rv = writer.Write(baseClause.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ClassHeadNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    classKey.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    classHeadName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    classVirtSpecifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    baseClause.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

BaseClauseNode::BaseClauseNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::baseClauseNode, sourcePos_, nullptr)
{
}

BaseClauseNode::BaseClauseNode(const soul::ast::SourcePos& sourcePos_, Node* baseSpecifierList_) : UnaryNode(NodeKind::baseClauseNode, sourcePos_, baseSpecifierList_)
{
}

std::expected<Node*, int> BaseClauseNode::Clone() const
{
    std::expected<Node*, int> crv = Child()->Clone();
    if (!crv) return crv;
    BaseClauseNode* clone = new BaseClauseNode(GetSourcePos(), *crv);
    return std::expected<Node*, int>(clone);
}

void BaseClauseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BaseSpecifierListNode::BaseSpecifierListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::baseSpecifierListNode, sourcePos_)
{
}

std::expected<Node*, int> BaseSpecifierListNode::Clone() const
{
    BaseSpecifierListNode* clone = new BaseSpecifierListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> crv = node->Clone();
        if (!crv) return crv;
        std::expected<bool, int> rv = clone->AddNode(*crv);
    }
    return std::expected<Node*, int>(clone);
}

void BaseSpecifierListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BaseSpecifierNode::BaseSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::baseSpecifierNode, sourcePos_), virtualFirst(false)
{
}

BaseSpecifierNode::BaseSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* classOrDeclType_, Node* accessSpecifier_, Node* virtualSpecifier_, Node* attributes_, bool virtualFirst_) :
    CompoundNode(NodeKind::baseSpecifierNode, sourcePos_), classOrDeclType(classOrDeclType_), accessSpecifier(accessSpecifier_), virtualSpecifier(virtualSpecifier_), attributes(attributes_),
    virtualFirst(virtualFirst_)
{
}

std::expected<Node*, int> BaseSpecifierNode::Clone() const
{
    Node* clonedAccessSpecifier = nullptr;
    if (accessSpecifier)
    {
        std::expected<Node*, int> crv = accessSpecifier->Clone();
        if (!crv) return crv;
        clonedAccessSpecifier = *crv;
    }
    Node* clonedVirtualSpecifier = nullptr;
    if (virtualSpecifier)
    {
        std::expected<Node*, int> crv = virtualSpecifier->Clone();
        if (!crv) return crv;
        clonedVirtualSpecifier = *crv;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> crv = attributes->Clone();
        if (!crv) return crv;
        clonedAttributes = *crv;
    }
    BaseSpecifierNode* clone = new BaseSpecifierNode(GetSourcePos(), classOrDeclType->Clone(), clonedAccessSpecifier, clonedVirtualSpecifier, clonedAttributes, virtualFirst);
    return clone;
}

void BaseSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BaseSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(classOrDeclType.get());
    if (!rv) return rv;
    rv = writer.Write(accessSpecifier.get());
    if (!rv) return rv;
    rv = writer.Write(virtualSpecifier.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(virtualFirst);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BaseSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    classOrDeclType.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    accessSpecifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    virtualSpecifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    rv = reader.ReadBool();
    if (!rv) return rv;
    virtualFirst = *rv;
    return std::expected<bool, int>(true);
}

BeginAccessGroupNode::BeginAccessGroupNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::beginAccessGroupNode, sourcePos_, nullptr)
{
}

BeginAccessGroupNode::BeginAccessGroupNode(const soul::ast::SourcePos& sourcePos_, Node* accessSpecifier_, const soul::ast::SourcePos& colonPos_) :
    UnaryNode(NodeKind::beginAccessGroupNode, sourcePos_, accessSpecifier_), colonPos(colonPos_)
{
}

std::expected<Node*, int> BeginAccessGroupNode::Clone() const
{
    std::expected<Node*, int> crv = Child()->Clone();
    if (!crv) return crv;
    BeginAccessGroupNode* clone = new BeginAccessGroupNode(GetSourcePos(), *crv, colonPos);
    return std::expected<Node*, int>(clone);
}

void BeginAccessGroupNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BeginAccessGroupNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(colonPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BeginAccessGroupNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    colonPos = *posRv;
    return std::expected<bool, int>(true);
}

MemberDeclarationNode::MemberDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::memberDeclarationNode, sourcePos_)
{
}

MemberDeclarationNode::MemberDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* declSpecifiers_, Node* memberDeclarators_, Node* semicolon_) :
    CompoundNode(NodeKind::memberDeclarationNode, sourcePos_), attributes(attributes_), declSpecifiers(declSpecifiers_), memberDeclarators(memberDeclarators_), semicolon(semicolon_)
{
}

std::expected<Node*, int> MemberDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> crv = attributes->Clone();
        if (!crv) return crv;
        clonedAttributes = *crv;
    }
    Node* clonedDeclSpecifiers = nullptr;
    if (declSpecifiers)
    {
        std::expected<Node*, int> crv = declSpecifiers->Clone();
        if (!crv) return crv;
        clonedDeclSpecifiers = *crv;
    }
    Node* clonedMemberDeclarators = nullptr;
    if (memberDeclarators)
    {
        std::expected<Node*, int> crv = memberDeclarators->Clone();
        if (!crv) return crv;
        clonedMemberDeclarators = *crv;
    }
    std::expected<Node*, int> crv = semicolon->Clone();
    if (!crv) return crv;
    MemberDeclarationNode* clone = new MemberDeclarationNode(GetSourcePos(), clonedAttributes, clonedDeclSpecifiers, clonedMemberDeclarators, *crv);
    return std::expected<Node*, int>(clone);
}

void MemberDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> MemberDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(declSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(memberDeclarators.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MemberDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    memberDeclarators.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

MemberDeclaratorListNode::MemberDeclaratorListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::memberDeclaratorListNode, sourcePos_)
{
}

std::expected<Node*, int> MemberDeclaratorListNode::Clone() const
{
    MemberDeclaratorListNode* clone = new MemberDeclaratorListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> crv = node->Clone();
        if (!crv) return crv;
        std::expected<bool, int> rv = clone->AddNode(*crv);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void MemberDeclaratorListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstructorNode::ConstructorNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::constructorNode, sourcePos_, nullptr, nullptr)
{
}

ConstructorNode::ConstructorNode(const soul::ast::SourcePos& sourcePos_, Node* constructorInitializer_, Node* compoundStatement_) :
    BinaryNode(NodeKind::constructorNode, sourcePos_, constructorInitializer_, compoundStatement_)
{
}

std::expected<Node*, int> ConstructorNode::Clone() const
{
    std::expected<Node*, int> lrv = Left()->Clone();
    if (!lrv) return lrv;
    std::expected<Node*, int> rrv = Right()->Clone();
    if (!rrv) return rrv;
    ConstructorNode* clone = new ConstructorNode(GetSourcePos(), *lrv, *rrv);
    return std::expected<Node*, int>(clone);
}

void ConstructorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstructorInitializerNode::ConstructorInitializerNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::constructorInitializerNode, sourcePos_), functionScope(nullptr)
{
}

ConstructorInitializerNode::ConstructorInitializerNode(const soul::ast::SourcePos& sourcePos_, Node* memberInitializerList_) :
    CompoundNode(NodeKind::constructorInitializerNode, sourcePos_), memberInitializerListNode(memberInitializerList_), functionScope(nullptr)
{
}

std::expected<bool, int>  ConstructorInitializerNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(memberInitializerListNode.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConstructorInitializerNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    memberInitializerListNode.reset(*nrv);
    return std::expected<bool, int>(true);
}

std::expected<Node*, int> ConstructorInitializerNode::Clone() const
{
    std::expected<Node*, int> crv = memberInitializerListNode->Clone();
    if (!crv) return crv;
    ConstructorInitializerNode* clone = new ConstructorInitializerNode(GetSourcePos(), *crv);
    return std::expected<Node*, int>(clone);
}

void ConstructorInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConstructorInitializerNode::SetLexerPosPair(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair_)
{
    lexerPosPair = lexerPosPair_;
}

void ConstructorInitializerNode::SetMemberInitializerListNode(Node* memberInitializerListNode_)
{
    memberInitializerListNode.reset(memberInitializerListNode_);
}

MemberInitializerListNode::MemberInitializerListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::memberInitializerListNode, sourcePos_)
{
}

std::expected<Node*, int> MemberInitializerListNode::Clone() const
{
    MemberInitializerListNode* clone = new MemberInitializerListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> crv = node->Clone();
        if (!crv) return crv;
        std::expected<bool, int> rv = clone->AddNode(*crv);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void MemberInitializerListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MemberInitializerNode::MemberInitializerNode(const soul::ast::SourcePos& sourcePos_) :
    BinaryNode(NodeKind::memberInitializerNode, sourcePos_, nullptr, nullptr)
{
}

MemberInitializerNode::MemberInitializerNode(const soul::ast::SourcePos& sourcePos_, Node* id_, Node* initializer_) :
    BinaryNode(NodeKind::memberInitializerNode, sourcePos_, id_, initializer_)
{
}

std::expected<Node*, int> MemberInitializerNode::Clone() const
{
    std::expected<Node*, int> lrv = Left()->Clone();
    if (!lrv) return lrv;
    std::expected<Node*, int> rrv = Right()->Clone();
    if (!rrv) return rrv;
    MemberInitializerNode* clone = new MemberInitializerNode(GetSourcePos(), *lrv, *rrv);
    return std::expected<Node*, int>(clone);
}

void MemberInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VirtSpecifierSequenceNode::VirtSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::virtSpecifierSequenceNode, sourcePos_)
{
}

std::expected<Node*, int> VirtSpecifierSequenceNode::Clone() const
{
    VirtSpecifierSequenceNode* clone = new VirtSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> crv = node->Clone();
        if (!crv) return crv;
        std::expected<bool, int> rv = clone->AddNode(*crv);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void VirtSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ClassNode::ClassNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::classNode, sourcePos_)
{
}

std::expected<Node*, int> ClassNode::Clone() const
{
    ClassNode* clone = new ClassNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ClassNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StructNode::StructNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::structNode, sourcePos_)
{
}

std::expected<Node*, int> StructNode::Clone() const
{
    StructNode* clone = new StructNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void StructNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UnionNode::UnionNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::unionNode, sourcePos_)
{
}

std::expected<Node*, int>UnionNode::Clone() const
{
    UnionNode* clone = new UnionNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void UnionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PublicNode::PublicNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::publicNode, sourcePos_)
{
}

std::expected<Node*, int> PublicNode::Clone() const
{
    PublicNode* clone = new PublicNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void PublicNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ProtectedNode::ProtectedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::protectedNode, sourcePos_)
{
}

std::expected<Node*, int> ProtectedNode::Clone() const
{
    ProtectedNode* clone = new ProtectedNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ProtectedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PrivateNode::PrivateNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::privateNode, sourcePos_)
{
}

std::expected<Node*, int> PrivateNode::Clone() const
{
    PrivateNode* clone = new PrivateNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void PrivateNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VirtualNode::VirtualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::virtualNode, sourcePos_)
{
}

std::expected<Node*, int> VirtualNode::Clone() const
{
    VirtualNode* clone = new VirtualNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void VirtualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OverrideNode::OverrideNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::overrideNode, sourcePos_)
{
}

std::expected<Node*, int> OverrideNode::Clone() const
{
    OverrideNode* clone = new OverrideNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void OverrideNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FinalNode::FinalNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::finalNode, sourcePos_)
{
}

std::expected<Node*, int> FinalNode::Clone() const
{
    FinalNode* clone = new FinalNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void FinalNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PureSpecifierNode::PureSpecifierNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::pureSpecifierNode, sourcePos_)
{
}

PureSpecifierNode::PureSpecifierNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& zeroPos_) : Node(NodeKind::pureSpecifierNode, sourcePos_), zeroPos(zeroPos_)
{
}

std::expected<Node*, int> PureSpecifierNode::Clone() const
{
    PureSpecifierNode* clone = new PureSpecifierNode(GetSourcePos(), zeroPos);
    return std::expected<Node*, int>(clone);
}

void PureSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int>  PureSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = Node::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(zeroPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> PureSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = Node::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    zeroPos = *posRv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
