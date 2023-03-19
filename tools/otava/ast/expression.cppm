// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.expression;

import std.core;
import otava.ast.node;

export namespace otava::ast {

class BinaryExprNode : public BinaryNode
{
public:
    BinaryExprNode(const soul::ast::SourcePos& sourcePos_);
    BinaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* op_, Node* left_, Node* right_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Op() const { return op.get(); }
private:
    std::unique_ptr<Node> op;
};

class UnaryExprNode : public UnaryNode
{
public:
    UnaryExprNode(const soul::ast::SourcePos& sourcePos_);
    UnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* op_, Node* child_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Op() const { return op.get(); }
private:
    std::unique_ptr<Node> op;
};

class ExpressionListNode : public ListNode
{
public:
    ExpressionListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void SetLParenPos(const soul::ast::SourcePos& lpPos_) { lpPos = lpPos_; }
    void SetRParenPos(const soul::ast::SourcePos& rpPos_) { rpPos = rpPos_; }
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class AssignmentInitNode : public UnaryNode
{
public:
    AssignmentInitNode(const soul::ast::SourcePos& sourcePos_);
    AssignmentInitNode(const soul::ast::SourcePos& sourcePos_, Node* initializer_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class YieldExprNode : public UnaryNode
{
public:
    YieldExprNode(const soul::ast::SourcePos& sourcePos_);
    YieldExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ThrowExprNode : public CompoundNode
{
public:
    ThrowExprNode(const soul::ast::SourcePos& sourcePos_);
    ThrowExprNode(const soul::ast::SourcePos& sourcePos_, Node* exception_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Exception() const { return exception.get(); }
private:
    std::unique_ptr<Node> exception;
};

class ConditionalExprNode : public CompoundNode
{
public:
    ConditionalExprNode(const soul::ast::SourcePos& sourcePos_);
    ConditionalExprNode(const soul::ast::SourcePos& sourcePos_, Node* condition_, Node* quest_, Node* thenExpr_, Node* colon_, Node* elseExpr_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Condition() const { return condition.get(); }
    Node* Quest() const { return quest.get(); }
    Node* ThenExpr() const { return thenExpr.get(); }
    Node* Colon() const { return colon.get(); }
    Node* ElseExpr() const { return elseExpr.get(); }
private:
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> quest;
    std::unique_ptr<Node> thenExpr;
    std::unique_ptr<Node> colon;
    std::unique_ptr<Node> elseExpr;
};

class AssignNode : public Node
{
public:
    AssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PlusAssignNode : public Node
{
public:
    PlusAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class MinusAssignNode : public Node
{
public:
    MinusAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class MulAssignNode : public Node
{
public:
    MulAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DivAssignNode : public Node
{
public:
    DivAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ModAssignNode : public Node
{
public:
    ModAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class XorAssignNode : public Node
{
public:
    XorAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AndAssignNode : public Node
{
public:
    AndAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class OrAssignNode : public Node
{
public:
    OrAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ShiftLeftAssignNode : public Node
{
public:
    ShiftLeftAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ShiftRightAssignNode : public Node
{
public:
    ShiftRightAssignNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DisjunctionNode : public Node
{
public:
    DisjunctionNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConjunctionNode : public Node
{
public:
    ConjunctionNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class InclusiveOrNode : public Node
{
public:
    InclusiveOrNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ExclusiveOrNode : public Node
{
public:
    ExclusiveOrNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AndNode : public Node
{
public:
    AndNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class EqualNode : public Node
{
public:
    EqualNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NotEqualNode : public Node
{
public:
    NotEqualNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class LessNode : public Node
{
public:
    LessNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class GreaterNode : public Node
{
public:
    GreaterNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class LessOrEqualNode : public Node
{
public:
    LessOrEqualNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class GreaterOrEqualNode : public Node
{
public:
    GreaterOrEqualNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class CompareNode : public Node
{
public:
    CompareNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ShiftLeftNode : public Node
{
public:
    ShiftLeftNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ShiftRightNode : public Node
{
public:
    ShiftRightNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PlusNode : public Node
{
public:
    PlusNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class MinusNode : public Node
{
public:
    MinusNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class MulNode : public Node
{
public:
    MulNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DivNode : public Node
{
public:
    DivNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ModNode : public Node
{
public:
    ModNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DotStarNode : public Node
{
public:
    DotStarNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ArrowStarNode : public Node
{
public:
    ArrowStarNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class CastExprNode : public UnaryNode
{
public:
    CastExprNode(const soul::ast::SourcePos& sourcePos_);
    CastExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* TypeId() const { return typeId.get(); }
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> typeId;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class DerefNode : public Node
{
public:
    DerefNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AddrOfNode : public Node
{
public:
    AddrOfNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NotNode : public Node
{
public:
    NotNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ComplementNode : public Node
{
public:
    ComplementNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PrefixIncNode : public Node
{
public:
    PrefixIncNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class PrefixDecNode : public Node
{
public:
    PrefixDecNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AwaitExprNode : public UnaryNode
{
public:
    AwaitExprNode(const soul::ast::SourcePos& sourcePos_);
    AwaitExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class SizeOfTypeExprNode : public UnaryNode
{
public:
    SizeOfTypeExprNode(const soul::ast::SourcePos& sourcePos_);
    SizeOfTypeExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class SizeOfPackExprNode : public UnaryNode
{
public:
    SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_);
    SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_, Node* idNode_, const soul::ast::SourcePos& ellipsisPos_, 
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& EllipsisPos() const { return ellipsisPos; }
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos ellipsisPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class SizeOfUnaryExprNode : public UnaryNode
{
public:
    SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_);
    SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AlignOfExprNode : public UnaryNode
{
public:
    AlignOfExprNode(const soul::ast::SourcePos& sourcePos_);
    AlignOfExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NoexceptExprNode : public UnaryNode
{
public:
    NoexceptExprNode(const soul::ast::SourcePos& sourcePos_);
    NoexceptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NewExprNode : public UnaryNode
{
public:
    NewExprNode(const soul::ast::SourcePos& sourcePos_);
    NewExprNode(const soul::ast::SourcePos& sourcePos_, Node* placement_, Node* child_, Node* initializer_, Node* colonColonHead_, const soul::ast::SourcePos& newPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* ColonColonHead() const { return colonColonHead.get(); }
    Node* Placement() const { return placement.get(); }
    Node* Initializer() const { return initializer.get(); }
    const soul::ast::SourcePos& NewPos() const { return newPos; }
private:
    std::unique_ptr<Node> colonColonHead;
    std::unique_ptr<Node> placement;
    std::unique_ptr<Node> initializer;
    soul::ast::SourcePos newPos;
};

class NewPlacementNode : public ListNode
{
public:
    NewPlacementNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void SetLParenPos(const soul::ast::SourcePos& lpPos_) { lpPos = lpPos_; }
    void SetRParenPos(const soul::ast::SourcePos& rpPos_) { rpPos = rpPos_; }
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class ParenNewTypeIdNode : public UnaryNode
{
public:
    ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_);
    ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NewTypeIdNode : public CompoundNode
{
public:
    NewTypeIdNode(const soul::ast::SourcePos& sourcePos_);
    NewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifierSeq_, Node* newDeclarator_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* TypeSpecifierSeq() const { return typeSpecifierSeq.get(); }
    Node* NewDeclarator() const { return newDeclarator.get(); }
private:
    std::unique_ptr<Node> typeSpecifierSeq;
    std::unique_ptr<Node> newDeclarator;
};

class ArrayDeletePtrNode : public UnaryNode
{
public:
    ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_);
    ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_, 
        const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* ColonColonHead() const { return colonColonHead.get(); }
    const soul::ast::SourcePos& DeletePos() const { return deletePos; }
    const soul::ast::SourcePos& LBracketPos() const { return lbPos; }
    const soul::ast::SourcePos& RBracketPos() const { return rbPos; }
private:
    std::unique_ptr<Node> colonColonHead;
    soul::ast::SourcePos deletePos;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class DeletePtrNode : public UnaryNode
{
public:
    DeletePtrNode(const soul::ast::SourcePos& sourcePos_);
    DeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* ColonColonHead() const { return colonColonHead.get(); }
    const soul::ast::SourcePos& DeletePos() const { return deletePos; }
private:
    std::unique_ptr<Node> colonColonHead;
    soul::ast::SourcePos deletePos;
};

class SubscriptExprNode : public UnaryNode
{
public:
    SubscriptExprNode(const soul::ast::SourcePos& sourcePos_);
    SubscriptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* index_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Index() const { return index.get(); }
    const soul::ast::SourcePos& LBracketPos() const { return lbPos; }
    const soul::ast::SourcePos& RBracketPos() const { return rbPos; }
private:
    std::unique_ptr<Node> index;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class InvokeExprNode : public ListNode
{
public:
    InvokeExprNode(const soul::ast::SourcePos& sourcePos_);
    InvokeExprNode(const soul::ast::SourcePos& sourcePos_, Node* subject_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Subject() const { return subject.get(); }
    void SetLParenPos(const soul::ast::SourcePos& lpPos_) { lpPos = lpPos_; }
    void SetRParenPos(const soul::ast::SourcePos& rpPos_) { rpPos = rpPos_; }
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> subject;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class PairNode : public BinaryNode
{
public:
    PairNode(const soul::ast::SourcePos& sourcePos_);
    PairNode(const soul::ast::SourcePos& sourcePos_, Node* left_, Node* right_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DotNode : public Node
{
public:
    DotNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ArrowNode : public Node
{
public:
    ArrowNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class MemberExprNode : public UnaryNode
{
public:
    MemberExprNode(const soul::ast::SourcePos& sourcePos_);
    MemberExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* op_, Node* id_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* Op() const { return op.get(); }
    Node* Id() const { return id.get(); }
private:
    std::unique_ptr<Node> op;
    std::unique_ptr<Node> id;
};

class PostfixIncExprNode : public UnaryNode
{
public:
    PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_);
    PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& OpPos() const { return opPos; }
private:
    soul::ast::SourcePos opPos;
};

class PostfixDecExprNode : public UnaryNode
{
public:
    PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_);
    PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& OpPos() const { return opPos; }
private:
    soul::ast::SourcePos opPos;
};

class TypeIdExprNode : public UnaryNode
{
public:
    TypeIdExprNode(const soul::ast::SourcePos& sourcePos_);
    TypeIdExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class DynamicCastNode : public Node
{
public:
    DynamicCastNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class StaticCastNode : public Node
{
public:
    StaticCastNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ReinterpretCastNode : public Node
{
public:
    ReinterpretCastNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConstCastNode : public Node
{
public:
    ConstCastNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class CppCastExprNode : public UnaryNode
{
public:
    CppCastExprNode(const soul::ast::SourcePos& sourcePos_);
    CppCastExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, Node* child_, Node* op_, 
        const soul::ast::SourcePos& laPos_, const soul::ast::SourcePos& raPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    Node* TypeId() const { return typeId.get(); }
    Node* Op() const { return op.get(); }
    const soul::ast::SourcePos& LAnglePos() const { return laPos; }
    const soul::ast::SourcePos& RAnglePos() const { return raPos; }
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> typeId;
    std::unique_ptr<Node> op;
    soul::ast::SourcePos laPos;
    soul::ast::SourcePos raPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class ThisNode : public Node
{
public:
    ThisNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ParenthesizedExprNode : public UnaryNode
{
public:
    ParenthesizedExprNode(const soul::ast::SourcePos& sourcePos_);
    ParenthesizedExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class FoldExprNode : public SequenceNode
{
public:
    FoldExprNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void SetLParenPos(const soul::ast::SourcePos& lpPos_) { lpPos = lpPos_; }
    void SetRParenPos(const soul::ast::SourcePos& rpPos_) { rpPos = rpPos_; }
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NewDeclaratorNode : public SequenceNode
{
public:
    NewDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ArrayNewDeclaratorNode : public SequenceNode
{
public:
    ArrayNewDeclaratorNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NewInitializerNode : public ListNode
{
public:
    NewInitializerNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    void SetLParenPos(const soul::ast::SourcePos& lpPos_) { lpPos = lpPos_; }
    void SetRParenPos(const soul::ast::SourcePos& rpPos_) { rpPos = rpPos_; }
    const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class BracedInitListNode : public ListNode
{
public:
    BracedInitListNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DesignatedInitializerNode : public BinaryNode
{
public:
    DesignatedInitializerNode(const soul::ast::SourcePos& sourcePos_);
    DesignatedInitializerNode(const soul::ast::SourcePos& sourcePos_, Node* designator_, Node* initializer_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DesignatorNode : public UnaryNode
{
public:
    DesignatorNode(const soul::ast::SourcePos& sourcePos_);
    DesignatorNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

} // namespace otava::ast
