// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.expression;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

BinaryExprNode::BinaryExprNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::binaryExprNode, sourcePos_, nullptr, nullptr)
{
}

BinaryExprNode::BinaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* op_, Node* left_, Node* right_) :
    BinaryNode(NodeKind::binaryExprNode, sourcePos_, left_, right_), op(op_)
{
}

std::expected<Node*, int> BinaryExprNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    std::expected<Node*, int> o = op->Clone();
    if (!o) return o;
    BinaryExprNode* clone = new BinaryExprNode(GetSourcePos(), *o, *l, *r);
    return std::expected<Node*, int>(clone);
}

void BinaryExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BinaryExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = BinaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(op.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BinaryExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = BinaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    op.reset(*nrv);
    return std::expected<bool, int>(true);
}

UnaryExprNode::UnaryExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::unaryExprNode, sourcePos_, nullptr)
{
}

UnaryExprNode::UnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* op_, Node* child_) : UnaryNode(NodeKind::unaryExprNode, sourcePos_, child_), op(op_)
{
}

std::expected<Node*, int> UnaryExprNode::Clone() const
{
    std::expected<Node*, int> o = op->Clone();
    if (!o) return o;
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    UnaryExprNode* clone = new UnaryExprNode(GetSourcePos(), *o, *c);
    return clone;
}

void UnaryExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> UnaryExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(op.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> UnaryExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    op.reset(*nrv);
    return std::expected<bool, int>(true);
}

ExpressionListNode::ExpressionListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::expressionListNode, sourcePos_)
{
}

std::expected<Node*, int> ExpressionListNode::Clone() const
{
    ExpressionListNode* clone = new ExpressionListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void ExpressionListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExpressionListNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExpressionListNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

AssignmentInitNode::AssignmentInitNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::assignmentInitializerNode, sourcePos_, nullptr)
{
}

AssignmentInitNode::AssignmentInitNode(const soul::ast::SourcePos& sourcePos_, Node* initializer_) : UnaryNode(NodeKind::assignmentInitializerNode, sourcePos_, initializer_)
{
}

std::expected<Node*, int> AssignmentInitNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    AssignmentInitNode* clone = new AssignmentInitNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void AssignmentInitNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

YieldExprNode::YieldExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::yieldExprNode, sourcePos_, nullptr)
{
}

YieldExprNode::YieldExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::yieldExprNode, sourcePos_, child_)
{
}

std::expected<Node*, int> YieldExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    YieldExprNode* clone = new YieldExprNode(GetSourcePos(), *c);
    return clone;
}

void YieldExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConditionalExprNode::ConditionalExprNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conditionalExprNode, sourcePos_)
{
}

ConditionalExprNode::ConditionalExprNode(const soul::ast::SourcePos& sourcePos_, Node* condition_, Node* quest_, Node* thenExpr_, Node* colon_, Node* elseExpr_) :
    CompoundNode(NodeKind::conditionalExprNode, sourcePos_), condition(condition_), quest(quest_), thenExpr(thenExpr_), colon(colon_), elseExpr(elseExpr_)
{
}

std::expected<Node*, int> ConditionalExprNode::Clone() const
{
    std::expected<Node*, int> c = condition->Clone();
    if (!c) return c;
    std::expected<Node*, int> q = quest->Clone();
    if (!q) return q;
    std::expected<Node*, int> t = thenExpr->Clone();
    if (!t) return t;
    std::expected<Node*, int> l = colon->Clone();
    if (!l) return l;
    std::expected<Node*, int> e = elseExpr->Clone();
    if (!e) return e;
    ConditionalExprNode* clone = new ConditionalExprNode(GetSourcePos(), *c, *q, *t, *l, *e);
    return std::expected<Node*, int>(clone);
}

void ConditionalExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ConditionalExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(condition.get());
    if (!rv) return rv;
    rv = writer.Write(quest.get());
    if (!rv) return rv;
    rv = writer.Write(thenExpr.get());
    if (!rv) return rv;
    rv = writer.Write(colon.get());
    if (!rv) return rv;
    rv = writer.Write(elseExpr.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ConditionalExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    condition.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    quest.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    thenExpr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    colon.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    elseExpr.reset(*nrv);
    return std::expected<bool, int>(true);
}

AssignNode::AssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::assignNode, sourcePos_)
{
}

std::expected<Node*, int> AssignNode::Clone() const
{
    AssignNode* clone = new AssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void AssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PlusAssignNode::PlusAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::plusAssignNode, sourcePos_)
{
}

std::expected<Node*, int> PlusAssignNode::Clone() const
{
    PlusAssignNode* clone = new PlusAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void PlusAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MinusAssignNode::MinusAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::minusAssignNode, sourcePos_)
{
}

std::expected<Node*, int> MinusAssignNode::Clone() const
{
    MinusAssignNode* clone = new MinusAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void MinusAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MulAssignNode::MulAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::mulAssignNode, sourcePos_)
{
}

std::expected<Node*, int> MulAssignNode::Clone() const
{
    MulAssignNode* clone = new MulAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void MulAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DivAssignNode::DivAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::divAssignNode, sourcePos_)
{
}

std::expected<Node*, int> DivAssignNode::Clone() const
{
    DivAssignNode* clone = new DivAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DivAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModAssignNode::ModAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::modAssignNode, sourcePos_)
{
}

std::expected<Node*, int> ModAssignNode::Clone() const
{
    ModAssignNode* clone = new ModAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ModAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

XorAssignNode::XorAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::xorAssignNode, sourcePos_)
{
}

std::expected<Node*, int> XorAssignNode::Clone() const
{
    XorAssignNode* clone = new XorAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void XorAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AndAssignNode::AndAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::andAssignNode, sourcePos_)
{
}

std::expected<Node*, int> AndAssignNode::Clone() const
{
    AndAssignNode* clone = new AndAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void AndAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OrAssignNode::OrAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::orAssignNode, sourcePos_)
{
}

std::expected<Node*, int> OrAssignNode::Clone() const
{
    OrAssignNode* clone = new OrAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void OrAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftLeftAssignNode::ShiftLeftAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftLeftAssignNode, sourcePos_)
{
}

std::expected<Node*, int> ShiftLeftAssignNode::Clone() const
{
    ShiftLeftAssignNode* clone = new ShiftLeftAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ShiftLeftAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftRightAssignNode::ShiftRightAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftRightAssignNode, sourcePos_)
{
}

std::expected<Node*, int> ShiftRightAssignNode::Clone() const
{
    ShiftRightAssignNode* clone = new ShiftRightAssignNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ShiftRightAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DisjunctionNode::DisjunctionNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::disjunctionNode, sourcePos_)
{
}

std::expected<Node*, int> DisjunctionNode::Clone() const
{
    DisjunctionNode* clone = new DisjunctionNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DisjunctionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConjunctionNode::ConjunctionNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::conjunctionNode, sourcePos_)
{
}

std::expected<Node*, int> ConjunctionNode::Clone() const
{
    ConjunctionNode* clone = new ConjunctionNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ConjunctionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InclusiveOrNode::InclusiveOrNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::inclusiveOrNode, sourcePos_)
{
}

std::expected<Node*, int> InclusiveOrNode::Clone() const
{
    InclusiveOrNode* clone = new InclusiveOrNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void InclusiveOrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ExclusiveOrNode::ExclusiveOrNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::exclusiveOrNode, sourcePos_)
{
}

std::expected<Node*, int> ExclusiveOrNode::Clone() const
{
    ExclusiveOrNode* clone = new ExclusiveOrNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ExclusiveOrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AndNode::AndNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::andNode, sourcePos_)
{
}

std::expected<Node*, int> AndNode::Clone() const
{
    AndNode* clone = new AndNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void AndNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EqualNode::EqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::equalNode, sourcePos_)
{
}

std::expected<Node*, int> EqualNode::Clone() const
{
    EqualNode* clone = new EqualNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void EqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NotEqualNode::NotEqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::notEqualNode, sourcePos_)
{
}

std::expected<Node*, int> NotEqualNode::Clone() const
{
    NotEqualNode* clone = new NotEqualNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void NotEqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LessNode::LessNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lessNode, sourcePos_)
{
}

std::expected<Node*, int> LessNode::Clone() const
{
    LessNode* clone = new LessNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void LessNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

GreaterNode::GreaterNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::greaterNode, sourcePos_)
{
}

std::expected<Node*, int> GreaterNode::Clone() const
{
    GreaterNode* clone = new GreaterNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void GreaterNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LessOrEqualNode::LessOrEqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lessOrEqualNode, sourcePos_)
{
}

std::expected<Node*, int> LessOrEqualNode::Clone() const
{
    LessOrEqualNode* clone = new LessOrEqualNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void LessOrEqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

GreaterOrEqualNode::GreaterOrEqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::greaterOrEqualNode, sourcePos_)
{
}

std::expected<Node*, int> GreaterOrEqualNode::Clone() const
{
    GreaterOrEqualNode* clone = new GreaterOrEqualNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void GreaterOrEqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CompareNode::CompareNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::compareNode, sourcePos_)
{
}

std::expected<Node*, int> CompareNode::Clone() const
{
    CompareNode* clone = new CompareNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void CompareNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftLeftNode::ShiftLeftNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftLeftNode, sourcePos_)
{
}

std::expected<Node*, int> ShiftLeftNode::Clone() const
{
    ShiftLeftNode* clone = new ShiftLeftNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ShiftLeftNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftRightNode::ShiftRightNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftRightNode, sourcePos_)
{
}

std::expected<Node*, int> ShiftRightNode::Clone() const
{
    ShiftRightNode* clone = new ShiftRightNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ShiftRightNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PlusNode::PlusNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::plusNode, sourcePos_)
{
}

std::expected<Node*, int> PlusNode::Clone() const
{
    PlusNode* clone = new PlusNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void PlusNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MinusNode::MinusNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::minusNode, sourcePos_)
{
}

std::expected<Node*, int> MinusNode::Clone() const
{
    MinusNode* clone = new MinusNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void MinusNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MulNode::MulNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::mulNode, sourcePos_)
{
}

std::expected<Node*, int> MulNode::Clone() const
{
    MulNode* clone = new MulNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void MulNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DivNode::DivNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::divNode, sourcePos_)
{
}

std::expected<Node*, int> DivNode::Clone() const
{
    DivNode* clone = new DivNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DivNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModNode::ModNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::modNode, sourcePos_)
{
}

std::expected<Node*, int> ModNode::Clone() const
{
    ModNode* clone = new ModNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ModNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DotStarNode::DotStarNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::dotStarNode, sourcePos_)
{
}

std::expected<Node*, int> DotStarNode::Clone() const
{
    DotStarNode* clone = new DotStarNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DotStarNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrowStarNode::ArrowStarNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::arrowStarNode, sourcePos_)
{
}

std::expected<Node*, int> ArrowStarNode::Clone() const
{
    ArrowStarNode* clone = new ArrowStarNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ArrowStarNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CastExprNode::CastExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::castExprNode, sourcePos_, nullptr)
{
}

CastExprNode::CastExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::castExprNode, sourcePos_, child_), typeId(typeId_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> CastExprNode::Clone() const
{
    std::expected<Node*, int> t = typeId->Clone();
    if (!t) return t;
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    CastExprNode* clone = new CastExprNode(GetSourcePos(), *t, *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void CastExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CastExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeId.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CastExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeId.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

DerefNode::DerefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::derefNode, sourcePos_)
{
}

std::expected<Node*, int> DerefNode::Clone() const
{
    DerefNode* clone = new DerefNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DerefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AddrOfNode::AddrOfNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::addrOfNode, sourcePos_)
{
}

std::expected<Node*, int> AddrOfNode::Clone() const
{
    AddrOfNode* clone = new AddrOfNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void AddrOfNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NotNode::NotNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::notNode, sourcePos_)
{
}

std::expected<Node*, int> NotNode::Clone() const
{
    NotNode* clone = new NotNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void NotNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ComplementNode::ComplementNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::complementNode, sourcePos_)
{
}

std::expected<Node*, int> ComplementNode::Clone() const
{
    ComplementNode* clone = new ComplementNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ComplementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PrefixIncNode::PrefixIncNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::prefixIncNode, sourcePos_)
{
}

std::expected<Node*, int> PrefixIncNode::Clone() const
{
    PrefixIncNode* clone = new PrefixIncNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void PrefixIncNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PrefixDecNode::PrefixDecNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::prefixDecNode, sourcePos_)
{
}

std::expected<Node*, int> PrefixDecNode::Clone() const
{
    PrefixDecNode* clone = new PrefixDecNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void PrefixDecNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AwaitExprNode::AwaitExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::awaitExprNode, sourcePos_, nullptr)
{
}

AwaitExprNode::AwaitExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) : UnaryNode(NodeKind::awaitExprNode, sourcePos_, child_)
{
}

std::expected<Node*, int> AwaitExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    AwaitExprNode* clone = new AwaitExprNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void AwaitExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SizeOfTypeExprNode::SizeOfTypeExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::sizeOfTypeExprNode, sourcePos_, nullptr)
{
}

SizeOfTypeExprNode::SizeOfTypeExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::sizeOfTypeExprNode, sourcePos_, typeId_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> SizeOfTypeExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    SizeOfTypeExprNode* clone = new SizeOfTypeExprNode(GetSourcePos(), *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void SizeOfTypeExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SizeOfTypeExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SizeOfTypeExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

SizeOfPackExprNode::SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::sizeOfPackExpNode, sourcePos_, nullptr)
{
}

SizeOfPackExprNode::SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_, Node* idNode_, const soul::ast::SourcePos& ellipsisPos_,
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::sizeOfPackExpNode, sourcePos_, idNode_), ellipsisPos(ellipsisPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> SizeOfPackExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    SizeOfPackExprNode* clone = new SizeOfPackExprNode(GetSourcePos(), *c, ellipsisPos, lpPos, rpPos);
    return clone;
}

void SizeOfPackExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SizeOfPackExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(ellipsisPos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SizeOfPackExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    ellipsisPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

SizeOfUnaryExprNode::SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::sizeOfUnaryExprNode, sourcePos_, nullptr)
{
}

SizeOfUnaryExprNode::SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) :
    UnaryNode(NodeKind::sizeOfUnaryExprNode, sourcePos_, child_)
{
}

std::expected<Node*, int> SizeOfUnaryExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    SizeOfUnaryExprNode* clone = new SizeOfUnaryExprNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void SizeOfUnaryExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AlignOfExprNode::AlignOfExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::alignOfExprNode, sourcePos_, nullptr)
{
}

AlignOfExprNode::AlignOfExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::alignOfExprNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int>AlignOfExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    AlignOfExprNode* clone = new AlignOfExprNode(GetSourcePos(), *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void AlignOfExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> AlignOfExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> AlignOfExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

NoexceptExprNode::NoexceptExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::noexceptExprNode, sourcePos_, nullptr)
{
}

NoexceptExprNode::NoexceptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::noexceptExprNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> NoexceptExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    NoexceptExprNode* clone = new NoexceptExprNode(GetSourcePos(), *c, lpPos, rpPos);
    return clone;
}

void NoexceptExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NoexceptExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NoexceptExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

NewExprNode::NewExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::newExprNode, sourcePos_, nullptr)
{
}

NewExprNode::NewExprNode(const soul::ast::SourcePos& sourcePos_, Node* placement_, Node* child_, Node* initializer_, Node* colonColonHead_, const soul::ast::SourcePos& newPos_) :
    UnaryNode(NodeKind::newExprNode, sourcePos_, child_), placement(placement_), initializer(initializer_), colonColonHead(colonColonHead_), newPos(newPos_)
{
}

std::expected<Node*, int> NewExprNode::Clone() const
{
    Node* clonedPlacement = nullptr;
    if (placement)
    {
        std::expected<Node*, int> p = placement->Clone();
        if (!p) return p;
        clonedPlacement = *p;
    }
    Node* clonedInitializer = nullptr;
    if (initializer)
    {
        std::expected<Node*, int> i = initializer->Clone();
        if (!i) return i;
        clonedInitializer = *i;
    }
    Node* clonedColonColonHead = nullptr;
    if (colonColonHead)
    {
        std::expected<Node*, int> h = colonColonHead->Clone();
        if (!h) return h;
        clonedColonColonHead = *h;
    }
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    NewExprNode* clone = new NewExprNode(GetSourcePos(), clonedPlacement, *c, clonedInitializer, clonedColonColonHead, newPos);
    return std::expected<Node*, int>(clone);
}

void NewExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NewExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(colonColonHead.get());
    if (!rv) return rv;
    rv = writer.Write(placement.get());
    if (!rv) return rv;
    rv = writer.Write(initializer.get());
    if (!rv) return rv;
    rv = writer.Write(newPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NewExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    colonColonHead.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    placement.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initializer.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    newPos = *posRv;
    return std::expected<bool, int>(true);
}

NewPlacementNode::NewPlacementNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::newPlacementNode, sourcePos_)
{
}

std::expected<Node*, int> NewPlacementNode::Clone() const
{
    NewPlacementNode* clone = new NewPlacementNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    clone->SetLParenPos(lpPos);
    clone->SetRParenPos(rpPos);
    return std::expected<Node*, int>(clone);
}

void NewPlacementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NewPlacementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NewPlacementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

ParenNewTypeIdNode::ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::parenNewTypeIdNode, sourcePos_, nullptr)
{
}

ParenNewTypeIdNode::ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::parenNewTypeIdNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> ParenNewTypeIdNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    ParenNewTypeIdNode* clone = new ParenNewTypeIdNode(GetSourcePos(), *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void ParenNewTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ParenNewTypeIdNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ParenNewTypeIdNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

NewTypeIdNode::NewTypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::newTypeIdNode, sourcePos_)
{
}

NewTypeIdNode::NewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifierSeq_, Node* newDeclarator_) :
    CompoundNode(NodeKind::newTypeIdNode, sourcePos_), typeSpecifierSeq(typeSpecifierSeq_), newDeclarator(newDeclarator_)
{
}

std::expected<Node*, int> NewTypeIdNode::Clone() const
{
    Node* clonedNewDeclarator = nullptr;
    if (newDeclarator)
    {
        std::expected<Node*, int> n = newDeclarator->Clone();
        if (!n) return n;
        clonedNewDeclarator = *n;
    }
    std::expected<Node*, int> t = typeSpecifierSeq->Clone();
    if (!t) return t;
    NewTypeIdNode* clone = new NewTypeIdNode(GetSourcePos(), *t, clonedNewDeclarator);
    return std::expected<Node*, int>(clone);
}

void NewTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NewTypeIdNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeSpecifierSeq.get());
    if (!rv) return rv;
    rv = writer.Write(newDeclarator.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NewTypeIdNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeSpecifierSeq.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    newDeclarator.reset(*nrv);
    return std::expected<bool, int>(true);
}

ArrayDeletePtrNode::ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::arrayDeletePtrNode, sourcePos_, nullptr)
{
}

ArrayDeletePtrNode::ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_,
    const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    UnaryNode(NodeKind::arrayDeletePtrNode, sourcePos_, ptr_), colonColonHead(colonColonHead_), deletePos(deletePos_), lbPos(lbPos_), rbPos(rbPos_)
{
}

std::expected<Node*, int> ArrayDeletePtrNode::Clone() const
{
    Node* clonedColonColonHead = nullptr;
    if (colonColonHead)
    {
        std::expected<Node*, int> c = colonColonHead->Clone();
        if (!c) return c;
        clonedColonColonHead = *c;
    }
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    ArrayDeletePtrNode* clone = new ArrayDeletePtrNode(GetSourcePos(), *c, clonedColonColonHead, deletePos, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void ArrayDeletePtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ArrayDeletePtrNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(colonColonHead.get());
    if (!rv) return rv;
    rv = writer.Write(deletePos);
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ArrayDeletePtrNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    colonColonHead.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    deletePos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

DeletePtrNode::DeletePtrNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::deletePtrNode, sourcePos_, nullptr)
{
}

DeletePtrNode::DeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_) :
    UnaryNode(NodeKind::deletePtrNode, sourcePos_, ptr_), colonColonHead(colonColonHead_), deletePos(deletePos_)
{
}

std::expected<Node*, int> DeletePtrNode::Clone() const
{
    Node* clonedColonColonHead = nullptr;
    if (colonColonHead)
    {
        std::expected<Node*, int> c = colonColonHead->Clone();
        if (!c) return c;
        clonedColonColonHead = *c;
    }
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    DeletePtrNode* clone = new DeletePtrNode(GetSourcePos(), *c, clonedColonColonHead, deletePos);
    return std::expected<Node*, int>(clone);
}

void DeletePtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DeletePtrNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(colonColonHead.get());
    if (!rv) return rv;
    rv = writer.Write(deletePos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DeletePtrNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    colonColonHead.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    deletePos = *posRv;
    return std::expected<bool, int>(true);
}

SubscriptExprNode::SubscriptExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::subscriptExprNode, sourcePos_, nullptr)
{
}

SubscriptExprNode::SubscriptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* index_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    UnaryNode(NodeKind::subscriptExprNode, sourcePos_, child_), index(index_), lbPos(lbPos_), rbPos(rbPos_)
{
}

std::expected<Node*, int> SubscriptExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    std::expected<Node*, int> i = index->Clone();
    if (!i) return i;
    SubscriptExprNode* clone = new SubscriptExprNode(GetSourcePos(), *c, *i, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void SubscriptExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SubscriptExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(index.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SubscriptExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    index.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

InvokeExprNode::InvokeExprNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::invokeExprNode, sourcePos_)
{
}

InvokeExprNode::InvokeExprNode(const soul::ast::SourcePos& sourcePos_, Node* subject_) : ListNode(NodeKind::invokeExprNode, sourcePos_), subject(subject_)
{
}

std::expected<Node*, int> InvokeExprNode::Clone() const
{
    Node* clonedSubject = nullptr;
    if (subject)
    {
        std::expected<Node*, int> s = subject->Clone();
        if (!s) return s;
        clonedSubject = *s;
    }
    InvokeExprNode* clone = new InvokeExprNode(GetSourcePos(), clonedSubject);
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void InvokeExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> InvokeExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(subject.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> InvokeExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    subject.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

PairNode::PairNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::pairNode, sourcePos_, nullptr, nullptr)
{
}

PairNode::PairNode(const soul::ast::SourcePos& sourcePos_, Node* left_, Node* right_) : BinaryNode(NodeKind::pairNode, sourcePos_, left_, right_)
{
}

std::expected<Node*, int> PairNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    PairNode* clone = new PairNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
}

void PairNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DotNode::DotNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::dotNode, sourcePos_)
{
}

std::expected<Node*, int> DotNode::Clone() const
{
    DotNode* clone = new DotNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DotNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrowNode::ArrowNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::arrowNode, sourcePos_)
{
}

std::expected<Node*, int> ArrowNode::Clone() const
{
    ArrowNode* clone = new ArrowNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ArrowNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MemberExprNode::MemberExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::memberExprNode, sourcePos_, nullptr)
{
}

MemberExprNode::MemberExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* op_, Node* id_) : UnaryNode(NodeKind::memberExprNode, sourcePos_, child_), op(op_), id(id_)
{
}

std::expected<Node*, int> MemberExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    std::expected<Node*, int> o = op->Clone();
    if (!o) return o;
    std::expected<Node*, int> i = id->Clone();
    if (!i) return i;
    MemberExprNode* clone = new MemberExprNode(GetSourcePos(), *c, *o, *i);
    return clone;
}

void MemberExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> MemberExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(op.get());
    if (!rv) return rv;
    rv = writer.Write(id.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> MemberExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    op.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    id.reset(*nrv);
    return std::expected<bool, int>(true);
}

PostfixIncExprNode::PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::postfixIncExprNode, sourcePos_, nullptr)
{
}

PostfixIncExprNode::PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_) :
    UnaryNode(NodeKind::postfixIncExprNode, sourcePos_, child_), opPos(opPos_)
{
}

std::expected<Node*, int>PostfixIncExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    PostfixIncExprNode* clone = new PostfixIncExprNode(GetSourcePos(), *c, opPos);
    return std::expected<Node*, int>(clone);
}

void PostfixIncExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PostfixIncExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(opPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> PostfixIncExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    opPos = *posRv;
    return std::expected<bool, int>(true);
}

PostfixDecExprNode::PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::postfixDecExprNode, sourcePos_, nullptr)
{
}

PostfixDecExprNode::PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_) :
    UnaryNode(NodeKind::postfixDecExprNode, sourcePos_, child_), opPos(opPos_)
{
}

std::expected<Node*, int> PostfixDecExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    PostfixDecExprNode* clone = new PostfixDecExprNode(GetSourcePos(), *c, opPos);
    return clone;
}

void PostfixDecExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> PostfixDecExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(opPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> PostfixDecExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    opPos = *posRv;
    return std::expected<bool, int>(true);
}

TypeIdExprNode::TypeIdExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::typeIdExprNode, sourcePos_, nullptr)
{
}

TypeIdExprNode::TypeIdExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::typeIdExprNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> TypeIdExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    TypeIdExprNode* clone = new TypeIdExprNode(GetSourcePos(), *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void TypeIdExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TypeIdExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TypeIdExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

DynamicCastNode::DynamicCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::dynamicCastNode, sourcePos_)
{
}

std::expected<Node*, int> DynamicCastNode::Clone() const
{
    DynamicCastNode* clone = new DynamicCastNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DynamicCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StaticCastNode::StaticCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::staticCastNode, sourcePos_)
{
}

std::expected<Node*, int> StaticCastNode::Clone() const
{
    StaticCastNode* clone = new StaticCastNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void StaticCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ReinterpretCastNode::ReinterpretCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::reinterpretCastNode, sourcePos_)
{
}

std::expected<Node*, int> ReinterpretCastNode::Clone() const
{
    ReinterpretCastNode* clone = new ReinterpretCastNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ReinterpretCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstCastNode::ConstCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constCastNode, sourcePos_)
{
}

std::expected<Node*, int> ConstCastNode::Clone() const
{
    ConstCastNode* clone = new ConstCastNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ConstCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CppCastExprNode::CppCastExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::cppCastExprNode, sourcePos_, nullptr)
{
}

CppCastExprNode::CppCastExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, Node* child_, Node* op_,
    const soul::ast::SourcePos& laPos_, const soul::ast::SourcePos& raPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::cppCastExprNode, sourcePos_, child_), typeId(typeId_), op(op_), laPos(laPos_), raPos(raPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> CppCastExprNode::Clone() const
{
    std::expected<Node*, int> t = typeId->Clone();
    if (!t) return t;
    std::expected<Node*, int> c = Child()->Clone();
    if (!c)  return c;
    std::expected<Node*, int> o = op->Clone();
    if (!o) return o;
    CppCastExprNode* clone = new CppCastExprNode(GetSourcePos(), *t, *c, *o, laPos, raPos, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void CppCastExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CppCastExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeId.get());
    if (!rv) return rv;
    rv = writer.Write(op.get());
    if (!rv) return rv;
    rv = writer.Write(laPos);
    if (!rv) return rv;
    rv = writer.Write(raPos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CppCastExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeId.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    op.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    laPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    raPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

ThisNode::ThisNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::thisNode, sourcePos_)
{
}

std::expected<Node*, int> ThisNode::Clone() const
{
    ThisNode* clone = new ThisNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ThisNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ParenthesizedExprNode::ParenthesizedExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::parenExprNode, sourcePos_, nullptr)
{
}

ParenthesizedExprNode::ParenthesizedExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::parenExprNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> ParenthesizedExprNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    ParenthesizedExprNode* clone = new ParenthesizedExprNode(GetSourcePos(), *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void ParenthesizedExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ParenthesizedExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = UnaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ParenthesizedExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = UnaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

FoldExprNode::FoldExprNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::foldExprNode, sourcePos_)
{
}

std::expected<Node*, int> FoldExprNode::Clone() const
{
    FoldExprNode* clone = new FoldExprNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    clone->SetLParenPos(lpPos);
    clone->SetRParenPos(rpPos);
    return std::expected<Node*, int>(clone);
}

void FoldExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> FoldExprNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = SequenceNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> FoldExprNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = SequenceNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

NewDeclaratorNode::NewDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::newDeclaratorNode, sourcePos_)
{
}

std::expected<Node*, int> NewDeclaratorNode::Clone() const
{
    NewDeclaratorNode* clone = new NewDeclaratorNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void NewDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrayNewDeclaratorNode::ArrayNewDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::arrayNewDeclaratorNode, sourcePos_)
{
}

std::expected<Node*, int> ArrayNewDeclaratorNode::Clone() const
{
    ArrayNewDeclaratorNode* clone = new ArrayNewDeclaratorNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void ArrayNewDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NewInitializerNode::NewInitializerNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::newInitializerNode, sourcePos_)
{
}

std::expected<Node*, int> NewInitializerNode::Clone() const
{
    NewInitializerNode* clone = new NewInitializerNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void NewInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> NewInitializerNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = ListNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> NewInitializerNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = ListNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

BracedInitListNode::BracedInitListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::bracedInitListNode, sourcePos_)
{
}

std::expected<Node*, int> BracedInitListNode::Clone() const
{
    BracedInitListNode* clone = new BracedInitListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void BracedInitListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DesignatedInitializerNode::DesignatedInitializerNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::designatedInitializerNode, sourcePos_, nullptr, nullptr)
{
}

DesignatedInitializerNode::DesignatedInitializerNode(const soul::ast::SourcePos& sourcePos_, Node* designator_, Node* initializer_) :
    BinaryNode(NodeKind::designatedInitializerNode, sourcePos_, designator_, initializer_)
{
}

std::expected<Node*, int> DesignatedInitializerNode::Clone() const
{
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right()->Clone();
    if (!r) return r;
    DesignatedInitializerNode* clone = new DesignatedInitializerNode(GetSourcePos(), *l, *r);
    return std::expected<Node*, int>(clone);
}

void DesignatedInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DesignatorNode::DesignatorNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::designatorNode, sourcePos_, nullptr)
{
}

DesignatorNode::DesignatorNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_) : UnaryNode(NodeKind::designatorNode, sourcePos_, identifier_)
{
}

std::expected<Node*, int> DesignatorNode::Clone() const
{
    std::expected<Node*, int> c = Child()->Clone();
    if (!c) return c;
    DesignatorNode* clone = new DesignatorNode(GetSourcePos(), *c);
    return std::expected<Node*, int>(clone);
}

void DesignatorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
