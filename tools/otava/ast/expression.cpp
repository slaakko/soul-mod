// =================================
// Copyright (c) 2022 Seppo Laakko
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

Node* BinaryExprNode::Clone() const
{
    BinaryExprNode* clone = new BinaryExprNode(GetSourcePos(), op->Clone(), Left()->Clone(), Right()->Clone());
    return clone;
}

void BinaryExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BinaryExprNode::Write(Writer& writer)
{
    BinaryNode::Write(writer);
    writer.Write(op.get());
}

void BinaryExprNode::Read(Reader& reader)
{
    BinaryNode::Read(reader);
    op.reset(reader.ReadNode());
}

UnaryExprNode::UnaryExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::unaryExprNode, sourcePos_, nullptr)
{
}

UnaryExprNode::UnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* op_, Node* child_) : UnaryNode(NodeKind::unaryExprNode, sourcePos_, child_), op(op_)
{
}

Node* UnaryExprNode::Clone() const
{
    UnaryExprNode* clone = new UnaryExprNode(GetSourcePos(), op->Clone(), Child()->Clone());
    return clone;
}

void UnaryExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void UnaryExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(op.get());
}

void UnaryExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    op.reset(reader.ReadNode());
}

ExpressionListNode::ExpressionListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::expressionListNode, sourcePos_)
{
}

Node* ExpressionListNode::Clone() const
{
    ExpressionListNode* clone = new ExpressionListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void ExpressionListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ExpressionListNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ExpressionListNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

AssignmentInitNode::AssignmentInitNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::assignmentInitializerNode, sourcePos_, nullptr)
{
}

AssignmentInitNode::AssignmentInitNode(const soul::ast::SourcePos& sourcePos_, Node* initializer_) : UnaryNode(NodeKind::assignmentInitializerNode, sourcePos_, initializer_)
{
}

Node* AssignmentInitNode::Clone() const
{
    AssignmentInitNode* clone = new AssignmentInitNode(GetSourcePos(), Child()->Clone());
    return clone;
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

Node* YieldExprNode::Clone() const
{
    YieldExprNode* clone = new YieldExprNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void YieldExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ThrowExprNode::ThrowExprNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::throwExprNode, sourcePos_)
{
}

ThrowExprNode::ThrowExprNode(const soul::ast::SourcePos& sourcePos_, Node* exception_) : CompoundNode(NodeKind::throwExprNode, sourcePos_), exception(exception_)
{
}

Node* ThrowExprNode::Clone() const
{
    Node* clonedException = nullptr;
    if (exception)
    {
        clonedException = exception->Clone();
    }
    ThrowExprNode* clone = new ThrowExprNode(GetSourcePos(), clonedException);
    return clone;
}

void ThrowExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ThrowExprNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(exception.get());
}

void ThrowExprNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    exception.reset(reader.ReadNode());
}

ConditionalExprNode::ConditionalExprNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conditionalExprNode, sourcePos_)
{
}

ConditionalExprNode::ConditionalExprNode(const soul::ast::SourcePos& sourcePos_, Node* condition_, Node* quest_, Node* thenExpr_, Node* colon_, Node* elseExpr_) :
    CompoundNode(NodeKind::conditionalExprNode, sourcePos_), condition(condition_), quest(quest_), thenExpr(thenExpr_), colon(colon_), elseExpr(elseExpr_)
{
}

Node* ConditionalExprNode::Clone() const
{
    ConditionalExprNode* clone = new ConditionalExprNode(GetSourcePos(), condition->Clone(), quest->Clone(), thenExpr->Clone(), colon->Clone(), elseExpr->Clone());
    return clone;
}

void ConditionalExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConditionalExprNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(condition.get());
    writer.Write(quest.get());
    writer.Write(thenExpr.get());
    writer.Write(colon.get());
    writer.Write(elseExpr.get());
}

void ConditionalExprNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    condition.reset(reader.ReadNode());
    quest.reset(reader.ReadNode());
    thenExpr.reset(reader.ReadNode());
    colon.reset(reader.ReadNode());
    elseExpr.reset(reader.ReadNode());
}

AssignNode::AssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::assignNode, sourcePos_)
{
}

Node* AssignNode::Clone() const
{
    AssignNode* clone = new AssignNode(GetSourcePos());
    return clone;
}

void AssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PlusAssignNode::PlusAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::plusAssignNode, sourcePos_)
{
}

Node* PlusAssignNode::Clone() const
{
    PlusAssignNode* clone = new PlusAssignNode(GetSourcePos());
    return clone;
}

void PlusAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MinusAssignNode::MinusAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::minusAssignNode, sourcePos_)
{
}

Node* MinusAssignNode::Clone() const
{
    MinusAssignNode* clone = new MinusAssignNode(GetSourcePos());
    return clone;
}

void MinusAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MulAssignNode::MulAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::mulAssignNode, sourcePos_)
{
}

Node* MulAssignNode::Clone() const
{
    MulAssignNode* clone = new MulAssignNode(GetSourcePos());
    return clone;
}

void MulAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DivAssignNode::DivAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::divAssignNode, sourcePos_)
{
}

Node* DivAssignNode::Clone() const
{
    DivAssignNode* clone = new DivAssignNode(GetSourcePos());
    return clone;
}

void DivAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModAssignNode::ModAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::modAssignNode, sourcePos_)
{
}

Node* ModAssignNode::Clone() const
{
    ModAssignNode* clone = new ModAssignNode(GetSourcePos());
    return clone;
}

void ModAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

XorAssignNode::XorAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::xorAssignNode, sourcePos_)
{
}

Node* XorAssignNode::Clone() const
{
    XorAssignNode* clone = new XorAssignNode(GetSourcePos());
    return clone;
}

void XorAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AndAssignNode::AndAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::andAssignNode, sourcePos_)
{
}

Node* AndAssignNode::Clone() const
{
    AndAssignNode* clone = new AndAssignNode(GetSourcePos());
    return clone;
}

void AndAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OrAssignNode::OrAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::orAssignNode, sourcePos_)
{
}

Node* OrAssignNode::Clone() const
{
    OrAssignNode* clone = new OrAssignNode(GetSourcePos());
    return clone;
}

void OrAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftLeftAssignNode::ShiftLeftAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftLeftAssignNode, sourcePos_)
{
}

Node* ShiftLeftAssignNode::Clone() const
{
    ShiftLeftAssignNode* clone = new ShiftLeftAssignNode(GetSourcePos());
    return clone;
}

void ShiftLeftAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftRightAssignNode::ShiftRightAssignNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftRightAssignNode, sourcePos_)
{
}

Node* ShiftRightAssignNode::Clone() const
{
    ShiftRightAssignNode* clone = new ShiftRightAssignNode(GetSourcePos());
    return clone;
}

void ShiftRightAssignNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DisjunctionNode::DisjunctionNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::disjunctionNode, sourcePos_)
{
}

Node* DisjunctionNode::Clone() const
{
    DisjunctionNode* clone = new DisjunctionNode(GetSourcePos());
    return clone;
}

void DisjunctionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConjunctionNode::ConjunctionNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::conjunctionNode, sourcePos_)
{
}

Node* ConjunctionNode::Clone() const
{
    ConjunctionNode* clone = new ConjunctionNode(GetSourcePos());
    return clone;
}

void ConjunctionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InclusiveOrNode::InclusiveOrNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::inclusiveOrNode, sourcePos_)
{
}

Node* InclusiveOrNode::Clone() const
{
    InclusiveOrNode* clone = new InclusiveOrNode(GetSourcePos());
    return clone;
}

void InclusiveOrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ExclusiveOrNode::ExclusiveOrNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::exclusiveOrNode, sourcePos_)
{
}

Node* ExclusiveOrNode::Clone() const
{
    ExclusiveOrNode* clone = new ExclusiveOrNode(GetSourcePos());
    return clone;
}

void ExclusiveOrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AndNode::AndNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::andNode, sourcePos_)
{
}

Node* AndNode::Clone() const
{
    AndNode* clone = new AndNode(GetSourcePos());
    return clone;
}

void AndNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

EqualNode::EqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::equalNode, sourcePos_)
{
}

Node* EqualNode::Clone() const
{
    EqualNode* clone = new EqualNode(GetSourcePos());
    return clone;
}

void EqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NotEqualNode::NotEqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::notEqualNode, sourcePos_)
{
}

Node* NotEqualNode::Clone() const
{
    NotEqualNode* clone = new NotEqualNode(GetSourcePos());
    return clone;
}

void NotEqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LessNode::LessNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lessNode, sourcePos_)
{
}

Node* LessNode::Clone() const
{
    LessNode* clone = new LessNode(GetSourcePos());
    return clone;
}

void LessNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

GreaterNode::GreaterNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::greaterNode, sourcePos_)
{
}

Node* GreaterNode::Clone() const
{
    GreaterNode* clone = new GreaterNode(GetSourcePos());
    return clone;
}

void GreaterNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

LessOrEqualNode::LessOrEqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::lessOrEqualNode, sourcePos_)
{
}

Node* LessOrEqualNode::Clone() const
{
    LessOrEqualNode* clone = new LessOrEqualNode(GetSourcePos());
    return clone;
}

void LessOrEqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

GreaterOrEqualNode::GreaterOrEqualNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::greaterOrEqualNode, sourcePos_)
{
}

Node* GreaterOrEqualNode::Clone() const
{
    GreaterOrEqualNode* clone = new GreaterOrEqualNode(GetSourcePos());
    return clone;
}

void GreaterOrEqualNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CompareNode::CompareNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::compareNode, sourcePos_)
{
}

Node* CompareNode::Clone() const
{
    CompareNode* clone = new CompareNode(GetSourcePos());
    return clone;
}

void CompareNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftLeftNode::ShiftLeftNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftLeftNode, sourcePos_)
{
}

Node* ShiftLeftNode::Clone() const
{
    ShiftLeftNode* clone = new ShiftLeftNode(GetSourcePos());
    return clone;
}

void ShiftLeftNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ShiftRightNode::ShiftRightNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::shiftRightNode, sourcePos_)
{
}

Node* ShiftRightNode::Clone() const
{
    ShiftRightNode* clone = new ShiftRightNode(GetSourcePos());
    return clone;
}

void ShiftRightNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PlusNode::PlusNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::plusNode, sourcePos_)
{
}

Node* PlusNode::Clone() const
{
    PlusNode* clone = new PlusNode(GetSourcePos());
    return clone;
}

void PlusNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MinusNode::MinusNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::minusNode, sourcePos_)
{
}

Node* MinusNode::Clone() const
{
    MinusNode* clone = new MinusNode(GetSourcePos());
    return clone;
}

void MinusNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

MulNode::MulNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::mulNode, sourcePos_)
{
}

Node* MulNode::Clone() const
{
    MulNode* clone = new MulNode(GetSourcePos());
    return clone;
}

void MulNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DivNode::DivNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::divNode, sourcePos_)
{
}

Node* DivNode::Clone() const
{
    DivNode* clone = new DivNode(GetSourcePos());
    return clone;
}

void DivNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ModNode::ModNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::modNode, sourcePos_)
{
}

Node* ModNode::Clone() const
{
    ModNode* clone = new ModNode(GetSourcePos());
    return clone;
}

void ModNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DotStarNode::DotStarNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::dotStarNode, sourcePos_)
{
}

Node* DotStarNode::Clone() const
{
    DotStarNode* clone = new DotStarNode(GetSourcePos());
    return clone;
}

void DotStarNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrowStarNode::ArrowStarNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::arrowStarNode, sourcePos_)
{
}

Node* ArrowStarNode::Clone() const
{
    ArrowStarNode* clone = new ArrowStarNode(GetSourcePos());
    return clone;
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

Node* CastExprNode::Clone() const
{
    CastExprNode* clone = new CastExprNode(GetSourcePos(), typeId->Clone(), Child()->Clone(), lpPos, rpPos);
    return clone;
}

void CastExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void CastExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(typeId.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void CastExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    typeId.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

DerefNode::DerefNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::derefNode, sourcePos_)
{
}

Node* DerefNode::Clone() const
{
    DerefNode* clone = new DerefNode(GetSourcePos());
    return clone;
}

void DerefNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

AddrOfNode::AddrOfNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::addrOfNode, sourcePos_)
{
}

Node* AddrOfNode::Clone() const
{
    AddrOfNode* clone = new AddrOfNode(GetSourcePos());
    return clone;
}

void AddrOfNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NotNode::NotNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::notNode, sourcePos_)
{
}

Node* NotNode::Clone() const
{
    NotNode* clone = new NotNode(GetSourcePos());
    return clone;
}

void NotNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ComplementNode::ComplementNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::complementNode, sourcePos_)
{
}

Node* ComplementNode::Clone() const
{
    ComplementNode* clone = new ComplementNode(GetSourcePos());
    return clone;
}

void ComplementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PrefixIncNode::PrefixIncNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::prefixIncNode, sourcePos_)
{
}

Node* PrefixIncNode::Clone() const
{
    PrefixIncNode* clone = new PrefixIncNode(GetSourcePos());
    return clone;
}

void PrefixIncNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

PrefixDecNode::PrefixDecNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::prefixDecNode, sourcePos_)
{
}

Node* PrefixDecNode::Clone() const
{
    PrefixDecNode* clone = new PrefixDecNode(GetSourcePos());
    return clone;
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

Node* AwaitExprNode::Clone() const
{
    AwaitExprNode* clone = new AwaitExprNode(GetSourcePos(), Child()->Clone());
    return clone;
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

Node* SizeOfTypeExprNode::Clone() const
{
    SizeOfTypeExprNode* clone = new SizeOfTypeExprNode(GetSourcePos(), Child()->Clone(), lpPos, rpPos);
    return clone;
}

void SizeOfTypeExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SizeOfTypeExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void SizeOfTypeExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

SizeOfPackExprNode::SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::sizeOfPackExpNode, sourcePos_, nullptr)
{
}

SizeOfPackExprNode::SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_, Node* idNode_, const soul::ast::SourcePos& ellipsisPos_, 
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::sizeOfPackExpNode, sourcePos_, idNode_), ellipsisPos(ellipsisPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* SizeOfPackExprNode::Clone() const
{
    SizeOfPackExprNode* clone = new SizeOfPackExprNode(GetSourcePos(), Child()->Clone(), ellipsisPos, lpPos, rpPos);
    return clone;
}

void SizeOfPackExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SizeOfPackExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(ellipsisPos);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void SizeOfPackExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    ellipsisPos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

SizeOfUnaryExprNode::SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::sizeOfUnaryExprNode, sourcePos_, nullptr)
{
}

SizeOfUnaryExprNode::SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) :
    UnaryNode(NodeKind::sizeOfUnaryExprNode, sourcePos_, child_)
{
}

Node* SizeOfUnaryExprNode::Clone() const
{
    SizeOfUnaryExprNode* clone = new SizeOfUnaryExprNode(GetSourcePos(), Child()->Clone());
    return clone;
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

Node* AlignOfExprNode::Clone() const
{
    AlignOfExprNode* clone = new AlignOfExprNode(GetSourcePos(), Child()->Clone(), lpPos, rpPos);
    return clone;
}

void AlignOfExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void AlignOfExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void AlignOfExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

NoexceptExprNode::NoexceptExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::noexceptExprNode, sourcePos_, nullptr)
{
}

NoexceptExprNode::NoexceptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::noexceptExprNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* NoexceptExprNode::Clone() const
{
    NoexceptExprNode* clone = new NoexceptExprNode(GetSourcePos(), Child()->Clone(), lpPos, rpPos);
    return clone;
}

void NoexceptExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NoexceptExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void NoexceptExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

NewExprNode::NewExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::newExprNode, sourcePos_, nullptr)
{
}

NewExprNode::NewExprNode(const soul::ast::SourcePos& sourcePos_, Node* placement_, Node* child_, Node* initializer_, Node* colonColonHead_, const soul::ast::SourcePos& newPos_) :
    UnaryNode(NodeKind::newExprNode, sourcePos_, child_), placement(placement_), initializer(initializer_), colonColonHead(colonColonHead_), newPos(newPos_)
{
}

Node* NewExprNode::Clone() const
{
    Node* clonedPlacement = nullptr;
    if (placement)
    {
        clonedPlacement = placement->Clone();
    }
    Node* clonedInitializer = nullptr;
    if (initializer)
    {
        clonedInitializer = initializer->Clone();
    }
    Node* clonedColonColonHead = nullptr;
    if (colonColonHead)
    {
        clonedColonColonHead = colonColonHead->Clone();
    }
    NewExprNode* clone = new NewExprNode(GetSourcePos(), clonedPlacement, Child(), clonedInitializer, clonedColonColonHead, newPos);
    return clone;
}

void NewExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NewExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(colonColonHead.get());
    writer.Write(placement.get());
    writer.Write(initializer.get());
    writer.Write(newPos);
}

void NewExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    colonColonHead.reset(reader.ReadNode());
    placement.reset(reader.ReadNode());
    initializer.reset(reader.ReadNode());
    newPos = reader.ReadSourcePos();
}

NewPlacementNode::NewPlacementNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::newPlacementNode, sourcePos_)
{
}

Node* NewPlacementNode::Clone() const
{
    NewPlacementNode* clone = new NewPlacementNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetLParenPos(lpPos);
    clone->SetRParenPos(rpPos);
    return clone;
}

void NewPlacementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NewPlacementNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void NewPlacementNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

ParenNewTypeIdNode::ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::parenNewTypeIdNode, sourcePos_, nullptr)
{
}

ParenNewTypeIdNode::ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::parenNewTypeIdNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* ParenNewTypeIdNode::Clone() const
{
    ParenNewTypeIdNode* clone = new ParenNewTypeIdNode(GetSourcePos(), Child()->Clone(), lpPos, rpPos);
    return clone;
}

void ParenNewTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ParenNewTypeIdNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ParenNewTypeIdNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

NewTypeIdNode::NewTypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::newTypeIdNode, sourcePos_)
{
}

NewTypeIdNode::NewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifierSeq_, Node* newDeclarator_) : 
    CompoundNode(NodeKind::newTypeIdNode, sourcePos_), typeSpecifierSeq(typeSpecifierSeq_), newDeclarator(newDeclarator_)
{
}

Node* NewTypeIdNode::Clone() const
{
    Node* clonedNewDeclarator = nullptr;
    if (newDeclarator)
    {
        clonedNewDeclarator = newDeclarator->Clone();
    }
    NewTypeIdNode* clone = new NewTypeIdNode(GetSourcePos(), typeSpecifierSeq->Clone(), clonedNewDeclarator);
    return clone;
}

void NewTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NewTypeIdNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeSpecifierSeq.get());
    writer.Write(newDeclarator.get());
}

void NewTypeIdNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeSpecifierSeq.reset(reader.ReadNode());
    newDeclarator.reset(reader.ReadNode());
}

ArrayDeletePtrNode::ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::arrayDeletePtrNode, sourcePos_, nullptr)
{
}

ArrayDeletePtrNode::ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_, 
    const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    UnaryNode(NodeKind::arrayDeletePtrNode, sourcePos_, ptr_), colonColonHead(colonColonHead_), deletePos(deletePos_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* ArrayDeletePtrNode::Clone() const
{
    Node* clonedColonColonHead = nullptr;
    if (colonColonHead)
    {
        clonedColonColonHead = colonColonHead->Clone();
    }
    ArrayDeletePtrNode* clone = new ArrayDeletePtrNode(GetSourcePos(), Child()->Clone(), clonedColonColonHead, deletePos, lbPos, rbPos);
    return clone;
}

void ArrayDeletePtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ArrayDeletePtrNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(colonColonHead.get());
    writer.Write(deletePos);
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void ArrayDeletePtrNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    colonColonHead.reset(reader.ReadNode());
    deletePos = reader.ReadSourcePos();
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

DeletePtrNode::DeletePtrNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::deletePtrNode, sourcePos_, nullptr)
{
}

DeletePtrNode::DeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_) :
    UnaryNode(NodeKind::deletePtrNode, sourcePos_, ptr_), colonColonHead(colonColonHead_), deletePos(deletePos_)
{
}

Node* DeletePtrNode::Clone() const
{
    Node* clonedColonColonHead = nullptr;
    if (colonColonHead)
    {
        clonedColonColonHead = colonColonHead->Clone();
    }
    DeletePtrNode* clone = new DeletePtrNode(GetSourcePos(), Child()->Clone(), clonedColonColonHead, deletePos);
    return clone;
}

void DeletePtrNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DeletePtrNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(colonColonHead.get());
    writer.Write(deletePos);
}

void DeletePtrNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    colonColonHead.reset(reader.ReadNode());
    deletePos = reader.ReadSourcePos();
}

SubscriptExprNode::SubscriptExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::subscriptExprNode, sourcePos_, nullptr)
{
}

SubscriptExprNode::SubscriptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* index_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    UnaryNode(NodeKind::subscriptExprNode, sourcePos_, child_), index(index_), lbPos(lbPos_), rbPos(rbPos_)
{
}

Node* SubscriptExprNode::Clone() const
{
    SubscriptExprNode* clone = new SubscriptExprNode(GetSourcePos(), Child()->Clone(), index->Clone(), lbPos, rbPos);
    return clone;
}

void SubscriptExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SubscriptExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(index.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void SubscriptExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    index.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

InvokeExprNode::InvokeExprNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::invokeExprNode, sourcePos_)
{
}

InvokeExprNode::InvokeExprNode(const soul::ast::SourcePos& sourcePos_, Node* subject_) : ListNode(NodeKind::invokeExprNode, sourcePos_), subject(subject_)
{
}

Node* InvokeExprNode::Clone() const
{
    Node* clonedSubject = nullptr;
    if (subject)
    {
        clonedSubject = subject->Clone();
    }
    InvokeExprNode* clone = new InvokeExprNode(GetSourcePos(), clonedSubject);
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void InvokeExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void InvokeExprNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(subject.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void InvokeExprNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    subject.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

PairNode::PairNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::pairNode, sourcePos_, nullptr, nullptr)
{
}

PairNode::PairNode(const soul::ast::SourcePos& sourcePos_, Node* left_, Node* right_) : BinaryNode(NodeKind::pairNode, sourcePos_, left_, right_)
{
}

Node* PairNode::Clone() const
{
    PairNode* clone = new PairNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
}

void PairNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DotNode::DotNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::dotNode, sourcePos_)
{
}

Node* DotNode::Clone() const
{
    DotNode* clone = new DotNode(GetSourcePos());
    return clone;
}

void DotNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrowNode::ArrowNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::arrowNode, sourcePos_)
{
}

Node* ArrowNode::Clone() const
{
    ArrowNode* clone = new ArrowNode(GetSourcePos());
    return clone;
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

Node* MemberExprNode::Clone() const
{
    MemberExprNode* clone = new MemberExprNode(GetSourcePos(), Child()->Clone(), op->Clone(), id->Clone());
    return clone;
}

void MemberExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void MemberExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(op.get());
    writer.Write(id.get());
}

void MemberExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    op.reset(reader.ReadNode());
    id.reset(reader.ReadNode());
}

PostfixIncExprNode::PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::postfixIncExprNode, sourcePos_, nullptr)
{
}

PostfixIncExprNode::PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_) : 
    UnaryNode(NodeKind::postfixIncExprNode, sourcePos_, child_), opPos(opPos_)
{
}

Node* PostfixIncExprNode::Clone() const
{
    PostfixIncExprNode* clone = new PostfixIncExprNode(GetSourcePos(), Child()->Clone(), opPos);
    return clone;
}

void PostfixIncExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PostfixIncExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(opPos);
}

void PostfixIncExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    opPos = reader.ReadSourcePos();
}

PostfixDecExprNode::PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::postfixDecExprNode, sourcePos_, nullptr)
{
}

PostfixDecExprNode::PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_) : 
    UnaryNode(NodeKind::postfixDecExprNode, sourcePos_, child_), opPos(opPos_)
{
}

Node* PostfixDecExprNode::Clone() const
{
    PostfixDecExprNode* clone = new PostfixDecExprNode(GetSourcePos(), Child()->Clone(), opPos);
    return clone;
}

void PostfixDecExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void PostfixDecExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(opPos);
}

void PostfixDecExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    opPos = reader.ReadSourcePos();
}

TypeIdExprNode::TypeIdExprNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::typeIdExprNode, sourcePos_, nullptr)
{
}

TypeIdExprNode::TypeIdExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    UnaryNode(NodeKind::typeIdExprNode, sourcePos_, child_), lpPos(lpPos_), rpPos(rpPos_)
{
}

Node* TypeIdExprNode::Clone() const
{
    TypeIdExprNode* clone = new TypeIdExprNode(GetSourcePos(), Child()->Clone(), lpPos, rpPos);
    return clone;
}

void TypeIdExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TypeIdExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void TypeIdExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

DynamicCastNode::DynamicCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::dynamicCastNode, sourcePos_)
{
}

Node* DynamicCastNode::Clone() const
{
    DynamicCastNode* clone = new DynamicCastNode(GetSourcePos());
    return clone;
}

void DynamicCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

StaticCastNode::StaticCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::staticCastNode, sourcePos_)
{
}

Node* StaticCastNode::Clone() const
{
    StaticCastNode* clone = new StaticCastNode(GetSourcePos());
    return clone;
}

void StaticCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ReinterpretCastNode::ReinterpretCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::reinterpretCastNode, sourcePos_)
{
}

Node* ReinterpretCastNode::Clone() const
{
    ReinterpretCastNode* clone = new ReinterpretCastNode(GetSourcePos());
    return clone;
}

void ReinterpretCastNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConstCastNode::ConstCastNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::constCastNode, sourcePos_)
{
}

Node* ConstCastNode::Clone() const
{
    ConstCastNode* clone = new ConstCastNode(GetSourcePos());
    return clone;
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

Node* CppCastExprNode::Clone() const
{
    CppCastExprNode* clone = new CppCastExprNode(GetSourcePos(), typeId->Clone(), Child()->Clone(), op->Clone(), laPos, raPos, lpPos, rpPos);
    return clone;
}

void CppCastExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void CppCastExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(typeId.get());
    writer.Write(op.get());
    writer.Write(laPos);
    writer.Write(raPos);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void CppCastExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    typeId.reset(reader.ReadNode());
    op.reset(reader.ReadNode());
    laPos = reader.ReadSourcePos();
    raPos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

ThisNode::ThisNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::thisNode, sourcePos_)
{
}

Node* ThisNode::Clone() const
{
    ThisNode* clone = new ThisNode(GetSourcePos());
    return clone;
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

Node* ParenthesizedExprNode::Clone() const
{
    ParenthesizedExprNode* clone = new ParenthesizedExprNode(GetSourcePos(), Child()->Clone(), lpPos, rpPos);
    return clone;
}

void ParenthesizedExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ParenthesizedExprNode::Write(Writer& writer)
{
    UnaryNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ParenthesizedExprNode::Read(Reader& reader)
{
    UnaryNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

FoldExprNode::FoldExprNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::foldExprNode, sourcePos_)
{
}

Node* FoldExprNode::Clone() const
{
    FoldExprNode* clone = new FoldExprNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    clone->SetLParenPos(lpPos);
    clone->SetRParenPos(rpPos);
    return clone;
}

void FoldExprNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FoldExprNode::Write(Writer& writer)
{
    SequenceNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void FoldExprNode::Read(Reader& reader)
{
    SequenceNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

NewDeclaratorNode::NewDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::newDeclaratorNode, sourcePos_)
{
}

Node* NewDeclaratorNode::Clone() const
{
    NewDeclaratorNode* clone = new NewDeclaratorNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void NewDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ArrayNewDeclaratorNode::ArrayNewDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::arrayNewDeclaratorNode, sourcePos_)
{
}

Node* ArrayNewDeclaratorNode::Clone() const
{
    ArrayNewDeclaratorNode* clone = new ArrayNewDeclaratorNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void ArrayNewDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NewInitializerNode::NewInitializerNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::newInitializerNode, sourcePos_)
{
}

Node* NewInitializerNode::Clone() const
{
    NewInitializerNode* clone = new NewInitializerNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void NewInitializerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NewInitializerNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void NewInitializerNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

BracedInitListNode::BracedInitListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::bracedInitListNode, sourcePos_)
{
}

Node* BracedInitListNode::Clone() const
{
    BracedInitListNode* clone = new BracedInitListNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* DesignatedInitializerNode::Clone() const
{
    DesignatedInitializerNode* clone = new DesignatedInitializerNode(GetSourcePos(), Left()->Clone(), Right()->Clone());
    return clone;
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

Node* DesignatorNode::Clone() const 
{
    DesignatorNode* clone = new DesignatorNode(GetSourcePos(), Child()->Clone());
    return clone;
}

void DesignatorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
