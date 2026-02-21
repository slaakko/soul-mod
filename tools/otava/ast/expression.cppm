// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.expression;

import std;
import otava.ast.node;

export namespace otava::ast {

class BinaryExprNode : public BinaryNode
{
public:
    BinaryExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    BinaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* op_, Node* left_, Node* right_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Op() const noexcept { return op.get(); }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> op;
};

class UnaryExprNode : public UnaryNode
{
public:
    UnaryExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    UnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* op_, Node* child_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Op() const noexcept { return op.get(); }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> op;
};

class ExpressionListNode : public ListNode
{
public:
    ExpressionListNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetLParenPos(const soul::ast::SourcePos& lpPos_) noexcept { lpPos = lpPos_; }
    inline void SetRParenPos(const soul::ast::SourcePos& rpPos_) noexcept { rpPos = rpPos_; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    std::u32string Str() const override;
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class AssignmentInitNode : public UnaryNode
{
public:
    AssignmentInitNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AssignmentInitNode(const soul::ast::SourcePos& sourcePos_, Node* initializer_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override;
};

class YieldExprNode : public UnaryNode
{
public:
    YieldExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    YieldExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ConditionalExprNode : public CompoundNode
{
public:
    ConditionalExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ConditionalExprNode(const soul::ast::SourcePos& sourcePos_, Node* condition_, Node* quest_, Node* thenExpr_, Node* colon_, Node* elseExpr_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Condition() const noexcept { return condition.get(); }
    inline Node* Quest() const noexcept { return quest.get(); }
    inline Node* ThenExpr() const noexcept { return thenExpr.get(); }
    inline Node* Colon() const noexcept { return colon.get(); }
    inline Node* ElseExpr() const noexcept { return elseExpr.get(); }
    std::u32string Str() const override;
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
    AssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"="; };
};

class PlusAssignNode : public Node
{
public:
    PlusAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"+="; };
};

class MinusAssignNode : public Node
{
public:
    MinusAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"-="; };
};

class MulAssignNode : public Node
{
public:
    MulAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"*="; };
};

class DivAssignNode : public Node
{
public:
    DivAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"/="; };
};

class ModAssignNode : public Node
{
public:
    ModAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"%="; };
};

class XorAssignNode : public Node
{
public:
    XorAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"^="; };
};

class AndAssignNode : public Node
{
public:
    AndAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"&="; };
};

class OrAssignNode : public Node
{
public:
    OrAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"|="; };
};

class ShiftLeftAssignNode : public Node
{
public:
    ShiftLeftAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"<<="; };
};

class ShiftRightAssignNode : public Node
{
public:
    ShiftRightAssignNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U">>="; };
};

class DisjunctionNode : public Node
{
public:
    DisjunctionNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"||"; };
};

class ConjunctionNode : public Node
{
public:
    ConjunctionNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"&&"; };
};

class InclusiveOrNode : public Node
{
public:
    InclusiveOrNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"|"; };
};

class ExclusiveOrNode : public Node
{
public:
    ExclusiveOrNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"^"; };
};

class AndNode : public Node
{
public:
    AndNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"&"; };
};

class EqualNode : public Node
{
public:
    EqualNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"=="; };
};

class NotEqualNode : public Node
{
public:
    NotEqualNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"!=="; };
};

class LessNode : public Node
{
public:
    LessNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"<"; };
};

class GreaterNode : public Node
{
public:
    GreaterNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U">"; };
};

class LessOrEqualNode : public Node
{
public:
    LessOrEqualNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"<="; };
};

class GreaterOrEqualNode : public Node
{
public:
    GreaterOrEqualNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U">="; };
};

class CompareNode : public Node
{
public:
    CompareNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"<=>"; };
};

class ShiftLeftNode : public Node
{
public:
    ShiftLeftNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"<<"; };
};

class ShiftRightNode : public Node
{
public:
    ShiftRightNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U">>"; };
};

class PlusNode : public Node
{
public:
    PlusNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"+"; };
};

class MinusNode : public Node
{
public:
    MinusNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"-"; };
};

class MulNode : public Node
{
public:
    MulNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"*"; };
};

class DivNode : public Node
{
public:
    DivNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"/"; };
};

class ModNode : public Node
{
public:
    ModNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"%"; };
};

class DotStarNode : public Node
{
public:
    DotStarNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U".*"; };
};

class ArrowStarNode : public Node
{
public:
    ArrowStarNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"->"; };
};

class CastExprNode : public UnaryNode
{
public:
    CastExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    CastExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    inline Node* TypeId() const noexcept { return typeId.get(); }
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> typeId;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class DerefNode : public Node
{
public:
    DerefNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"*"; }
};

class AddrOfNode : public Node
{
public:
    AddrOfNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"&"; }
};

class NotNode : public Node
{
public:
    NotNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"!"; }
};

class ComplementNode : public Node
{
public:
    ComplementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"~"; }
};

class PrefixIncNode : public Node
{
public:
    PrefixIncNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"++"; }
};

class PrefixDecNode : public Node
{
public:
    PrefixDecNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"--"; }
};

class AwaitExprNode : public UnaryNode
{
public:
    AwaitExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AwaitExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class SizeOfTypeExprNode : public UnaryNode
{
public:
    SizeOfTypeExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    SizeOfTypeExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class SizeOfPackExprNode : public UnaryNode
{
public:
    SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    SizeOfPackExprNode(const soul::ast::SourcePos& sourcePos_, Node* idNode_, const soul::ast::SourcePos& ellipsisPos_, 
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& EllipsisPos() const noexcept { return ellipsisPos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos ellipsisPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class SizeOfUnaryExprNode : public UnaryNode
{
public:
    SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    SizeOfUnaryExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class AlignOfExprNode : public UnaryNode
{
public:
    AlignOfExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    AlignOfExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NoexceptExprNode : public UnaryNode
{
public:
    NoexceptExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    NoexceptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NewExprNode : public UnaryNode
{
public:
    NewExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    NewExprNode(const soul::ast::SourcePos& sourcePos_, Node* placement_, Node* child_, Node* initializer_, Node* colonColonHead_, 
        const soul::ast::SourcePos& newPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ColonColonHead() const noexcept { return colonColonHead.get(); }
    inline Node* Placement() const noexcept { return placement.get(); }
    inline Node* Initializer() const noexcept { return initializer.get(); }
    inline const soul::ast::SourcePos& NewPos() const noexcept { return newPos; }
private:
    std::unique_ptr<Node> colonColonHead;
    std::unique_ptr<Node> placement;
    std::unique_ptr<Node> initializer;
    soul::ast::SourcePos newPos;
};

class NewPlacementNode : public ListNode
{
public:
    NewPlacementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetLParenPos(const soul::ast::SourcePos& lpPos_) noexcept { lpPos = lpPos_; }
    inline void SetRParenPos(const soul::ast::SourcePos& rpPos_) noexcept { rpPos = rpPos_; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class ParenNewTypeIdNode : public UnaryNode
{
public:
    ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ParenNewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NewTypeIdNode : public CompoundNode
{
public:
    NewTypeIdNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    NewTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifierSeq_, Node* newDeclarator_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeSpecifierSeq() const noexcept { return typeSpecifierSeq.get(); }
    inline Node* NewDeclarator() const noexcept { return newDeclarator.get(); }
private:
    std::unique_ptr<Node> typeSpecifierSeq;
    std::unique_ptr<Node> newDeclarator;
};

class ArrayDeletePtrNode : public UnaryNode
{
public:
    ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ArrayDeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_, 
        const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ColonColonHead() const noexcept { return colonColonHead.get(); }
    inline const soul::ast::SourcePos& DeletePos() const noexcept { return deletePos; }
    inline const soul::ast::SourcePos& LBracketPos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const noexcept { return rbPos; }
private:
    std::unique_ptr<Node> colonColonHead;
    soul::ast::SourcePos deletePos;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class DeletePtrNode : public UnaryNode
{
public:
    DeletePtrNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DeletePtrNode(const soul::ast::SourcePos& sourcePos_, Node* ptr_, Node* colonColonHead_, const soul::ast::SourcePos& deletePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ColonColonHead() const noexcept { return colonColonHead.get(); }
    inline const soul::ast::SourcePos& DeletePos() const noexcept { return deletePos; }
private:
    std::unique_ptr<Node> colonColonHead;
    soul::ast::SourcePos deletePos;
};

class SubscriptExprNode : public UnaryNode
{
public:
    SubscriptExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    SubscriptExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* index_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Index() const noexcept { return index.get(); }
    inline const soul::ast::SourcePos& LBracketPos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const noexcept { return rbPos; }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> index;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class InvokeExprNode : public ListNode
{
public:
    InvokeExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    InvokeExprNode(const soul::ast::SourcePos& sourcePos_, Node* subject_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Subject() const noexcept { return subject.get(); }
    inline void SetLParenPos(const soul::ast::SourcePos& lpPos_) noexcept { lpPos = lpPos_; }
    inline void SetRParenPos(const soul::ast::SourcePos& rpPos_) noexcept { rpPos = rpPos_; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    inline bool IsCompileUnitInitFn() const noexcept { return compileUnitInitFn; }
    inline void SetCompileUnitInitFn() noexcept { compileUnitInitFn = true; }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> subject;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
    bool compileUnitInitFn;
};

class PairNode : public BinaryNode
{
public:
    PairNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    PairNode(const soul::ast::SourcePos& sourcePos_, Node* left_, Node* right_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DotNode : public Node
{
public:
    DotNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"."; }
};

class ArrowNode : public Node
{
public:
    ArrowNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"->"; }
};

class MemberExprNode : public UnaryNode
{
public:
    MemberExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    MemberExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, Node* op_, Node* id_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Op() const noexcept { return op.get(); }
    inline Node* Id() const noexcept { return id.get(); }
    std::u32string Str() const override;
private:
    std::unique_ptr<Node> op;
    std::unique_ptr<Node> id;
};

class PostfixIncExprNode : public UnaryNode
{
public:
    PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    PostfixIncExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& OpPos() const noexcept { return opPos; }
    std::u32string Str() const override;
private:
    soul::ast::SourcePos opPos;
};

class PostfixDecExprNode : public UnaryNode
{
public:
    PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    PostfixDecExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& opPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& OpPos() const noexcept { return opPos; }
    std::u32string Str() const override;
private:
    soul::ast::SourcePos opPos;
};

class TypeIdExprNode : public UnaryNode
{
public:
    TypeIdExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TypeIdExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    std::u32string Str() const override;
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class DynamicCastNode : public Node
{
public:
    DynamicCastNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"dynamic_cast"; }
};

class StaticCastNode : public Node
{
public:
    StaticCastNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"static_cast"; }
};

class ReinterpretCastNode : public Node
{
public:
    ReinterpretCastNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"reinterpret_cast"; }
};

class ConstCastNode : public Node
{
public:
    ConstCastNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"const_cast"; }
};

class CppCastExprNode : public UnaryNode
{
public:
    CppCastExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    CppCastExprNode(const soul::ast::SourcePos& sourcePos_, Node* typeId_, Node* child_, Node* op_, 
        const soul::ast::SourcePos& laPos_, const soul::ast::SourcePos& raPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeId() const noexcept { return typeId.get(); }
    inline Node* Op() const noexcept { return op.get(); }
    inline const soul::ast::SourcePos& LAnglePos() const noexcept { return laPos; }
    inline const soul::ast::SourcePos& RAnglePos() const noexcept { return raPos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    std::u32string Str() const override;
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
    ThisNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override { return U"this"; }
};

class ParenthesizedExprNode : public UnaryNode
{
public:
    ParenthesizedExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ParenthesizedExprNode(const soul::ast::SourcePos& sourcePos_, Node* child_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    std::u32string Str() const override;
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class FoldExprNode : public SequenceNode
{
public:
    FoldExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetLParenPos(const soul::ast::SourcePos& lpPos_) noexcept { lpPos = lpPos_; }
    inline void SetRParenPos(const soul::ast::SourcePos& rpPos_) noexcept { rpPos = rpPos_; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class NewDeclaratorNode : public SequenceNode
{
public:
    NewDeclaratorNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ArrayNewDeclaratorNode : public SequenceNode
{
public:
    ArrayNewDeclaratorNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class NewInitializerNode : public ListNode
{
public:
    NewInitializerNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline void SetLParenPos(const soul::ast::SourcePos& lpPos_) noexcept { lpPos = lpPos_; }
    inline void SetRParenPos(const soul::ast::SourcePos& rpPos_) noexcept { rpPos = rpPos_; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class BracedInitListNode : public ListNode
{
public:
    BracedInitListNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DesignatedInitializerNode : public BinaryNode
{
public:
    DesignatedInitializerNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DesignatedInitializerNode(const soul::ast::SourcePos& sourcePos_, Node* designator_, Node* initializer_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class DesignatorNode : public UnaryNode
{
public:
    DesignatorNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DesignatorNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class ThrowExprNode : public UnaryNode
{
public:
    ThrowExprNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ThrowExprNode(const soul::ast::SourcePos& sourcePos_, Node* expr__) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    std::u32string Str() const override;
};

} // namespace otava::ast
