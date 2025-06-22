// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.declaration;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

DeclarationSequenceNode::DeclarationSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::declarationSequenceNode, sourcePos_)
{
}

Node* DeclarationSequenceNode::Clone() const
{
    DeclarationSequenceNode* clone = new DeclarationSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void DeclarationSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SimpleDeclarationNode::SimpleDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::simpleDeclarationNode, sourcePos_)
{
}

SimpleDeclarationNode::SimpleDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* declarationSpecifiers_, Node* initDeclaratorList_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::simpleDeclarationNode, sourcePos_), declarationSpecifiers(declarationSpecifiers_), initDeclaratorList(initDeclaratorList_), attributes(attributes_), semicolon(semicolon_)
{
}

Node* SimpleDeclarationNode::Clone() const
{
    Node* clonedDeclSpecifiers = nullptr;
    if (declarationSpecifiers)
    {
        clonedDeclSpecifiers = declarationSpecifiers->Clone();
    }
    Node* clonedInitDeclaratorList = nullptr;
    if (initDeclaratorList)
    {
        clonedInitDeclaratorList = initDeclaratorList->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    SimpleDeclarationNode* clone = new SimpleDeclarationNode(GetSourcePos(), clonedDeclSpecifiers, clonedInitDeclaratorList, clonedAttributes, semicolon->Clone());
    return clone;
}

void SimpleDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SimpleDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declarationSpecifiers.get());
    writer.Write(initDeclaratorList.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

void SimpleDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declarationSpecifiers.reset(reader.ReadNode());
    initDeclaratorList.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

AsmDeclarationNode::AsmDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::asmDeclarationNode, sourcePos_)
{
}

AsmDeclarationNode::AsmDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* asm__, Node* asmText_, Node* semicolon_, Node* attributes_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::asmDeclarationNode, sourcePos_), asm_(asm__), asmText(asmText_), semicolon(semicolon_), attributes(attributes_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* AsmDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    AsmDeclarationNode* clone = new AsmDeclarationNode(GetSourcePos(), asm_->Clone(), asmText->Clone(), semicolon->Clone(), clonedAttributes, lpPos, rpPos);
    return clone;
}

void AsmDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AsmDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(asm_.get());
    writer.Write(asmText.get());
    writer.Write(semicolon.get());
    writer.Write(attributes.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void AsmDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    asm_.reset(reader.ReadNode());
    asmText.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

AsmNode::AsmNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::asmNode, sourcePos_)
{
}

Node* AsmNode::Clone() const
{
    AsmNode* clone = new AsmNode(GetSourcePos());
    return clone;
}

void AsmNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LinkageSpecificationNode::LinkageSpecificationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::linkageSpecificationNode, sourcePos_)
{
}

LinkageSpecificationNode::LinkageSpecificationNode(const soul::ast::SourcePos& sourcePos_, Node* extrn_, Node* linkage_, Node* declarations_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::linkageSpecificationNode, sourcePos_), extrn(extrn_), linkage(linkage_), declarations(declarations_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* LinkageSpecificationNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        clonedDeclarations = declarations->Clone();
    }
    LinkageSpecificationNode* clone = new LinkageSpecificationNode(GetSourcePos(), extrn->Clone(), linkage->Clone(), clonedDeclarations, lbPos, rbPos);
    return clone;
}

void LinkageSpecificationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void LinkageSpecificationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(extrn.get());
    writer.Write(linkage.get());
    writer.Write(declarations.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void LinkageSpecificationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    extrn.reset(reader.ReadNode());
    linkage.reset(reader.ReadNode());
    declarations.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

NamespaceDefinitionNode::NamespaceDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::namespaceDefinitionNode, sourcePos_)
{
}

NamespaceDefinitionNode::NamespaceDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* nskw_, Node* nsName_, Node* nsBody_, Node* inln_, Node* attributes_,
    const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::namespaceDefinitionNode, sourcePos_), nskw(nskw_), nsName(nsName_), nsBody(nsBody_), inln(inln_), attributes(attributes_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* NamespaceDefinitionNode::Clone() const
{
    Node* clonedNsName = nullptr;
    if (nsName)
    {
        clonedNsName = nsName->Clone();
    }
    Node* clonedInline = nullptr;
    if (inln)
    {
        clonedNsName = inln->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    NamespaceDefinitionNode* clone = new NamespaceDefinitionNode(GetSourcePos(), nskw->Clone(), clonedNsName, nsBody->Clone(), clonedInline, clonedAttributes, lbPos, rbPos);
    return clone;
}

void NamespaceDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NamespaceDefinitionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(nskw.get());
    writer.Write(nsName.get());
    writer.Write(nsBody.get());
    writer.Write(inln.get());
    writer.Write(attributes.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void NamespaceDefinitionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    nskw.reset(reader.ReadNode());
    nsName.reset(reader.ReadNode());
    nsBody.reset(reader.ReadNode());
    inln.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

NamespaceBodyNode::NamespaceBodyNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::namespaceBodyNode, sourcePos_)
{
}

NamespaceBodyNode::NamespaceBodyNode(const soul::ast::SourcePos& sourcePos_, Node* declarations_) : CompoundNode(NodeKind::namespaceBodyNode, sourcePos_), declarations(declarations_)
{
}

Node* NamespaceBodyNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        clonedDeclarations = declarations->Clone();
    }
    NamespaceBodyNode* clone = new NamespaceBodyNode(GetSourcePos(), clonedDeclarations);
    return clone;
}

void NamespaceBodyNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NamespaceBodyNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declarations.get());
}

void NamespaceBodyNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declarations.reset(reader.ReadNode());
}

NamespaceAliasDefinitionNode::NamespaceAliasDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::namespaceAliasDefinitionNode, sourcePos_)
{
}

NamespaceAliasDefinitionNode::NamespaceAliasDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* id_, Node* assign_, Node* qns_, Node* semicolon_) :
    CompoundNode(NodeKind::namespaceAliasDefinitionNode, sourcePos_), id(id_), assign(assign_), qns(qns_), semicolon(semicolon_)
{
}

Node* NamespaceAliasDefinitionNode::Clone() const
{
    NamespaceAliasDefinitionNode* clone = new NamespaceAliasDefinitionNode(GetSourcePos(), id->Clone(), assign->Clone(), qns->Clone(), semicolon->Clone());
    return clone;
}

void NamespaceAliasDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NamespaceAliasDefinitionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(id.get());
    writer.Write(assign.get());
    writer.Write(qns.get());
    writer.Write(semicolon.get());
}

void NamespaceAliasDefinitionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    id.reset(reader.ReadNode());
    assign.reset(reader.ReadNode());
    qns.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

UsingDeclarationNode::UsingDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::usingDeclarationNode, sourcePos_)
{
}

UsingDeclarationNode::UsingDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* declarators_, Node* semicolon_) :
    CompoundNode(NodeKind::usingDeclarationNode, sourcePos_), usng(usng_), declarators(declarators_), semicolon(semicolon_)
{
}

Node* UsingDeclarationNode::Clone() const
{
    UsingDeclarationNode* clone = new UsingDeclarationNode(GetSourcePos(), usng->Clone(), declarators->Clone(), semicolon->Clone());
    return clone;
}

void UsingDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void UsingDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(usng.get());
    writer.Write(declarators.get());
    writer.Write(semicolon.get());
}

void UsingDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    usng.reset(reader.ReadNode());
    declarators.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

UsingNode::UsingNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::usingNode, sourcePos_)
{
}

Node* UsingNode::Clone() const
{
    UsingNode* clone = new UsingNode(GetSourcePos());
    return clone;
}

void UsingNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UsingDeclaratorListNode::UsingDeclaratorListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::usingDeclaratorListNode, sourcePos_)
{
}

Node* UsingDeclaratorListNode::Clone() const
{
    UsingDeclaratorListNode* clone = new UsingDeclaratorListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void UsingDeclaratorListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UsingEnumDeclarationNode::UsingEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::usingEnumDeclarationNode, sourcePos_)
{
}

UsingEnumDeclarationNode::UsingEnumDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* ees_, Node* semicolon_) :
    CompoundNode(NodeKind::usingEnumDeclarationNode, sourcePos_), usng(usng_), ees(ees_), semicolon(semicolon_)
{
}

Node* UsingEnumDeclarationNode::Clone() const
{
    UsingEnumDeclarationNode* clone = new UsingEnumDeclarationNode(GetSourcePos(), usng->Clone(), ees->Clone(), semicolon->Clone());
    return clone;
}

void UsingEnumDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void UsingEnumDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(usng.get());
    writer.Write(ees.get());
    writer.Write(semicolon.get());
}

void UsingEnumDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    usng.reset(reader.ReadNode());
    ees.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

UsingDirectiveNode::UsingDirectiveNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::usingDirectiveNode, sourcePos_)
{
}

UsingDirectiveNode::UsingDirectiveNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* nskw_, Node* id_, Node* semicolon_, Node* attributes_) :
    CompoundNode(NodeKind::usingDirectiveNode, sourcePos_), usng(usng_), nskw(nskw_), id(id_), semicolon(semicolon_), attributes(attributes_)
{
}

Node* UsingDirectiveNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    UsingDirectiveNode* clone = new UsingDirectiveNode(GetSourcePos(), usng->Clone(), nskw->Clone(), id->Clone(), semicolon->Clone(), clonedAttributes);
    return clone;
}

void UsingDirectiveNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void UsingDirectiveNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(usng.get());
    writer.Write(nskw.get());
    writer.Write(id.get());
    writer.Write(semicolon.get());
    writer.Write(attributes.get());
}

void UsingDirectiveNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    usng.reset(reader.ReadNode());
    nskw.reset(reader.ReadNode());
    id.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

NamespaceNode::NamespaceNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::namespaceNode, sourcePos_)
{
}

Node* NamespaceNode::Clone() const
{
    NamespaceNode* clone = new NamespaceNode(GetSourcePos());
    return clone;
}

void NamespaceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StaticAssertDeclarationNode::StaticAssertDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::staticAssertDeclarationNode, sourcePos_)
{
}

StaticAssertDeclarationNode::StaticAssertDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* staticAssert_, Node* constantExpr_, Node* comma_, Node* stringLiteral_, Node* semicolon_,
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos rpPos_) :
    CompoundNode(NodeKind::staticAssertDeclarationNode, sourcePos_), staticAssert(staticAssert_), constantExpr(constantExpr_), comma(comma_), stringLiteral(stringLiteral_), semicolon(semicolon_),
    lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* StaticAssertDeclarationNode::Clone() const
{
    Node* clonedComma = nullptr;
    if (comma)
    {
        clonedComma = comma->Clone();
    }
    Node* clonedStringLiteral = nullptr;
    if (stringLiteral)
    {
        clonedStringLiteral = stringLiteral->Clone();
    }
    StaticAssertDeclarationNode* clone = new StaticAssertDeclarationNode(GetSourcePos(), staticAssert->Clone(), constantExpr->Clone(), clonedComma, clonedStringLiteral, 
        semicolon->Clone(), lpPos, rpPos);
    return clone;
}

void StaticAssertDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void StaticAssertDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(staticAssert.get());
    writer.Write(constantExpr.get());
    writer.Write(comma.get());
    writer.Write(stringLiteral.get());
    writer.Write(semicolon.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void StaticAssertDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    staticAssert.reset(reader.ReadNode());
    constantExpr.reset(reader.ReadNode());
    comma.reset(reader.ReadNode());
    stringLiteral.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

StaticAssertNode::StaticAssertNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::staticAssertNode, sourcePos_)
{
}

Node* StaticAssertNode::Clone() const
{
    StaticAssertNode* clone = new StaticAssertNode(GetSourcePos());
    return clone;
}

void StaticAssertNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AliasDeclarationNode::AliasDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::aliasDeclarationNode, sourcePos_)
{
}

AliasDeclarationNode::AliasDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* identifier_, Node* assign_, Node* definingTypeId_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::aliasDeclarationNode, sourcePos_), usng(usng_), identifier(identifier_), assign(assign_), definingTypeId(definingTypeId_), attributes(attributes_), semicolon(semicolon_)
{
}

Node* AliasDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    AliasDeclarationNode* clone = new AliasDeclarationNode(GetSourcePos(), usng->Clone(), identifier->Clone(), assign->Clone(), definingTypeId->Clone(), clonedAttributes, semicolon->Clone());
    return clone;
}

void AliasDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AliasDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(usng.get());
    writer.Write(identifier.get());
    writer.Write(assign.get());
    writer.Write(definingTypeId.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

void AliasDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    usng.reset(reader.ReadNode());
    identifier.reset(reader.ReadNode());
    assign.reset(reader.ReadNode());
    definingTypeId.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

EmptyDeclarationNode::EmptyDeclarationNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::emptyDeclarationNode, sourcePos_)
{
}

Node* EmptyDeclarationNode::Clone() const
{
    EmptyDeclarationNode* clone = new EmptyDeclarationNode(GetSourcePos());
    return clone;
}

void EmptyDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AttributeDeclarationNode::AttributeDeclarationNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::attributeDeclarationNode, sourcePos_, nullptr, nullptr)
{
}

AttributeDeclarationNode::AttributeDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_) :
    BinaryNode(NodeKind::attributeDeclarationNode, sourcePos_, attributes_, semicolon_)
{
}

Node* AttributeDeclarationNode::Clone() const
{
    AttributeDeclarationNode* clone = new AttributeDeclarationNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void AttributeDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InitDeclaratorListNode::InitDeclaratorListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::initDeclaratorListNode, sourcePos_)
{
}

Node* InitDeclaratorListNode::Clone() const
{
    InitDeclaratorListNode* clone = new InitDeclaratorListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void InitDeclaratorListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InitDeclaratorNode::InitDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::initDeclaratorNode, sourcePos_, nullptr, nullptr)
{
}

InitDeclaratorNode::InitDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, Node* init_) : 
    BinaryNode(NodeKind::initDeclaratorNode, sourcePos_, declarator_, init_)
{
}

Node* InitDeclaratorNode::Clone() const
{
    InitDeclaratorNode* clone = new InitDeclaratorNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void InitDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TrailingFunctionDeclaratorNode::TrailingFunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::trailingFunctionDeclaratorNode, sourcePos_)
{
}

TrailingFunctionDeclaratorNode::TrailingFunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, Node* params_, Node* trailingReturnType_) :
    CompoundNode(NodeKind::trailingFunctionDeclaratorNode, sourcePos_), declarator(declarator_), params(params_), trailingReturnType(trailingReturnType_)
{
}

Node* TrailingFunctionDeclaratorNode::Clone() const
{
    TrailingFunctionDeclaratorNode* clone = new TrailingFunctionDeclaratorNode(GetSourcePos(), declarator->Clone(), params->Clone(), trailingReturnType->Clone());
    return clone;
}

void TrailingFunctionDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TrailingFunctionDeclaratorNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declarator.get());
    writer.Write(params.get());
    writer.Write(trailingReturnType.get());
}

void TrailingFunctionDeclaratorNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declarator.reset(reader.ReadNode());
    params.reset(reader.ReadNode());
    trailingReturnType.reset(reader.ReadNode());
}

ParenthesizedDeclaratorNode::ParenthesizedDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::parenthesizedDeclaratorNode, sourcePos_)
{
}

ParenthesizedDeclaratorNode::ParenthesizedDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::parenthesizedDeclaratorNode, sourcePos_), declarator(declarator_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* ParenthesizedDeclaratorNode::Clone() const
{
    ParenthesizedDeclaratorNode* clone = new ParenthesizedDeclaratorNode(GetSourcePos(), declarator->Clone(), lpPos, rpPos);
    return clone;
}

void ParenthesizedDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ParenthesizedDeclaratorNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declarator.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ParenthesizedDeclaratorNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declarator.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

AbstractDeclaratorNode::AbstractDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::abstractDeclaratorNode, sourcePos_)
{
}

Node* AbstractDeclaratorNode::Clone() const
{
    AbstractDeclaratorNode* clone = new AbstractDeclaratorNode(GetSourcePos());
    return clone;
}

void AbstractDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeclSpecifierSequenceNode::DeclSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::declSpecifierSequenceNode, sourcePos_)
{
}

Node* DeclSpecifierSequenceNode::Clone() const
{
    DeclSpecifierSequenceNode* clone = new DeclSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void DeclSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FriendNode::FriendNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::friendNode, sourcePos_)
{
}

Node* FriendNode::Clone() const
{
    FriendNode* clone = new FriendNode(GetSourcePos());
    return clone;
}

void FriendNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypedefNode::TypedefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::typedefNode, sourcePos_)
{
}

Node* TypedefNode::Clone() const
{
    TypedefNode* clone = new TypedefNode(GetSourcePos());
    return clone;
}

void TypedefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstExprNode::ConstExprNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constExprNode, sourcePos_)
{
}

Node* ConstExprNode::Clone() const
{
    ConstExprNode* clone = new ConstExprNode(GetSourcePos());
    return clone;
}

void ConstExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstEvalNode::ConstEvalNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constEvalNode, sourcePos_)
{
}

Node* ConstEvalNode::Clone() const
{
    ConstEvalNode* clone = new ConstEvalNode(GetSourcePos());
    return clone;
}

void ConstEvalNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstInitNode::ConstInitNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constInitNode, sourcePos_)
{
}

Node* ConstInitNode::Clone() const
{
    ConstInitNode* clone = new ConstInitNode(GetSourcePos());
    return clone;
}

void ConstInitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InlineNode::InlineNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::inlineNode, sourcePos_)
{
}

Node* InlineNode::Clone() const
{
    InlineNode* clone = new InlineNode(GetSourcePos());
    return clone;
}

void InlineNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StaticNode::StaticNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::staticNode, sourcePos_)
{
}

Node* StaticNode::Clone() const
{
    StaticNode* clone = new StaticNode(GetSourcePos());
    return clone;
}

void StaticNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ThreadLocalNode::ThreadLocalNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::threadLocalNode, sourcePos_)
{
}

Node* ThreadLocalNode::Clone() const
{
    ThreadLocalNode* clone = new ThreadLocalNode(GetSourcePos());
    return clone;
}

void ThreadLocalNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ExternNode::ExternNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::externNode, sourcePos_)
{
}

Node* ExternNode::Clone() const
{
    ExternNode* clone = new ExternNode(GetSourcePos());
    return clone;
}

void ExternNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MutableNode::MutableNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::mutableNode, sourcePos_)
{
}

Node* MutableNode::Clone() const
{
    MutableNode* clone = new MutableNode(GetSourcePos());
    return clone;
}

void MutableNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ExplicitNode::ExplicitNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::explicitNode, sourcePos_)
{
}

Node* ExplicitNode::Clone() const
{
    ExplicitNode* clone = new ExplicitNode(GetSourcePos());
    return clone;
}

void ExplicitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConditionalExplicitNode::ConditionalExplicitNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::conditionalExplicitNode, sourcePos_, nullptr)
{
}

ConditionalExplicitNode::ConditionalExplicitNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::conditionalExplicitNode, sourcePos_, cond_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* ConditionalExplicitNode::Clone() const
{
    ConditionalExplicitNode* clone = new ConditionalExplicitNode(GetSourcePos(), cond->Clone(), lpPos, rpPos);
    return clone;
}

void ConditionalExplicitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConditionalExplicitNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(cond.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ConditionalExplicitNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    cond.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

QualifiedPtrNode::QualifiedPtrNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::qualifiedPtrNode, sourcePos_, nullptr, nullptr)
{
}

QualifiedPtrNode::QualifiedPtrNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* ptr_) :
    BinaryNode(NodeKind::qualifiedPtrNode, sourcePos_, nns_, ptr_)
{
}

Node* QualifiedPtrNode::Clone() const
{
    QualifiedPtrNode* clone = new QualifiedPtrNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void QualifiedPtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PtrOperatorNode::PtrOperatorNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::ptrOperatorNode, sourcePos_, nullptr)
{
}

PtrOperatorNode::PtrOperatorNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::ptrOperatorNode, sourcePos_, child_)
{
}

Node* PtrOperatorNode::Clone() const
{
    PtrOperatorNode* clone = new PtrOperatorNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void PtrOperatorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PtrDeclaratorNode::PtrDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::ptrDeclaratorNode, sourcePos_)
{
}

Node* PtrDeclaratorNode::Clone() const
{
    PtrDeclaratorNode* clone = new PtrDeclaratorNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void PtrDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PackDeclaratorIdNode::PackDeclaratorIdNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::packDeclaratorIdNode, sourcePos_, nullptr, nullptr)
{
}

PackDeclaratorIdNode::PackDeclaratorIdNode(const soul::ast::SourcePos& sourcePos_, Node* ellipsis_, Node* idExpr_) :
    BinaryNode(NodeKind::packDeclaratorIdNode, sourcePos_, ellipsis_, idExpr_)
{
}

Node* PackDeclaratorIdNode::Clone() const
{
    PackDeclaratorIdNode* clone = new PackDeclaratorIdNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void PackDeclaratorIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrayDeclaratorNode::ArrayDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::arrayDeclaratorNode, sourcePos_, nullptr)
{
}

ArrayDeclaratorNode::ArrayDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* dimension_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    UnaryNode(NodeKind::arrayDeclaratorNode, sourcePos_, child_), dimension(dimension_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* ArrayDeclaratorNode::Clone() const
{
    Node* clonedDimension = nullptr;
    if (dimension)
    {
        clonedDimension = dimension->Clone();
    }
    ArrayDeclaratorNode* clone = new ArrayDeclaratorNode(GetSourcePos(), Child()->Clone(), clonedDimension, lbPos, rbPos);
    return clone;
}

void ArrayDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ArrayDeclaratorNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(dimension.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void ArrayDeclaratorNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    dimension.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

FunctionDeclaratorNode::FunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::functionDeclaratorNode, sourcePos_, nullptr)
{
}

FunctionDeclaratorNode::FunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* parameters_) : 
    UnaryNode(NodeKind::functionDeclaratorNode, sourcePos_, child_), params(parameters_)
{
}

Node* FunctionDeclaratorNode::Clone() const
{
    FunctionDeclaratorNode* clone = new FunctionDeclaratorNode(GetSourcePos(), Child()->Clone(), params->Clone());
    return clone;
}

void FunctionDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionDeclaratorNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(params.get());
}

void FunctionDeclaratorNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    params.reset(reader.ReadNode());
}

PrefixNode::PrefixNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::prefixNode, sourcePos_, nullptr, nullptr)
{
}

PrefixNode::PrefixNode(const soul::ast::SourcePos& sourcePos_, Node* prefix_, Node* subject_) : BinaryNode(NodeKind::prefixNode, sourcePos_, prefix_, subject_)
{
}

Node* PrefixNode::Clone() const
{
    PrefixNode* clone = new PrefixNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void PrefixNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TrailingQualifiersNode::TrailingQualifiersNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::trailingQualifiersNode, sourcePos_)
{
}

TrailingQualifiersNode::TrailingQualifiersNode(const soul::ast::SourcePos& sourcePos_, Node* subject_) : SequenceNode(NodeKind::trailingQualifiersNode, sourcePos_), subject(subject_)
{
}

Node* TrailingQualifiersNode::Clone() const
{
    TrailingQualifiersNode* clone = new TrailingQualifiersNode(GetSourcePos(), subject->Clone());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void TrailingQualifiersNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TrailingQualifiersNode::Write(Writer& writer)
{
    SequenceNode::Write(writer);
    writer.Write(subject.get());
}

void TrailingQualifiersNode::Read(Reader& reader)
{
    SequenceNode::Read(reader);
    subject.reset(reader.ReadNode());
}

TrailingAttributesNode::TrailingAttributesNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::trailingAttributesNode, sourcePos_, nullptr, nullptr)
{
}

TrailingAttributesNode::TrailingAttributesNode(const soul::ast::SourcePos& sourcePos_, Node* left_, Node* attributes_) : BinaryNode(NodeKind::trailingAttributesNode, sourcePos_, left_, attributes_)
{
}

Node* TrailingAttributesNode::Clone() const
{
    TrailingAttributesNode* clone = new TrailingAttributesNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void TrailingAttributesNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NoexceptSpecifierNode::NoexceptSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::noexceptSpecifierNode, sourcePos_)
{
}

NoexceptSpecifierNode::NoexceptSpecifierNode(const soul::ast::SourcePos& sourcePos_, Node* constantExpr_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::noexceptSpecifierNode, sourcePos_), constantExpr(constantExpr_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* NoexceptSpecifierNode::Clone() const
{
    Node* clonedConstantExpr = nullptr;
    if (constantExpr)
    {
        clonedConstantExpr = constantExpr->Clone();
    }
    NoexceptSpecifierNode* clone = new NoexceptSpecifierNode(GetSourcePos(), clonedConstantExpr, lpPos, rpPos);
    return clone;
}

void NoexceptSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NoexceptSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(constantExpr.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void NoexceptSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    constantExpr.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

ThrowSpecifierNode::ThrowSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::throwSpecifierNode, sourcePos_)
{
}

ThrowSpecifierNode::ThrowSpecifierNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::throwSpecifierNode, sourcePos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* ThrowSpecifierNode::Clone() const
{
    ThrowSpecifierNode* clone = new ThrowSpecifierNode(GetSourcePos(), lpPos, rpPos);
    return clone;
}

void ThrowSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ThrowSpecifierNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ThrowSpecifierNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

} // namespace otava::ast
