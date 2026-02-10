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

std::expected<Node*, int> DeclarationSequenceNode::Clone() const
{
    DeclarationSequenceNode* clone = new DeclarationSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> SimpleDeclarationNode::Clone() const
{
    Node* clonedDeclSpecifiers = nullptr;
    if (declarationSpecifiers)
    {
        std::expected<Node*, int> d = declarationSpecifiers->Clone();
        if (!d) return d;
        clonedDeclSpecifiers = *d;
    }
    Node* clonedInitDeclaratorList = nullptr;
    if (initDeclaratorList)
    {
        std::expected<Node*, int> i = initDeclaratorList->Clone();
        if (!i) return i;
        clonedInitDeclaratorList = *i;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    SimpleDeclarationNode* clone = new SimpleDeclarationNode(GetSourcePos(), clonedDeclSpecifiers, clonedInitDeclaratorList, clonedAttributes, *sc);
    return std::expected<Node*, int>(clone);
}

void SimpleDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int>  SimpleDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declarationSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(initDeclaratorList.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SimpleDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarationSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initDeclaratorList.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

AsmDeclarationNode::AsmDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::asmDeclarationNode, sourcePos_)
{
}

AsmDeclarationNode::AsmDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* asm__, Node* asmText_, Node* semicolon_, Node* attributes_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::asmDeclarationNode, sourcePos_), asm_(asm__), asmText(asmText_), semicolon(semicolon_), attributes(attributes_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> AsmDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> as = asm_->Clone();
    if (!as) return as;
    std::expected<Node*, int> at = asmText->Clone();
    if (!at) return at;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    AsmDeclarationNode* clone = new AsmDeclarationNode(GetSourcePos(), *as, *at, *sc, clonedAttributes, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void AsmDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> AsmDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(asm_.get());
    if (!rv) return rv;
    rv = writer.Write(asmText.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AsmDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    asm_.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    asmText.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

AsmNode::AsmNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::asmNode, sourcePos_)
{
}

std::expected<Node*, int> AsmNode::Clone() const
{
    AsmNode* clone = new AsmNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> LinkageSpecificationNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        std::expected<Node*, int> d = declarations->Clone();
        if (!d) return d;
        clonedDeclarations = *d;
    }
    std::expected<Node*, int> e = extrn->Clone();
    if (!e) return e;
    std::expected<Node*, int> l = linkage->Clone();
    if (!l) return l;
    LinkageSpecificationNode* clone = new LinkageSpecificationNode(GetSourcePos(), *e, *l, clonedDeclarations, lbPos, rbPos);
    return clone;
}

void LinkageSpecificationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LinkageSpecificationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(extrn.get());
    if (!rv) return rv;
    rv = writer.Write(linkage.get());
    if (!rv) return rv;
    rv = writer.Write(declarations.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LinkageSpecificationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    extrn.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    linkage.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarations.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

NamespaceDefinitionNode::NamespaceDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::namespaceDefinitionNode, sourcePos_)
{
}

NamespaceDefinitionNode::NamespaceDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* nskw_, Node* nsName_, Node* nsBody_, Node* inln_, Node* attributes_,
    const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::namespaceDefinitionNode, sourcePos_), nskw(nskw_), nsName(nsName_), nsBody(nsBody_), inln(inln_), attributes(attributes_), lbPos(lbPos_), rbPos(rbPos_)
{
}

std::expected<Node*, int> NamespaceDefinitionNode::Clone() const
{
    Node* clonedNsName = nullptr;
    if (nsName)
    {
        std::expected<Node*, int> n = nsName->Clone();
        if (!n) return n;
        clonedNsName = *n;
    }
    Node* clonedInline = nullptr;
    if (inln)
    {
        std::expected<Node*, int> i = inln->Clone();
        if (!i) return i;
        clonedInline = *i;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> n = nskw->Clone();
    if (!n) return n;
    std::expected<Node*, int> b = nsBody->Clone();
    if (!b) return b;
    NamespaceDefinitionNode* clone = new NamespaceDefinitionNode(GetSourcePos(), *n, clonedNsName, *b, clonedInline, clonedAttributes, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void NamespaceDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NamespaceDefinitionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(nskw.get());
    if (!rv) return rv;
    rv = writer.Write(nsName.get());
    if (!rv) return rv;
    rv = writer.Write(nsBody.get());
    if (!rv) return rv;
    rv = writer.Write(inln.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NamespaceDefinitionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    nskw.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    nsName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    nsBody.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    inln.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

NamespaceBodyNode::NamespaceBodyNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::namespaceBodyNode, sourcePos_)
{
}

NamespaceBodyNode::NamespaceBodyNode(const soul::ast::SourcePos& sourcePos_, Node* declarations_) : CompoundNode(NodeKind::namespaceBodyNode, sourcePos_), declarations(declarations_)
{
}

std::expected<Node*, int> NamespaceBodyNode::Clone() const
{
    Node* clonedDeclarations = nullptr;
    if (declarations)
    {
        std::expected<Node*, int> d = declarations->Clone();
        if (!d) return d;
        clonedDeclarations = *d;
    }
    NamespaceBodyNode* clone = new NamespaceBodyNode(GetSourcePos(), clonedDeclarations);
    return std::expected<Node*, int>(clone);
}

void NamespaceBodyNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NamespaceBodyNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declarations.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NamespaceBodyNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarations.reset(*nrv);
    return std::expected<bool, int>(true);
}

NamespaceAliasDefinitionNode::NamespaceAliasDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::namespaceAliasDefinitionNode, sourcePos_)
{
}

NamespaceAliasDefinitionNode::NamespaceAliasDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* id_, Node* assign_, Node* qns_, Node* semicolon_) :
    CompoundNode(NodeKind::namespaceAliasDefinitionNode, sourcePos_), id(id_), assign(assign_), qns(qns_), semicolon(semicolon_)
{
}

std::expected<Node*, int> NamespaceAliasDefinitionNode::Clone() const
{
    std::expected<Node*, int> i = id->Clone();
    if (!i) return i;
    std::expected<Node*, int> a = assign->Clone();
    if (!a) return a;
    std::expected<Node*, int> q = qns->Clone();
    if (!q) return q;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    NamespaceAliasDefinitionNode* clone = new NamespaceAliasDefinitionNode(GetSourcePos(), *i, *a, *q, *sc);
    return std::expected<Node*, int>(clone);
}

void NamespaceAliasDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NamespaceAliasDefinitionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(id.get());
    if (!rv) return rv;
    rv = writer.Write(assign.get());
    if (!rv) return rv;
    rv = writer.Write(qns.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NamespaceAliasDefinitionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    id.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    assign.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    qns.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

UsingDeclarationNode::UsingDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::usingDeclarationNode, sourcePos_)
{
}

UsingDeclarationNode::UsingDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* declarators_, Node* semicolon_) :
    CompoundNode(NodeKind::usingDeclarationNode, sourcePos_), usng(usng_), declarators(declarators_), semicolon(semicolon_)
{
}

std::expected<Node*, int> UsingDeclarationNode::Clone() const
{
    std::expected<Node*, int> u = usng->Clone();
    if (!u) return u;
    std::expected<Node*, int> d = declarators->Clone();
    if (!d) return d;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    UsingDeclarationNode* clone = new UsingDeclarationNode(GetSourcePos(), *u, *d, *sc);
    return clone;
}

void UsingDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> UsingDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(usng.get());
    if (!rv) return rv;
    rv = writer.Write(declarators.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> UsingDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    usng.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarators.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

UsingNode::UsingNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::usingNode, sourcePos_)
{
}

std::expected<Node*, int> UsingNode::Clone() const
{
    UsingNode* clone = new UsingNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void UsingNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

UsingDeclaratorListNode::UsingDeclaratorListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::usingDeclaratorListNode, sourcePos_)
{
}

std::expected<Node*, int> UsingDeclaratorListNode::Clone() const
{
    UsingDeclaratorListNode* clone = new UsingDeclaratorListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> c = node->Clone();
        if (!c) return c;
        std::expected<bool, int> rv = clone->AddNode(*c);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> UsingEnumDeclarationNode::Clone() const
{
    std::expected<Node*, int> u = usng->Clone();
    if (!u) return u;
    std::expected<Node*, int> e = ees->Clone();
    if (!e) return e;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    UsingEnumDeclarationNode* clone = new UsingEnumDeclarationNode(GetSourcePos(), *u, *e, *sc);
    return std::expected<Node*, int>(clone);
}

void UsingEnumDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> UsingEnumDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(usng.get());
    if (!rv) return rv;
    rv = writer.Write(ees.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> UsingEnumDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    usng.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ees.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

UsingDirectiveNode::UsingDirectiveNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::usingDirectiveNode, sourcePos_)
{
}

UsingDirectiveNode::UsingDirectiveNode(const soul::ast::SourcePos& sourcePos_, Node* usng_, Node* nskw_, Node* id_, Node* semicolon_, Node* attributes_) :
    CompoundNode(NodeKind::usingDirectiveNode, sourcePos_), usng(usng_), nskw(nskw_), id(id_), semicolon(semicolon_), attributes(attributes_)
{
}

std::expected<Node*, int> UsingDirectiveNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> u = usng->Clone();
    if (!u) return u;
    std::expected<Node*, int> n = nskw->Clone();
    if (!n) return n;
    std::expected<Node*, int> i = id->Clone();
    if (!i) return i;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    UsingDirectiveNode* clone = new UsingDirectiveNode(GetSourcePos(), *u, *n, *i, *sc, clonedAttributes);
    return std::expected<Node*, int>(clone);
}

void UsingDirectiveNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int>  UsingDirectiveNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(usng.get());
    if (!rv) return rv;
    rv = writer.Write(nskw.get());
    if (!rv) return rv;
    rv = writer.Write(id.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> UsingDirectiveNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    usng.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    nskw.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    id.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

NamespaceNode::NamespaceNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::namespaceNode, sourcePos_)
{
}

std::expected<Node*, int> NamespaceNode::Clone() const
{
    NamespaceNode* clone = new NamespaceNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void NamespaceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StaticAssertDeclarationNode::StaticAssertDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::staticAssertDeclarationNode, sourcePos_)
{
}

StaticAssertDeclarationNode::StaticAssertDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* staticAssert_, Node* constantExpr_, Node* comma_, Node* stringLiteral_, Node* semicolon_,
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::staticAssertDeclarationNode, sourcePos_), staticAssert(staticAssert_), constantExpr(constantExpr_), comma(comma_), stringLiteral(stringLiteral_), semicolon(semicolon_),
    lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> StaticAssertDeclarationNode::Clone() const
{
    Node* clonedComma = nullptr;
    if (comma)
    {
        std::expected<Node*, int> c = comma->Clone();
        if (!c) return c;
        clonedComma = *c;
    }
    Node* clonedStringLiteral = nullptr;
    if (stringLiteral)
    {
        std::expected<Node*, int> s = stringLiteral->Clone();
        if (!s) return s;
        clonedStringLiteral = *s;
    }
    std::expected<Node*, int> s = staticAssert->Clone();
    if (!s) return s;
    std::expected<Node*, int> c = constantExpr->Clone();
    if (!c) return c;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    StaticAssertDeclarationNode* clone = new StaticAssertDeclarationNode(GetSourcePos(), *s, *c, clonedComma, clonedStringLiteral, *sc, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void StaticAssertDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> StaticAssertDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(staticAssert.get());
    if (!rv) return rv;
    rv = writer.Write(constantExpr.get());
    if (!rv) return rv;
    rv = writer.Write(comma.get());
    if (!rv) return rv;
    rv = writer.Write(stringLiteral.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StaticAssertDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    staticAssert.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    constantExpr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    comma.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stringLiteral.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

StaticAssertNode::StaticAssertNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::staticAssertNode, sourcePos_)
{
}

std::expected<Node*, int> StaticAssertNode::Clone() const
{
    StaticAssertNode* clone = new StaticAssertNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> AliasDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> u = usng->Clone();
    if (!u) return u;
    std::expected<Node*, int> i = identifier->Clone();
    if (!i) return i;
    std::expected<Node*, int> a = assign->Clone();
    if (!a) return a;
    std::expected<Node*, int> d = definingTypeId->Clone();
    if (!d) return d;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    AliasDeclarationNode* clone = new AliasDeclarationNode(GetSourcePos(), *u, *i, *a, *d, clonedAttributes, *sc);
    return std::expected<Node*, int>(clone);
}

void AliasDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> AliasDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(usng.get());
    if (!rv) return rv;
    rv = writer.Write(identifier.get());
    if (!rv) return rv;
    rv = writer.Write(assign.get());
    if (!rv) return rv;
    rv = writer.Write(definingTypeId.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AliasDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    usng.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    identifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    assign.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    definingTypeId.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

EmptyDeclarationNode::EmptyDeclarationNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::emptyDeclarationNode, sourcePos_)
{
}

std::expected<Node*, int> EmptyDeclarationNode::Clone() const
{
    EmptyDeclarationNode* clone = new EmptyDeclarationNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> AttributeDeclarationNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    AttributeDeclarationNode* clone = new AttributeDeclarationNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
}

void AttributeDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InitDeclaratorListNode::InitDeclaratorListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::initDeclaratorListNode, sourcePos_)
{
}

std::expected<Node*, int> InitDeclaratorListNode::Clone() const
{
    InitDeclaratorListNode* clone = new InitDeclaratorListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> InitDeclaratorNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    InitDeclaratorNode* clone = new InitDeclaratorNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> TrailingFunctionDeclaratorNode::Clone() const
{
    std::expected<Node*, int> d = declarator->Clone();
    if (!d) return d;
    std::expected<Node*, int> p = params->Clone();
    if (!p) return p;
    std::expected<Node*, int> t = trailingReturnType->Clone();
    if (!t) return t;
    TrailingFunctionDeclaratorNode* clone = new TrailingFunctionDeclaratorNode(GetSourcePos(), *d, *p, *t);
    return std::expected<Node*, int>(clone);
}

void TrailingFunctionDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TrailingFunctionDeclaratorNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(params.get());
    if (!rv) return rv;
    rv = writer.Write(trailingReturnType.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TrailingFunctionDeclaratorNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    params.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    trailingReturnType.reset(*nrv);
    return std::expected<bool, int>(true);
}

ParenthesizedDeclaratorNode::ParenthesizedDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::parenthesizedDeclaratorNode, sourcePos_)
{
}

ParenthesizedDeclaratorNode::ParenthesizedDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::parenthesizedDeclaratorNode, sourcePos_), declarator(declarator_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> ParenthesizedDeclaratorNode::Clone() const
{
    std::expected<Node*, int> d = declarator->Clone();
    if (!d) return d;
    ParenthesizedDeclaratorNode* clone = new ParenthesizedDeclaratorNode(GetSourcePos(), *d, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void ParenthesizedDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ParenthesizedDeclaratorNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ParenthesizedDeclaratorNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

AbstractDeclaratorNode::AbstractDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::abstractDeclaratorNode, sourcePos_)
{
}

std::expected<Node*, int> AbstractDeclaratorNode::Clone() const
{
    AbstractDeclaratorNode* clone = new AbstractDeclaratorNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void AbstractDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeclSpecifierSequenceNode::DeclSpecifierSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::declSpecifierSequenceNode, sourcePos_)
{
}

std::expected<Node*, int> DeclSpecifierSequenceNode::Clone() const
{
    DeclSpecifierSequenceNode* clone = new DeclSpecifierSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void DeclSpecifierSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FriendNode::FriendNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::friendNode, sourcePos_)
{
}

std::expected<Node*, int> FriendNode::Clone() const
{
    FriendNode* clone = new FriendNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void FriendNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypedefNode::TypedefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::typedefNode, sourcePos_)
{
}

std::expected<Node*, int> TypedefNode::Clone() const
{
    TypedefNode* clone = new TypedefNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void TypedefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstExprNode::ConstExprNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constExprNode, sourcePos_)
{
}

std::expected<Node*, int> ConstExprNode::Clone() const
{
    ConstExprNode* clone = new ConstExprNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ConstExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstEvalNode::ConstEvalNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constEvalNode, sourcePos_)
{
}

std::expected<Node*, int> ConstEvalNode::Clone() const
{
    ConstEvalNode* clone = new ConstEvalNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ConstEvalNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstInitNode::ConstInitNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constInitNode, sourcePos_)
{
}

std::expected<Node*, int> ConstInitNode::Clone() const
{
    ConstInitNode* clone = new ConstInitNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ConstInitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InlineNode::InlineNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::inlineNode, sourcePos_)
{
}

std::expected<Node*, int> InlineNode::Clone() const
{
    InlineNode* clone = new InlineNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void InlineNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StaticNode::StaticNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::staticNode, sourcePos_)
{
}

std::expected<Node*, int> StaticNode::Clone() const
{
    StaticNode* clone = new StaticNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void StaticNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ThreadLocalNode::ThreadLocalNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::threadLocalNode, sourcePos_)
{
}

std::expected<Node*, int> ThreadLocalNode::Clone() const
{
    ThreadLocalNode* clone = new ThreadLocalNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ThreadLocalNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ExternNode::ExternNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::externNode, sourcePos_)
{
}

std::expected<Node*, int> ExternNode::Clone() const
{
    ExternNode* clone = new ExternNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ExternNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MutableNode::MutableNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::mutableNode, sourcePos_)
{
}

std::expected<Node*, int> MutableNode::Clone() const
{
    MutableNode* clone = new MutableNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void MutableNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ExplicitNode::ExplicitNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::explicitNode, sourcePos_)
{
}

std::expected<Node*, int> ExplicitNode::Clone() const
{
    ExplicitNode* clone = new ExplicitNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> ConditionalExplicitNode::Clone() const
{
    std::expected<Node*, int> c = cond->Clone();
    if (!c) return c;
    ConditionalExplicitNode* clone = new ConditionalExplicitNode(GetSourcePos(), *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void ConditionalExplicitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConditionalExplicitNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(cond.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConditionalExplicitNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    cond.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

QualifiedPtrNode::QualifiedPtrNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::qualifiedPtrNode, sourcePos_, nullptr, nullptr)
{
}

QualifiedPtrNode::QualifiedPtrNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* ptr_) :
    BinaryNode(NodeKind::qualifiedPtrNode, sourcePos_, nns_, ptr_)
{
}

std::expected<Node*, int> QualifiedPtrNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    QualifiedPtrNode* clone = new QualifiedPtrNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> PtrOperatorNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    PtrOperatorNode* clone = new PtrOperatorNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void PtrOperatorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PtrDeclaratorNode::PtrDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::ptrDeclaratorNode, sourcePos_)
{
}

std::expected<Node*, int>PtrDeclaratorNode::Clone() const
{
    PtrDeclaratorNode* clone = new PtrDeclaratorNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> PackDeclaratorIdNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    PackDeclaratorIdNode* clone = new PackDeclaratorIdNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> ArrayDeclaratorNode::Clone() const
{
    Node* clonedDimension = nullptr;
    if (dimension)
    {
        std::expected<Node*, int> d = dimension->Clone();
        if (!d) return d;
        clonedDimension = *d;
    }
    std::expected<Node*, int> c = Child()->Clone();
    ArrayDeclaratorNode* clone = new ArrayDeclaratorNode(GetSourcePos(), *c, clonedDimension, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void ArrayDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ArrayDeclaratorNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(dimension.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayDeclaratorNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    dimension.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

FunctionDeclaratorNode::FunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::functionDeclaratorNode, sourcePos_, nullptr)
{
}

FunctionDeclaratorNode::FunctionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* parameters_) :
    UnaryNode(NodeKind::functionDeclaratorNode, sourcePos_, child_), params(parameters_)
{
}

std::expected<Node*, int> FunctionDeclaratorNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    std::expected<Node*, int> p = params->Clone();
    if (!p) return p;
    FunctionDeclaratorNode* clone = new FunctionDeclaratorNode(GetSourcePos(), *c, *p);
    return std::expected<Node*, int>(clone);
}

void FunctionDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> FunctionDeclaratorNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(params.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FunctionDeclaratorNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    params.reset(*nrv);
    return std::expected<bool, int>(true);
}

PrefixNode::PrefixNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::prefixNode, sourcePos_, nullptr, nullptr)
{
}

PrefixNode::PrefixNode(const soul::ast::SourcePos& sourcePos_, Node* prefix_, Node* subject_) : BinaryNode(NodeKind::prefixNode, sourcePos_, prefix_, subject_)
{
}

std::expected<Node*, int> PrefixNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    PrefixNode* clone = new PrefixNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> TrailingQualifiersNode::Clone() const
{
    std::expected<Node*, int> s = subject->Clone();
    if (!s) return s;
    TrailingQualifiersNode* clone = new TrailingQualifiersNode(GetSourcePos(), *s);
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void TrailingQualifiersNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TrailingQualifiersNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = SequenceNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(subject.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TrailingQualifiersNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = SequenceNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    subject.reset(*nrv);
    return std::expected<bool, int>(true);
}

TrailingAttributesNode::TrailingAttributesNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::trailingAttributesNode, sourcePos_, nullptr, nullptr)
{
}

TrailingAttributesNode::TrailingAttributesNode(const soul::ast::SourcePos& sourcePos_, Node* left_, Node* attributes_) : BinaryNode(NodeKind::trailingAttributesNode, sourcePos_, left_, attributes_)
{
}

std::expected<Node*, int> TrailingAttributesNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    TrailingAttributesNode* clone = new TrailingAttributesNode(GetSourcePos(), *l, *r);
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

std::expected<Node*, int> NoexceptSpecifierNode::Clone() const
{
    Node* clonedConstantExpr = nullptr;
    if (constantExpr)
    {
        std::expected<Node*, int> c = constantExpr->Clone();
        if (!c) return c;
        clonedConstantExpr = *c;
    }
    NoexceptSpecifierNode* clone = new NoexceptSpecifierNode(GetSourcePos(), clonedConstantExpr, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void NoexceptSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NoexceptSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(constantExpr.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NoexceptSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    constantExpr.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

ThrowSpecifierNode::ThrowSpecifierNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::throwSpecifierNode, sourcePos_)
{
}

ThrowSpecifierNode::ThrowSpecifierNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::throwSpecifierNode, sourcePos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> ThrowSpecifierNode::Clone() const
{
    ThrowSpecifierNode* clone = new ThrowSpecifierNode(GetSourcePos(), lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void ThrowSpecifierNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ThrowSpecifierNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ThrowSpecifierNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
