// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.concepts;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

ConceptDefinitionNode::ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conceptDefinitionNode, sourcePos_)
{
}

ConceptDefinitionNode::ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* conceptName_, Node* assign_, Node* constraintExpr_, Node* semicolon_) :
    CompoundNode(NodeKind::conceptDefinitionNode, sourcePos_), conceptName(conceptName_), assign(assign_), constraintExpr(constraintExpr_), semicolon(semicolon_)
{
}

Node* ConceptDefinitionNode::Clone() const
{
    ConceptDefinitionNode* clone = new ConceptDefinitionNode(GetSourcePos(), conceptName->Clone(), assign->Clone(), constraintExpr->Clone(), semicolon->Clone());
    return clone;
}

void ConceptDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConceptDefinitionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(conceptName.get());
    writer.Write(assign.get());
    writer.Write(constraintExpr.get());
    writer.Write(semicolon.get());
}

std::expected<bool, int> ConceptDefinitionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    conceptName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    assign.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    constraintExpr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

RequiresExprNode::RequiresExprNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::requiresExprNode, sourcePos_)
{
}

RequiresExprNode::RequiresExprNode(const soul::ast::SourcePos& sourcePos_, Node* params_, Node* body_) : CompoundNode(NodeKind::requiresExprNode, sourcePos_), params(params_), body(body_)
{
}

Node* RequiresExprNode::Clone() const
{
    Node* clonedParams = nullptr;
    if (params)
    {
        clonedParams = params->Clone();
    }
    RequiresExprNode* clone = new RequiresExprNode(GetSourcePos(), clonedParams, body->Clone());
    return clone;
}

void RequiresExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void RequiresExprNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(params.get());
    writer.Write(body.get());
}

std::expected<bool, int> RequiresExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    params.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    body.reset(*nrv);
    return std::expected<bool, int>(true);
}

RequirementBodyNode::RequirementBodyNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::requirementBodyNode, sourcePos_)
{
}

Node* RequirementBodyNode::Clone() const
{
    RequirementBodyNode* clone = new RequirementBodyNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetLBracePos(lbPos);
    clone->SetRBracePos(rbPos);
    return clone;
}

void RequirementBodyNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void RequirementBodyNode::Write(Writer& writer)
{
    SequenceNode::Write(writer);
    writer.Write(lbPos);
    writer.Write(rbPos);
}

std::expected<bool, int> RequirementBodyNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = SequenceNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

void RequirementBodyNode::SetLBracePos(const soul::ast::SourcePos& lbPos_)
{
    lbPos = lbPos_;
}

void RequirementBodyNode::SetRBracePos(const soul::ast::SourcePos& rbPos_)
{
    rbPos = rbPos_;
}

SimpleRequirementNode::SimpleRequirementNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::simpleRequirementNode, sourcePos_, nullptr, nullptr)
{
}

SimpleRequirementNode::SimpleRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* semicolon_) : BinaryNode(NodeKind::simpleRequirementNode, sourcePos_, expr_, semicolon_)
{
}

Node* SimpleRequirementNode::Clone() const
{
    SimpleRequirementNode* clone = new SimpleRequirementNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void SimpleRequirementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeRequirementNode::TypeRequirementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::typeRequirementNode, sourcePos_)
{
}

TypeRequirementNode::TypeRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* nns_, Node* typeName_, Node* semicolon_) :
    CompoundNode(NodeKind::typeRequirementNode, sourcePos_), nns(nns_), typeName(typeName_), semicolon(semicolon_)
{
}

Node* TypeRequirementNode::Clone() const
{
    Node* clonedNns = nullptr;
    if (nns)
    {
        clonedNns = nns->Clone();
    }
    TypeRequirementNode* clone = new TypeRequirementNode(GetSourcePos(), clonedNns, typeName->Clone(), semicolon->Clone());
    return clone;
}

void TypeRequirementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TypeRequirementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(nns.get());
    writer.Write(typeName.get());
    writer.Write(semicolon.get());
}

std::expected<bool, int> TypeRequirementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    nns.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeName.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

CompoundRequirementNode::CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::compoundRequirementNode, sourcePos_)
{
}

CompoundRequirementNode::CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* noexcept_, Node* returnTypeRequirement_, Node* semicolon_,
    const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::compoundRequirementNode, sourcePos_), expr(expr_), noexceptNode(noexcept_), returnTypeRequirement(returnTypeRequirement_), semicolon(semicolon_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* CompoundRequirementNode::Clone() const
{
    Node* clonedNoExcept = nullptr;
    if (noexceptNode)
    {
        clonedNoExcept = noexceptNode->Clone();
    }
    Node* clonedReturnTypeRequirement = nullptr;
    if (returnTypeRequirement)
    {
        clonedReturnTypeRequirement = returnTypeRequirement->Clone();
    }
    CompoundRequirementNode* clone = new CompoundRequirementNode(GetSourcePos(), expr->Clone(), clonedNoExcept, clonedReturnTypeRequirement, semicolon->Clone(), lbPos, rbPos);
    return clone;
}

void CompoundRequirementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void CompoundRequirementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(expr.get());
    writer.Write(noexceptNode.get());
    writer.Write(returnTypeRequirement.get());
    writer.Write(semicolon.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

std::expected<bool, int> CompoundRequirementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    expr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    noexceptNode.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    returnTypeRequirement.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

ReturnTypeRequirementNode::ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::returnTypeRequirementNode, sourcePos_, nullptr)
{
}

ReturnTypeRequirementNode::ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_) : UnaryNode(NodeKind::returnTypeRequirementNode, sourcePos_, typeConstraint_)
{
}

Node* ReturnTypeRequirementNode::Clone() const
{
    ReturnTypeRequirementNode* clone = new ReturnTypeRequirementNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void ReturnTypeRequirementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NestedRequirementNode::NestedRequirementNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::nestedRequirementNode, sourcePos_, nullptr, nullptr)
{
}

NestedRequirementNode::NestedRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* constraintExpression_, Node* semicolon_) :
    BinaryNode(NodeKind::nestedRequirementNode, sourcePos_, constraintExpression_, semicolon_)
{
}

Node* NestedRequirementNode::Clone() const
{
    NestedRequirementNode* clone = new NestedRequirementNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void NestedRequirementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

TypeConstraintNode::TypeConstraintNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::typeConstraintNode, sourcePos_), hasTemplateArgumentList(false)
{
}

TypeConstraintNode::TypeConstraintNode(const soul::ast::SourcePos& sourcePos_, Node* conceptName_) : ListNode(NodeKind::typeConstraintNode, sourcePos_), conceptName(conceptName_), hasTemplateArgumentList(false)
{
}

Node* TypeConstraintNode::Clone() const
{
    TypeConstraintNode* clone = new TypeConstraintNode(GetSourcePos(), conceptName->Clone());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void TypeConstraintNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TypeConstraintNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(conceptName.get());
    writer.Write(hasTemplateArgumentList);
    writer.Write(laPos);
    writer.Write(raPos);
}

std::expected<bool, int> TypeConstraintNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    conceptName.reset(*nrv);
    rv = reader.ReadBool();
    if (!rv) return rv;
    hasTemplateArgumentList = *rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    laPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    raPos = *posRv;
    return std::expected<bool, int>(true);
}

void TypeConstraintNode::SetLAnglePos(const soul::ast::SourcePos& laPos_)
{
    laPos = laPos_;
}

void TypeConstraintNode::SetRAnglePos(const soul::ast::SourcePos& raPos_)
{
    raPos = raPos_;
}

RequiresClauseNode::RequiresClauseNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::requiresClauseNode, sourcePos_, nullptr)
{
}

RequiresClauseNode::RequiresClauseNode(const soul::ast::SourcePos& sourcePos_, Node* constraintLogicalOrExpr_) :
    UnaryNode(NodeKind::requiresClauseNode, sourcePos_, constraintLogicalOrExpr_)
{
}

Node* RequiresClauseNode::Clone() const
{
    RequiresClauseNode* clone = new RequiresClauseNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void RequiresClauseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
