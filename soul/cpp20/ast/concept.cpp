// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.concepts;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

ConceptDefinitionNode::ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conceptDefinitionNode, sourcePos_)
{
}

ConceptDefinitionNode::ConceptDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* conceptName_, Node* assign_, Node* constraintExpr_, Node* semicolon_) :
    CompoundNode(NodeKind::conceptDefinitionNode, sourcePos_), conceptName(conceptName_), assign(assign_), constraintExpr(constraintExpr_), semicolon(semicolon_)
{
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

void ConceptDefinitionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    conceptName.reset(reader.ReadNode());
    assign.reset(reader.ReadNode());
    constraintExpr.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

RequiresExprNode::RequiresExprNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::requiresExprNode, sourcePos_)
{
}

RequiresExprNode::RequiresExprNode(const soul::ast::SourcePos& sourcePos_, Node* params_, Node* body_) : CompoundNode(NodeKind::requiresExprNode, sourcePos_), params(params_), body(body_)
{
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

void RequiresExprNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    params.reset(reader.ReadNode());
    body.reset(reader.ReadNode());
}

RequirementBodyNode::RequirementBodyNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::requirementBodyNode, sourcePos_)
{
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

void RequirementBodyNode::Read(Reader& reader)
{
    SequenceNode::Read(reader);
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
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

void TypeRequirementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    nns.reset(reader.ReadNode());
    typeName.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

CompoundRequirementNode::CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::compoundRequirementNode, sourcePos_)
{
}

CompoundRequirementNode::CompoundRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* noexcept_, Node* returnTypeRequirement_, Node* semicolon_,
    const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::compoundRequirementNode, sourcePos_), expr(expr_), noexceptNode(noexcept_), returnTypeRequirement(returnTypeRequirement_), semicolon(semicolon_), lbPos(lbPos_), rbPos(rbPos_)
{
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

void CompoundRequirementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    expr.reset(reader.ReadNode());
    noexceptNode.reset(reader.ReadNode());
    returnTypeRequirement.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

ReturnTypeRequirementNode::ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::returnTypeRequirementNode, sourcePos_, nullptr)
{
}

ReturnTypeRequirementNode::ReturnTypeRequirementNode(const soul::ast::SourcePos& sourcePos_, Node* typeConstraint_) : UnaryNode(NodeKind::returnTypeRequirementNode, sourcePos_, typeConstraint_)
{
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

void TypeConstraintNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    conceptName.reset(reader.ReadNode());
    hasTemplateArgumentList = reader.ReadBool();
    laPos = reader.ReadSourcePos();
    raPos = reader.ReadSourcePos();
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

RequiresClauseNode::RequiresClauseNode(const soul::ast::SourcePos& sourcePos_, Node* constraintLogicalOrExpr_) : UnaryNode(NodeKind::requiresClauseNode, sourcePos_, constraintLogicalOrExpr_)
{
}

void RequiresClauseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace soul::cpp20::ast
