// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.templates;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

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

void TemplateHeadNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    templateParamList.reset(reader.ReadNode());
    requiresClause.reset(reader.ReadNode());
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

void TemplateParameterListNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    laPos = reader.ReadSourcePos();
    raPos = reader.ReadSourcePos();
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

void TypeParameterNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeConstraint.reset(reader.ReadNode());
    identifier.reset(reader.ReadNode());
    assign.reset(reader.ReadNode());
    typeId.reset(reader.ReadNode());
    ellipsis.reset(reader.ReadNode());
    templateHead.reset(reader.ReadNode());
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

void TemplateIdNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    templateName.reset(reader.ReadNode());
    laPos = reader.ReadSourcePos();
    raPos = reader.ReadSourcePos();
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

void DeductionGuideNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    templateName.reset(reader.ReadNode());
    params.reset(reader.ReadNode());
    arrow.reset(reader.ReadNode());
    templateId.reset(reader.ReadNode());
    explicitSpecifier.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
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

void ExplicitInstantiationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    extrn.reset(reader.ReadNode());
    tmp.reset(reader.ReadNode());
    declaration.reset(reader.ReadNode());
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

ExplicitSpecializationNode::ExplicitSpecializationNode(const soul::ast::SourcePos& sourcePos_, Node* tmp_, Node* declaration_, const soul::ast::SourcePos& laPos_, 
    const soul::ast::SourcePos& raPos_) :
    CompoundNode(NodeKind::explicitSpecializationNode, sourcePos_), tmp(tmp_), declaration(declaration_), laPos(laPos_), raPos(raPos_)
{
}

Node* ExplicitSpecializationNode::Clone() const
{
    ExplicitSpecializationNode* clone = new ExplicitSpecializationNode(GetSourcePos(), tmp->Clone(), declaration->Clone(), laPos, raPos);
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

void ExplicitSpecializationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    tmp.reset(reader.ReadNode());
    declaration.reset(reader.ReadNode());
    laPos = reader.ReadSourcePos();
    raPos = reader.ReadSourcePos();
}

} // namespace soul::cpp20::ast
