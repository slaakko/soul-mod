// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

export module soul.ast.cpp;

import std.core;
import util.code.formatter;

export namespace soul::ast::cpp {

using util::CodeFormatter;

class Visitor;

enum class Operator
{
    deref, addrOf, plus, minus, and_, or_, not_, cpl, dotStar, arrowStar, bitand_, bitxor, bitor_, mul, div, rem, shiftLeft, shiftRight,
    less, greater, lessOrEq, greaterOrEq, eq, notEq, comma,
    assign, mulAssign, divAssign, remAssign, plusAssign, minusAssign, shiftLeftAssign, shiftRightAssign, andAssign, xorAssign, orAssign
};

std::string OperatorStr(Operator op);

class Node
{
public:
    Node();
    virtual ~Node();
    virtual void Accept(Visitor& visitor) = 0;
    virtual void Write(CodeFormatter& formatter) = 0;
    virtual void Add(Node* node) {}
    virtual std::string ToString() const { return std::string(); }
};

class UnaryNode : public Node
{
public:
    UnaryNode(Node* child_);
    Node* Child() const { return child.get(); }
private:
    std::unique_ptr<Node> child;
};

class BinaryNode : public Node
{
public:
    BinaryNode(Node* left_, Node* right_);
    Node* Left() const { return left.get(); }
    Node* Right() const { return right.get(); }
private:
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};

class ThisNode : public Node
{
public:
    ThisNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override { return "this"; }
};

class IdExprNode : public Node
{
public:
    IdExprNode(const std::string& value_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override { return value; }
private:
    std::string value;
};

class IndexExprNode : public UnaryNode
{
public:
    IndexExprNode(Node* child_, Node* index_);
    Node* Index() const { return index.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    std::unique_ptr<Node> index;
};

class InvokeNode : public UnaryNode
{
public:
    InvokeNode(Node* child_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    void Add(Node* node) override;
    const std::vector<std::unique_ptr<Node>>& Args() const { return args; }
    std::string ToString() const override;
private:
    std::vector<std::unique_ptr<Node>> args;
};

class MemberAccessNode : public UnaryNode
{
public:
    MemberAccessNode(Node* child_, Node* member_);
    Node* Member() const { return member.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    std::unique_ptr<Node> member;
};

class PtrMemberAccessNode : public UnaryNode
{
public:
    PtrMemberAccessNode(Node* child_, Node* member_);
    Node* Member() const { return member.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    std::unique_ptr<Node> member;
};

class PostIncrementNode : public UnaryNode
{
public:
    PostIncrementNode(Node* child_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
};

class PostDecrementNode : public UnaryNode
{
public:
    PostDecrementNode(Node* child_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
};

class CppCastNode : public Node
{
public:
    CppCastNode();
};

class StaticCastNode : public CppCastNode
{
public:
    StaticCastNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override { return "static_cast"; }
};

class DynamicCastNode : public CppCastNode
{
public:
    DynamicCastNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override { return "dynamic_cast"; }
};

class ReinterpretCastNode : public CppCastNode
{
public:
    ReinterpretCastNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override { return "reinterpret_cast"; }
};

class ConstCastNode : public CppCastNode
{
public:
    ConstCastNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override { return "const_cast"; }
};

class PostCastNode : public UnaryNode
{
public:
    PostCastNode(CppCastNode* cppCastNode_, Node* type_, Node* child_);
    Node* Type() const { return type.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    std::unique_ptr<CppCastNode> cppCastNode;
    std::unique_ptr<Node> type;
};

class TypeIdExprNode : public UnaryNode
{
public:
    TypeIdExprNode(Node* child_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
};

class PreIncrementNode : public UnaryNode
{
public:
    PreIncrementNode(Node* child_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
};

class PreDecrementNode : public UnaryNode
{
public:
    PreDecrementNode(Node* child_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
};

class UnaryOpExprNode : public UnaryNode
{
public:
    UnaryOpExprNode(Operator op_, Node* child_);
    Operator Op() const { return op; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    Operator op;
};

class SizeOfNode : public UnaryNode
{
public:
    SizeOfNode(Node* child_, bool parens_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    bool parens;
};

class CastNode : public UnaryNode
{
public:
    CastNode(Node* type_, Node* child_);
    Node* Type() const { return type.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    std::unique_ptr<Node> type;
};

class BinaryOpExprNode : public BinaryNode
{
public:
    BinaryOpExprNode(Operator op_, Node* left_, Node* right_);
    Operator Op() const { return op; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    Operator op;
};

class ConditionalNode : public Node
{
public:
    ConditionalNode(Node* condition_, Node* thenExpr_, Node* elseExpr_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    Node* Condition() const { return condition.get(); }
    Node* ThenExpr() const { return thenExpr.get(); }
    Node* ElseExpr() const { return elseExpr.get(); }
    std::string ToString() const override;
private:
    std::unique_ptr<Node> condition;
    std::unique_ptr<Node> thenExpr;
    std::unique_ptr<Node> elseExpr;
};

class ThrowExprNode : public Node
{
public:
    ThrowExprNode(Node* exception_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    std::unique_ptr<Node> exception;
};

class NewNode : public Node
{
public:
    NewNode(bool global_);
    bool Global() const { return global; }
    bool Parens() const { return parens; }
    void SetParens(bool parens_) { parens = parens_; }
    void BeginAddToPlacement() { addToPlacement = true; }
    void EndAddToPlacement() { addToPlacement = false; }
    void BeginAddToInitializer() { addToInitializer = true; }
    void EndAddToInitializer() { addToPlacement = false; }
    void Add(Node* node) override;
    void SetTypeId(Node* typeId_);
    const std::vector<std::unique_ptr<Node>>& Placement() const { return placement; }
    const std::vector<std::unique_ptr<Node>>& Initializer() const { return initializer; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    bool global;
    std::vector<std::unique_ptr<Node>> placement;
    std::unique_ptr<Node> typeId;
    bool parens;
    bool addToPlacement;
    bool addToInitializer;
    std::vector<std::unique_ptr<Node>> initializer;
};

class DeleteNode : public UnaryNode
{
public:
    DeleteNode(bool global_, bool isArray_, Node* child_);
    bool Global() const { return global; }
    bool IsArray() const { return isArray; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    bool global;
    bool isArray;
};

class ParenExprNode : public UnaryNode
{
public:
    ParenExprNode(Node* child_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
};

class LiteralNode : public Node
{
public:
    LiteralNode(const std::string& rep_);
    const std::string& Rep() const { return rep; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override { return rep; }
private:
    std::string rep;
};

class StatementNode : public Node
{
public:
    StatementNode();
    virtual bool IsCompoundStatementNode() const { return false; }
};

class LabeledStatementNode : public StatementNode
{
public:
    LabeledStatementNode(const std::string& label_, StatementNode* stmt_);
    const std::string& Label() const { return label; }
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::string label;
    std::unique_ptr<StatementNode> stmt;
};

class CaseStatementNode : public StatementNode
{
public:
    CaseStatementNode(Node* caseExpr_, StatementNode* stmt_);
    Node* CaseExpr() const { return caseExpr.get(); }
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> caseExpr;
    std::unique_ptr<StatementNode> stmt;
};

class DefaultStatementNode : public StatementNode
{
public:
    DefaultStatementNode(StatementNode* stmt_);
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<StatementNode> stmt;
};

class EmptyStatementNode : public StatementNode
{
public:
    EmptyStatementNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
};

class ExpressionStatementNode : public StatementNode
{
public:
    ExpressionStatementNode(Node* expr_);
    Node* Expr() const { return expr.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> expr;
};

class CompoundStatementNode : public StatementNode
{
public:
    CompoundStatementNode();
    void InsertFront(StatementNode* stmt);
    void Add(StatementNode* stmt);
    const std::vector<std::unique_ptr<StatementNode>>& Statements() const { return statements; };
    bool IsCompoundStatementNode() const override { return true; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::vector<std::unique_ptr<StatementNode>> statements;
};

class IfStatementNode : public StatementNode
{
public:
    IfStatementNode(Node* cond_, StatementNode* thenStmt_, StatementNode* elseStmt_);
    Node* Cond() const { return cond.get(); }
    StatementNode* ThenStmt() const { return thenStmt.get(); }
    StatementNode* ElseStmt() const { return elseStmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<StatementNode> thenStmt;
    std::unique_ptr<StatementNode> elseStmt;
};

class SwitchStatementNode : public StatementNode
{
public:
    SwitchStatementNode(Node* cond_, StatementNode* stmt_);
    Node* Cond() const { return cond.get(); }
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<StatementNode> stmt;
};

class WhileStatementNode : public StatementNode
{
public:
    WhileStatementNode(Node* cond_, StatementNode* stmt_);
    Node* Cond() const { return cond.get(); }
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<StatementNode> stmt;
};

class DoStatementNode : public StatementNode
{
public:
    DoStatementNode(Node* cond_, StatementNode* stmt_);
    Node* Cond() const { return cond.get(); }
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<StatementNode> stmt;
};

class ForStatementNode : public StatementNode
{
public:
    ForStatementNode(Node* init_, Node* cond_, Node* iter_, StatementNode* stmt_);
    Node* Init() const { return init.get(); }
    Node* Cond() const { return cond.get(); }
    Node* Iter() const { return iter.get(); }
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> init;
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> iter;
    std::unique_ptr<StatementNode> stmt;
};

class BreakStatementNode : public StatementNode
{
public:
    BreakStatementNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
};

class ContinueStatementNode : public StatementNode
{
public:
    ContinueStatementNode();
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
};

class GotoStatementNode : public StatementNode
{
public:
    GotoStatementNode(const std::string& target_);
    const std::string& Target() const { return target; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::string target;
};

class ReturnStatementNode : public StatementNode
{
public:
    ReturnStatementNode(Node* expr_);
    Node* Expr() const { return expr.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> expr;
};

class TypeIdNode;

class ForRangeDeclarationNode : public Node
{
public:
    ForRangeDeclarationNode(TypeIdNode* typeId_, const std::string& declarator_);
    TypeIdNode* TypeId() const { return typeId.get(); }
    const std::string& Declarator() const { return declarator; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<TypeIdNode> typeId;
    std::string declarator;
};

class RangeForStatementNode : public StatementNode
{
public:
    RangeForStatementNode(ForRangeDeclarationNode* declaration_, Node* container_, StatementNode* stmt_);
    ForRangeDeclarationNode* Declaration() const { return declaration.get(); }
    Node* Container() const { return container.get(); }
    StatementNode* Stmt() const { return stmt.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<ForRangeDeclarationNode> declaration;
    std::unique_ptr<Node> container;
    std::unique_ptr<StatementNode> stmt;
};

class DeclarationStatementNode : public StatementNode
{
public:
    DeclarationStatementNode(Node* declaration_);
    Node* Declaration() const { return declaration.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<Node> declaration;
};

class ExceptionDeclarationNode : public Node
{
public:
    ExceptionDeclarationNode(TypeIdNode* typeId_, const std::string& declarator_, bool catchAll_);
    TypeIdNode* TypeId() const { return typeId.get(); }
    const std::string& Declarator() const { return declarator; }
    bool CatchAll() const { return catchAll; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<TypeIdNode> typeId;
    std::string declarator;
    bool catchAll;
};

class HandlerNode : public Node
{
public:
    HandlerNode(ExceptionDeclarationNode* exceptionDeclaration_, CompoundStatementNode* handlerBlock_);
    ExceptionDeclarationNode* ExceptionDeclaration() const { return exceptionDeclaration.get(); }
    CompoundStatementNode* HandlerBlock() const { return handlerBlock.get(); }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<ExceptionDeclarationNode> exceptionDeclaration;
    std::unique_ptr<CompoundStatementNode> handlerBlock;
};

class TryStatementNode : public StatementNode
{
public:
    TryStatementNode(CompoundStatementNode* tryBlock_);
    CompoundStatementNode* TryBlock() const { return tryBlock.get(); }
    void AddHandler(HandlerNode* handler);
    const std::vector<std::unique_ptr<HandlerNode>>& Handlers() const { return handlers; }
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
private:
    std::unique_ptr<CompoundStatementNode> tryBlock;
    std::vector<std::unique_ptr<HandlerNode>> handlers;
};

class TypeSpecifier : public Node
{
public:
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
};

class TypeIdNode : public Node
{
public:
    TypeIdNode();
    void Add(TypeSpecifier* typeSpecifier);
    const std::vector<std::unique_ptr<TypeSpecifier>>& TypeSpecifiers() const { return typeSpecifiers; }
    const std::string& Declarator() const { return declarator; }
    void SetDeclarator(const std::string& declarator_);
    void Accept(Visitor& visitor) override;
    void Write(CodeFormatter& formatter) override;
    std::string ToString() const override;
private:
    std::vector<std::unique_ptr<TypeSpecifier>> typeSpecifiers;
    std::string declarator;
};

class Visitor
{
public:
    virtual void Visit(ThisNode& node) {}
    virtual void Visit(IdExprNode& node) {}
    virtual void Visit(IndexExprNode& node) {}
    virtual void Visit(InvokeNode& node) {}
    virtual void Visit(MemberAccessNode& node) {}
    virtual void Visit(PtrMemberAccessNode& node) {}
    virtual void Visit(PostIncrementNode& node) {}
    virtual void Visit(PostDecrementNode& node) {}
    virtual void Visit(StaticCastNode& node) {}
    virtual void Visit(DynamicCastNode& node) {}
    virtual void Visit(ReinterpretCastNode& node) {}
    virtual void Visit(ConstCastNode& node) {}
    virtual void Visit(PostCastNode& node) {}
    virtual void Visit(TypeIdExprNode& node) {}
    virtual void Visit(PreIncrementNode& node) {}
    virtual void Visit(PreDecrementNode& node) {}
    virtual void Visit(UnaryOpExprNode& node) {}
    virtual void Visit(SizeOfNode& node) {}
    virtual void Visit(CastNode& node) {}
    virtual void Visit(BinaryOpExprNode& node) {}
    virtual void Visit(ConditionalNode& node) {}
    virtual void Visit(ThrowExprNode& node) {}
    virtual void Visit(NewNode& node) {}
    virtual void Visit(DeleteNode& node) {}
    virtual void Visit(ParenExprNode& node) {}
    virtual void Visit(LiteralNode& node) {}
    virtual void Visit(LabeledStatementNode& node) {}
    virtual void Visit(CaseStatementNode& node) {}
    virtual void Visit(DefaultStatementNode& node) {}
    virtual void Visit(EmptyStatementNode& node) {}
    virtual void Visit(ExpressionStatementNode& node) {}
    virtual void Visit(CompoundStatementNode& node) {}
    virtual void Visit(IfStatementNode& node) {}
    virtual void Visit(SwitchStatementNode& node) {}
    virtual void Visit(WhileStatementNode& node) {}
    virtual void Visit(DoStatementNode& node) {}
    virtual void Visit(ForStatementNode& node) {}
    virtual void Visit(BreakStatementNode& node) {}
    virtual void Visit(ContinueStatementNode& node) {}
    virtual void Visit(GotoStatementNode& node) {}
    virtual void Visit(ReturnStatementNode& node) {}
    virtual void Visit(ForRangeDeclarationNode& node) {}
    virtual void Visit(RangeForStatementNode& node) {}
    virtual void Visit(DeclarationStatementNode& node) {}
    virtual void Visit(ExceptionDeclarationNode& node) {}
    virtual void Visit(HandlerNode& node) {}
    virtual void Visit(TryStatementNode& node) {}
    virtual void Visit(TypeIdNode& node);
};

} // namespace soul::ast::cpp
