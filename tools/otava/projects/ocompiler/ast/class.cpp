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

Node* ClassSpecifierNode::Clone() const
{
    ClassSpecifierNode* clone = new ClassSpecifierNode(GetSourcePos(), classHead->Clone());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
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

Node* BaseClauseNode::Clone() const
{
    BaseClauseNode* clone = new BaseClauseNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void BaseClauseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

BaseSpecifierListNode::BaseSpecifierListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::baseSpecifierListNode, sourcePos_)
{
}

Node* BaseSpecifierListNode::Clone() const
{
    BaseSpecifierListNode* clone = new BaseSpecifierListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* BeginAccessGroupNode::Clone() const
{
    BeginAccessGroupNode* clone = new BeginAccessGroupNode(GetSourcePos(), Child()->Clone(), colonPos);
    return clone;
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
    MemberDeclarationNode* clone = new MemberDeclarationNode(GetSourcePos(), clonedAttributes, clonedDeclSpecifiers, clonedMemberDeclarators, semicolon->Clone());
    return clone;
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

Node* MemberDeclaratorListNode::Clone() const
{
    MemberDeclaratorListNode* clone = new MemberDeclaratorListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* ConstructorNode::Clone() const
{
    ConstructorNode* clone = new ConstructorNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
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

Node* ConstructorInitializerNode::Clone() const
{
    ConstructorInitializerNode* clone = new ConstructorInitializerNode(GetSourcePos(), memberInitializerListNode->Clone());
    return clone;
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

Node* MemberInitializerListNode::Clone() const
{
    MemberInitializerListNode* clone = new MemberInitializerListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* MemberInitializerNode::Clone() const
{
    MemberInitializerNode* clone = new MemberInitializerNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void MemberInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VirtSpecifierSequenceNode::VirtSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::virtSpecifierSequenceNode, sourcePos_)
{
}

Node* VirtSpecifierSequenceNode::Clone() const
{
    VirtSpecifierSequenceNode* clone = new VirtSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void VirtSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ClassNode::ClassNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::classNode, sourcePos_)
{
}

Node* ClassNode::Clone() const
{
    ClassNode* clone = new ClassNode(GetSourcePos());
    return clone;
}

void ClassNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StructNode::StructNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::structNode, sourcePos_)
{
}

Node* StructNode::Clone() const
{
    StructNode* clone = new StructNode(GetSourcePos());
    return clone;
}

void StructNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UnionNode::UnionNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::unionNode, sourcePos_)
{
}

Node* UnionNode::Clone() const
{
    UnionNode* clone = new UnionNode(GetSourcePos());
    return clone;
}

void UnionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PublicNode::PublicNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::publicNode, sourcePos_)
{
}

Node* PublicNode::Clone() const
{
    PublicNode* clone = new PublicNode(GetSourcePos());
    return clone;
}

void PublicNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ProtectedNode::ProtectedNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::protectedNode, sourcePos_)
{
}

Node* ProtectedNode::Clone() const
{
    ProtectedNode* clone = new ProtectedNode(GetSourcePos());
    return clone;
}

void ProtectedNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PrivateNode::PrivateNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::privateNode, sourcePos_)
{
}

Node* PrivateNode::Clone() const
{
    PrivateNode* clone = new PrivateNode(GetSourcePos());
    return clone;
}

void PrivateNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

VirtualNode::VirtualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::virtualNode, sourcePos_)
{
}

Node* VirtualNode::Clone() const
{
    VirtualNode* clone = new VirtualNode(GetSourcePos());
    return clone;
}

void VirtualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OverrideNode::OverrideNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::overrideNode, sourcePos_)
{
}

Node* OverrideNode::Clone() const
{
    OverrideNode* clone = new OverrideNode(GetSourcePos());
    return clone;
}

void OverrideNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FinalNode::FinalNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::finalNode, sourcePos_)
{
}

Node* FinalNode::Clone() const
{
    FinalNode* clone = new FinalNode(GetSourcePos());
    return clone;
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

Node* PureSpecifierNode::Clone() const
{
    PureSpecifierNode* clone = new PureSpecifierNode(GetSourcePos(), zeroPos);
    return clone;
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
