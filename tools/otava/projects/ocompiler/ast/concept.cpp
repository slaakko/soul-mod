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

std::expected<Node*, int> ConceptDefinitionNode::Clone() const
{
    std::expected<Node*, int> cn = conceptName->Clone();
    if (!cn) return cn;
    std::expected<Node*, int> an = assign->Clone();
    if (!an) return an;
    std::expected<Node*, int> en = constraintExpr->Clone();
    if (!en) return en;
    std::expected<Node*, int> sn = semicolon->Clone();
    if (!sn) return sn;
    ConceptDefinitionNode* clone = new ConceptDefinitionNode(GetSourcePos(), *cn, *an, *en, *sn);
    return std::expected<Node*, int>(clone);
}

void ConceptDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConceptDefinitionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(conceptName.get());
    if (!rv) return rv;
    rv = writer.Write(assign.get());
    if (!rv) return rv;
    rv = writer.Write(constraintExpr.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> RequiresExprNode::Clone() const
{
    Node* clonedParams = nullptr;
    if (params)
    {
        std::expected<Node*, int> pc = params->Clone();
        if (!pc) return pc;
        clonedParams = *pc;
    }
    std::expected<Node*, int> bc = body->Clone();
    if (!bc) return bc;
    RequiresExprNode* clone = new RequiresExprNode(GetSourcePos(), clonedParams, *bc);
    return std::expected<Node*, int>(clone);
}

void RequiresExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> RequiresExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(params.get());
    if (!rv) return rv;
    rv = writer.Write(body.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> RequirementBodyNode::Clone() const
{
    RequirementBodyNode* clone = new RequirementBodyNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> nc = node->Clone();
        if (!nc) return nc;
        std::expected<bool, int> rv = clone->AddNode(*nc);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    clone->SetLBracePos(lbPos);
    clone->SetRBracePos(rbPos);
    return std::expected<Node*, int>(clone);
}

void RequirementBodyNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> RequirementBodyNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = SequenceNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> SimpleRequirementNode::Clone() const
{
    std::expected<Node*, int> lrv = Left()->Clone();
    if (!lrv) return lrv;
    std::expected<Node*, int> rrv = Right()->Clone();
    if (!rrv) return rrv;
    SimpleRequirementNode* clone = new SimpleRequirementNode(GetSourcePos(), *lrv, *rrv);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> TypeRequirementNode::Clone() const
{
    Node* clonedNns = nullptr;
    if (nns)
    {
        std::expected<Node*, int> nc = nns->Clone();
        if (!nc) return nc;
        clonedNns = *nc;
    }
    std::expected<Node*, int> tn = typeName->Clone();
    if (!tn) return tn;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    TypeRequirementNode* clone = new TypeRequirementNode(GetSourcePos(), clonedNns, *tn, *sc);
    return std::expected<Node*, int>(clone);
}

void TypeRequirementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeRequirementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(nns.get());
    if (!rv) return rv;
    rv = writer.Write(typeName.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> CompoundRequirementNode::Clone() const
{
    Node* clonedNoExcept = nullptr;
    if (noexceptNode)
    {
        std::expected<Node*, int> ne = noexceptNode->Clone();
        if (!ne) return ne;
        clonedNoExcept = *ne;
    }
    Node* clonedReturnTypeRequirement = nullptr;
    if (returnTypeRequirement)
    {
        std::expected<Node*, int> rt = returnTypeRequirement->Clone();
        if (!rt) return rt;
        clonedReturnTypeRequirement = *rt;
    }
    std::expected<Node*, int> ex = expr->Clone();
    if (!ex) return ex;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    CompoundRequirementNode* clone = new CompoundRequirementNode(GetSourcePos(), *ex, clonedNoExcept, clonedReturnTypeRequirement, *sc, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void CompoundRequirementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CompoundRequirementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(expr.get());
    if (!rv) return rv;
    rv = writer.Write(noexceptNode.get());
    if (!rv) return rv;
    rv = writer.Write(returnTypeRequirement.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> ReturnTypeRequirementNode::Clone() const
{
    std::expected<Node*, int> cc = Child()->Clone();
    if (!cc) return cc;
    ReturnTypeRequirementNode* clone = new ReturnTypeRequirementNode(GetSourcePos(), *cc);
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> NestedRequirementNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    NestedRequirementNode* clone = new NestedRequirementNode(GetSourcePos(), *l, *r);
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

std::expected<Node*, int> TypeConstraintNode::Clone() const
{
    std::expected<Node*, int> cn = conceptName->Clone();
    if (!cn) return cn;
    TypeConstraintNode* clone = new TypeConstraintNode(GetSourcePos(), *cn);
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void TypeConstraintNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeConstraintNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(conceptName.get());
    if (!rv) return rv;
    rv = writer.Write(hasTemplateArgumentList);
    if (!rv) return rv;
    rv = writer.Write(laPos);
    if (!rv) return rv;
    rv = writer.Write(raPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> RequiresClauseNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    RequiresClauseNode* clone = new RequiresClauseNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void RequiresClauseNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
