// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.templates;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

TemplateDeclarationNode::TemplateDeclarationNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::templateDeclarationNode, sourcePos_, nullptr, nullptr)
{
}

TemplateDeclarationNode::TemplateDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* templateHead_, Node* declaration_) :
    BinaryNode(NodeKind::templateDeclarationNode, sourcePos_, templateHead_, declaration_)
{
}

std::expected<Node*, int> TemplateDeclarationNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    TemplateDeclarationNode* clone = new TemplateDeclarationNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
}

void TemplateDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TemplateHeadNode::TemplateHeadNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::templateHeadNode, sourcePos_)
{
}

void TemplateHeadNode::SetTemplateParameterList(Node* templateParamList_)
{
    templateParamList.reset(templateParamList_);
}

void TemplateHeadNode::SetRequiresClause(Node* requiresClause_)
{
    requiresClause.reset(requiresClause_);
}

std::expected<Node*, int> TemplateHeadNode::Clone() const
{
    TemplateHeadNode* clone = new TemplateHeadNode(GetSourcePos());
    if (templateParamList)
    {
        std::expected<Node*, int> t = templateParamList->Clone();
        if (!t) return t;
        clone->SetTemplateParameterList(*t);
    }
    if (requiresClause)
    {
        std::expected<Node*, int> r = requiresClause->Clone();
        if (!r) return r;
        clone->SetRequiresClause(*r);
    }
    return std::expected<Node*, int>(clone);
}

void TemplateHeadNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TemplateHeadNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(templateParamList.get());
    if (!rv) return rv;
    rv = writer.Write(requiresClause.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TemplateHeadNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateParamList.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    requiresClause.reset(*nrv);
    return std::expected<bool, int>(true);
}

TemplateParameterListNode::TemplateParameterListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::templateParameterListNode, sourcePos_)
{
}

std::expected<Node*, int> TemplateParameterListNode::Clone() const
{
    TemplateParameterListNode* clone = new TemplateParameterListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    clone->SetLAnglePos(laPos);
    clone->SetRAnglePos(raPos);
    return std::expected<Node*, int>(clone);
}

void TemplateParameterListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TemplateParameterListNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(laPos);
    if (!rv) return rv;
    rv = writer.Write(raPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TemplateParameterListNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    laPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    raPos = *posRv;
    return std::expected<bool, int>(true);
}

TypeParameterNode::TypeParameterNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::typeParameterNode, sourcePos_)
{
}

TypeParameterNode::TypeParameterNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_, Node* identifier_, Node* assign_, Node* typeId_, Node* ellipsis_, Node* templateHead_) :
    CompoundNode(NodeKind::typeParameterNode, sourcePos_), typeConstraint(typeConstraint_), identifier(identifier_), assign(assign_), typeId(typeId_), ellipsis(ellipsis_), templateHead(templateHead_)
{
}

std::expected<Node*, int> TypeParameterNode::Clone() const
{
    Node* clonedAssign = nullptr;
    if (assign)
    {
        std::expected<Node*, int> a = assign->Clone();
        if (!a) return a;
        clonedAssign = *a;
    }
    Node* clonedTypeId = nullptr;
    if (typeId)
    {
        std::expected<Node*, int> t = typeId->Clone();
        if (!t) return t;
        clonedTypeId = *t;
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        std::expected<Node*, int> e = ellipsis->Clone();
        if (!e) return e;
        clonedEllipsis = *e;
    }
    Node* clonedTemplateHead = nullptr;
    if (templateHead)
    {
        std::expected<Node*, int> h = templateHead->Clone();
        if (!h) return h;
        clonedTemplateHead = *h;
    }
    std::expected<Node*, int> t = typeConstraint->Clone();
    if (!t) return t;
    std::expected<Node*, int> i = identifier->Clone();
    if (!i) return i;
    TypeParameterNode* clone = new TypeParameterNode(GetSourcePos(), *t, *i, clonedAssign, clonedTypeId, clonedEllipsis, clonedTemplateHead);
    return std::expected<Node*, int>(clone);
}

void TypeParameterNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeParameterNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeConstraint.get());
    if (!rv) return rv;
    rv = writer.Write(identifier.get());
    if (!rv) return rv;
    rv = writer.Write(assign.get());
    if (!rv) return rv;
    rv = writer.Write(typeId.get());
    if (!rv) return rv;
    rv = writer.Write(ellipsis.get());
    if (!rv) return rv;
    rv = writer.Write(templateHead.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TypeParameterNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeConstraint.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    identifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    assign.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeId.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ellipsis.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateHead.reset(*nrv);
    return std::expected<bool, int>(true);
}

TemplateIdNode::TemplateIdNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::templateIdNode, sourcePos_)
{
}

TemplateIdNode::TemplateIdNode(const soul::ast::SourcePos& sourcePos_, Node* templateName_) : ListNode(NodeKind::templateIdNode, sourcePos_), templateName(templateName_)
{
}

std::expected<Node*, int> TemplateIdNode::Clone() const
{
    std::expected<Node*, int> n = templateName->Clone();
    if (!n) return n;
    TemplateIdNode* clone = new TemplateIdNode(GetSourcePos(), *n);
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void TemplateIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TemplateIdNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(templateName.get());
    if (!rv) return rv;
    rv = writer.Write(laPos);
    if (!rv) return rv;
    rv = writer.Write(raPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TemplateIdNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateName.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    laPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    raPos = *posRv;
    return std::expected<bool, int>(true);
}

void TemplateIdNode::SetTemplateArgKinds(const std::vector<bool>& templateArgKinds_)
{
    templateArgKinds = templateArgKinds_;
}

TypenameNode::TypenameNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::typenameNode, sourcePos_)
{
}

std::expected<Node*, int> TypenameNode::Clone() const
{
    TypenameNode* clone = new TypenameNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void TypenameNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeductionGuideNode::DeductionGuideNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::deductionGuideNode, sourcePos_)
{
}

DeductionGuideNode::DeductionGuideNode(const soul::ast::SourcePos& sourcePos_, Node* templateName_, Node* params_, Node* arrow_, Node* templateId_, Node* explicitSpecifier_,
    Node* semicolon_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::deductionGuideNode, sourcePos_), templateName(templateName_), params(params_), arrow(arrow_), explicitSpecifier(explicitSpecifier_), semicolon(semicolon_),
    lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> DeductionGuideNode::Clone() const
{
    Node* clonedExplicitSpecifier = nullptr;
    if (explicitSpecifier)
    {
        std::expected<Node*, int> e = explicitSpecifier->Clone();
        if (!e) return e;
        clonedExplicitSpecifier = *e;
    }
    std::expected<Node*, int> n = templateName->Clone();
    if (!n) return n;
    std::expected<Node*, int> p = params->Clone();
    if (!p) return p;
    std::expected<Node*, int> a = arrow->Clone();
    if (!a) return a;
    std::expected<Node*, int> i = templateId->Clone();
    if (!i) return i;
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    DeductionGuideNode* clone = new DeductionGuideNode(GetSourcePos(), *n, *p, *a, *i, clonedExplicitSpecifier, *s, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void DeductionGuideNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DeductionGuideNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(templateName.get());
    if (!rv) return rv;
    rv = writer.Write(params.get());
    if (!rv) return rv;
    rv = writer.Write(arrow.get());
    if (!rv) return rv;
    rv = writer.Write(templateId.get());
    if (!rv) return rv;
    rv = writer.Write(explicitSpecifier.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DeductionGuideNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    params.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    arrow.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateId.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    explicitSpecifier.reset(*nrv);
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

ExplicitInstantiationNode::ExplicitInstantiationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::explicitInstantiationNode, sourcePos_)
{
}

ExplicitInstantiationNode::ExplicitInstantiationNode(const soul::ast::SourcePos& sourcePos_, Node* extrn_, Node* tmp_, Node* declaration_) :
    CompoundNode(NodeKind::explicitInstantiationNode, sourcePos_), extrn(extrn_), tmp(tmp_), declaration(declaration_)
{
}

std::expected<Node*, int> ExplicitInstantiationNode::Clone() const
{
    Node* clonedExtrn = nullptr;
    if (extrn)
    {
        std::expected<Node*, int> e = extrn->Clone();
        if (!e) return e;
        clonedExtrn = *e;
    }
    std::expected<Node*, int> t = tmp->Clone();
    if (!t) return t;
    std::expected<Node*, int> d = declaration->Clone();
    if (!d) return d;
    ExplicitInstantiationNode* clone = new ExplicitInstantiationNode(GetSourcePos(), clonedExtrn, *t, *d);
    return std::expected<Node*, int>(clone);
}

void ExplicitInstantiationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExplicitInstantiationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(extrn.get());
    if (!rv) return rv;
    rv = writer.Write(tmp.get());
    if (!rv) return rv;
    rv = writer.Write(declaration.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExplicitInstantiationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    extrn.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    tmp.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declaration.reset(*nrv);
    return std::expected<bool, int>(true);
}

TemplateNode::TemplateNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::templateNode, sourcePos_)
{
}

std::expected<Node*, int> TemplateNode::Clone() const
{
    TemplateNode* clone = new TemplateNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void TemplateNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ExplicitSpecializationNode::ExplicitSpecializationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::explicitSpecializationNode, sourcePos_)
{
}

ExplicitSpecializationNode::ExplicitSpecializationNode(const soul::ast::SourcePos& sourcePos_, Node* tmp_, Node* templateHeadNode_, Node* declaration_,
    const soul::ast::SourcePos& laPos_, const soul::ast::SourcePos& raPos_) :
    CompoundNode(NodeKind::explicitSpecializationNode, sourcePos_), tmp(tmp_), templateHeadNode(templateHeadNode_), declaration(declaration_), laPos(laPos_), raPos(raPos_)
{
}

std::expected<Node*, int> ExplicitSpecializationNode::Clone() const
{
    std::expected<Node*, int> t = tmp->Clone();
    if (!t) return t;
    std::expected<Node*, int> h = templateHeadNode->Clone();
    if (!h) return h;
    std::expected<Node*, int> d = declaration->Clone();
    if (!d) return d;
    ExplicitSpecializationNode* clone = new ExplicitSpecializationNode(GetSourcePos(), *t, *h, *d, laPos, raPos);
    return std::expected<Node*, int>(clone);
}

void ExplicitSpecializationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExplicitSpecializationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(tmp.get());
    if (!rv) return rv;
    rv = writer.Write(declaration.get());
    if (!rv) return rv;
    rv = writer.Write(laPos);
    if (!rv) return rv;
    rv = writer.Write(raPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExplicitSpecializationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    tmp.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declaration.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    laPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    raPos = *posRv;
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
