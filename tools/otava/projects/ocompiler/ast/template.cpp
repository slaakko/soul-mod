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

Node* TemplateDeclarationNode::Clone() const
{
    TemplateDeclarationNode* clone = new TemplateDeclarationNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
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

Node* TemplateHeadNode::Clone() const
{
    TemplateHeadNode* clone = new TemplateHeadNode(GetSourcePos());
    if (templateParamList)
    {
        clone->SetTemplateParameterList(templateParamList->Clone());
    }
    if (requiresClause)
    {
        clone->SetRequiresClause(requiresClause->Clone());
    }
    return clone;
}

void TemplateHeadNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TemplateHeadNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(templateParamList.get());
    writer.Write(requiresClause.get());
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

Node* TemplateParameterListNode::Clone() const
{
    TemplateParameterListNode* clone = new TemplateParameterListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetLAnglePos(laPos);
    clone->SetRAnglePos(raPos);
    return clone;
}

void TemplateParameterListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TemplateParameterListNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(laPos);
    writer.Write(raPos);
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

Node* TypeParameterNode::Clone() const
{
    Node* clonedAssign = nullptr;
    if (assign)
    {
        clonedAssign = assign->Clone();
    }
    Node* clonedTypeId = nullptr;
    if (typeId)
    {
        clonedTypeId = typeId->Clone();
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        clonedEllipsis = ellipsis->Clone();
    }
    Node* clonedTemplateHead = nullptr;
    if (templateHead)
    {
        clonedTemplateHead = templateHead->Clone();
    }
    TypeParameterNode* clone = new TypeParameterNode(GetSourcePos(), typeConstraint->Clone(), identifier->Clone(), clonedAssign, clonedTypeId, clonedEllipsis, clonedTemplateHead);
    return clone;
}

void TypeParameterNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TypeParameterNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeConstraint.get());
    writer.Write(identifier.get());
    writer.Write(assign.get());
    writer.Write(typeId.get());
    writer.Write(ellipsis.get());
    writer.Write(templateHead.get());
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

Node* TemplateIdNode::Clone() const
{
    TemplateIdNode* clone = new TemplateIdNode(GetSourcePos(), templateName->Clone());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void TemplateIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TemplateIdNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(templateName.get());
    writer.Write(laPos);
    writer.Write(raPos);
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

Node* TypenameNode::Clone() const
{
    TypenameNode* clone = new TypenameNode(GetSourcePos());
    return clone;
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

Node* DeductionGuideNode::Clone() const
{
    Node* clonedExplicitSpecifier = nullptr;
    if (explicitSpecifier)
    {
        clonedExplicitSpecifier = explicitSpecifier->Clone();
    }
    DeductionGuideNode* clone = new DeductionGuideNode(GetSourcePos(), templateName->Clone(), params->Clone(), arrow->Clone(), templateId->Clone(), clonedExplicitSpecifier,
        semicolon->Clone(), lpPos, rpPos);
    return clone;
}

void DeductionGuideNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DeductionGuideNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(templateName.get());
    writer.Write(params.get());
    writer.Write(arrow.get());
    writer.Write(templateId.get());
    writer.Write(explicitSpecifier.get());
    writer.Write(semicolon.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
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

Node* ExplicitInstantiationNode::Clone() const
{
    Node* clonedExtrn = nullptr;
    if (extrn)
    {
        clonedExtrn = extrn->Clone();
    }
    ExplicitInstantiationNode* clone = new ExplicitInstantiationNode(GetSourcePos(), clonedExtrn, tmp->Clone(), declaration->Clone());
    return clone;
}

void ExplicitInstantiationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ExplicitInstantiationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(extrn.get());
    writer.Write(tmp.get());
    writer.Write(declaration.get());
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

Node* TemplateNode::Clone() const
{
    TemplateNode* clone = new TemplateNode(GetSourcePos());
    return clone;
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

Node* ExplicitSpecializationNode::Clone() const
{
    ExplicitSpecializationNode* clone = new ExplicitSpecializationNode(GetSourcePos(), tmp->Clone(), templateHeadNode->Clone(), declaration->Clone(), laPos, raPos);
    return clone;
}

void ExplicitSpecializationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ExplicitSpecializationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(tmp.get());
    writer.Write(declaration.get());
    writer.Write(laPos);
    writer.Write(raPos);
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
