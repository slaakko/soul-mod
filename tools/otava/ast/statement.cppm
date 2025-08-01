// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.statement;

import std;
import otava.ast.node;
import soul.ast.lexer.pos.pair;

export namespace otava::ast {

class LabeledStatementNode : public CompoundNode
{
public:
    LabeledStatementNode(const soul::ast::SourcePos& sourcePos_);
    LabeledStatementNode(const soul::ast::SourcePos& sourcePos_, Node* label_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& colonPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Label() const { return label.get(); }
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& ColonPos() const { return colonPos; }
private:
    std::unique_ptr<Node> label;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos colonPos;
};

class CaseStatementNode : public CompoundNode
{
public:
    CaseStatementNode(const soul::ast::SourcePos& sourcePos_);
    CaseStatementNode(const soul::ast::SourcePos& sourcePos_, Node* caseExpr_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& casePos_, const soul::ast::SourcePos& colonPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* CaseExpression() const { return caseExpr.get(); }
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& CasePos() const { return casePos; }
    inline const soul::ast::SourcePos& ColonPos() const { return colonPos; }
private:
    std::unique_ptr<Node> caseExpr;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos casePos;
    soul::ast::SourcePos colonPos;
};

class DefaultStatementNode : public CompoundNode
{
public:
    DefaultStatementNode(const soul::ast::SourcePos& sourcePos_);
    DefaultStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& defaultPos_, const soul::ast::SourcePos& colonPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& DefaultPos() const { return defaultPos; }
    inline const soul::ast::SourcePos& ColonPos() const { return colonPos; }
private:
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos defaultPos;
    soul::ast::SourcePos colonPos;
};

class CompoundStatementNode : public SequenceNode
{
public:
    CompoundStatementNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const { return attributes.get(); }
    inline void SetAttributes(Node* attributes_) { attributes.reset(attributes_); }
    void SetLexerPosPair(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair_);
    inline const soul::ast::lexer::pos::pair::LexerPosPair& GetLexerPosPair() const { return lexerPosPair; }
    inline void SetLBracePos(const soul::ast::SourcePos& lbPos_) { lbPos = lbPos_; }
    inline void SetRBracePos(const soul::ast::SourcePos& rbPos_) { rbPos = rbPos_; }
    inline const soul::ast::SourcePos& LBracePos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const { return rbPos; }
    int Level() const;
    inline void* FunctionScope() const { return functionScope; }
    inline void SetFunctionScope(void* functionScope_) { functionScope = functionScope_; }
private:
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
    soul::ast::lexer::pos::pair::LexerPosPair lexerPosPair;
    void* functionScope;
};

class IfStatementNode : public CompoundNode
{
public:
    IfStatementNode(const soul::ast::SourcePos& sourcePos_);
    IfStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* thenStmt_, Node* elseStmt_, Node* attributes_,
        const soul::ast::SourcePos& ifPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_, const soul::ast::SourcePos& constExprPos_, 
        const soul::ast::SourcePos& elsePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* InitStatement() const { return initStmt.get(); }
    inline Node* Condition() const { return cond.get(); }
    inline Node* ThenStatement() const { return thenStmt.get(); }
    inline Node* ElseStatement() const { return elseStmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& IfPos() const { return ifPos; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
    inline const soul::ast::SourcePos& ConstExprSourcePos() const { return constExprPos; }
    inline const soul::ast::SourcePos& ElsePos() const { return elsePos; }
    inline bool IsConstExprIf() const { return constExprPos.IsValid(); }
private:
    std::unique_ptr<Node> initStmt;
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> thenStmt;
    std::unique_ptr<Node> elseStmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos ifPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
    soul::ast::SourcePos constExprPos;
    soul::ast::SourcePos elsePos;
};

class SwitchStatementNode : public CompoundNode
{
public:
    SwitchStatementNode(const soul::ast::SourcePos& sourcePos_);
    SwitchStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& switchPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* InitStatement() const { return initStmt.get(); }
    inline Node* Condition() const { return cond.get(); }
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& SwitchPos() const { return switchPos; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> initStmt;
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos switchPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class WhileStatementNode : public CompoundNode
{
public:
    WhileStatementNode(const soul::ast::SourcePos& sourcePos_);
    WhileStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& whilePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Condition() const { return cond.get(); }
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& WhilePos() const { return whilePos; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos whilePos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class DoStatementNode : public CompoundNode
{
public:
    DoStatementNode(const soul::ast::SourcePos& sourcePos_);
    DoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* expr_, Node* attributes_, Node* semicolon_,
        const soul::ast::SourcePos& doPos_, const soul::ast::SourcePos& whilePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Expression() const { return expr.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& DoPos() const { return doPos; }
    inline const soul::ast::SourcePos& WhilePos() const { return whilePos; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> expr;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos doPos;
    soul::ast::SourcePos whilePos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class RangeForStatementNode : public CompoundNode
{
public:
    RangeForStatementNode(const soul::ast::SourcePos& sourcePos_);
    RangeForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* declaration_, Node* initializer_, Node* stmt_, Node* attributes_,
        const soul::ast::SourcePos& forPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_, const soul::ast::SourcePos& colonPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* InitStatement() const { return initStmt.get(); }
    inline Node* Declaration() const { return declaration.get(); }
    inline Node* Initializer() const { return initializer.get(); }
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& ForPos() const { return forPos; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
    inline const soul::ast::SourcePos& ColonPos() const { return colonPos; }
private:
    std::unique_ptr<Node> initStmt;
    std::unique_ptr<Node> declaration;
    std::unique_ptr<Node> initializer;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos forPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
    soul::ast::SourcePos colonPos;
};

class ForRangeDeclarationNode : public BinaryNode
{
public:
    ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* declarator_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> attributes;
};

class StructuredBindingNode : public CompoundNode
{
public:
    StructuredBindingNode(const soul::ast::SourcePos& sourcePos_);
    StructuredBindingNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* refQualifier_, Node* identifiers_, Node* initializer_, Node* attributes_, Node* semicolon_,
        const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* DeclSpecifiers() const { return declSpecifiers.get(); }
    inline Node* RefQualifier() const { return refQualifier.get(); }
    inline Node* Identifiers() const { return identifiers.get(); }
    inline Node* Initializer() const { return initializer.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& LBracketPos() const { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const { return rbPos; }
private:
    std::unique_ptr<Node> declSpecifiers;
    std::unique_ptr<Node> refQualifier;
    std::unique_ptr<Node> identifiers;
    std::unique_ptr<Node> initializer;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
};

class ForStatementNode : public CompoundNode
{
public:
    ForStatementNode(const soul::ast::SourcePos& sourcePos_);
    ForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* loopExpr_, Node* stmt_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& forPos_,
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* InitStatement() const { return initStmt.get(); }
    inline Node* Condition() const { return cond.get(); }
    inline Node* LoopExpr() const { return loopExpr.get(); }
    inline Node* Statement() const { return stmt.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& ForPos() const { return forPos; }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> initStmt;
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> loopExpr;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos forPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class BreakStatementNode : public CompoundNode
{
public:
    BreakStatementNode(const soul::ast::SourcePos& sourcePos_);
    BreakStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& breakPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& BreakPos() const { return breakPos; }
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos breakPos;
};

class ContinueStatementNode : public CompoundNode
{
public:
    ContinueStatementNode(const soul::ast::SourcePos& sourcePos_);
    ContinueStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& continuePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& ContinuePos() const { return continuePos; }
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos continuePos;
};

class ReturnStatementNode : public CompoundNode
{
public:
    ReturnStatementNode(const soul::ast::SourcePos& sourcePos_);
    ReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& returnPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ReturnValue() const { return returnValue.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& ReturnPos() const { return returnPos; }
private:
    std::unique_ptr<Node> returnValue;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos returnPos;
};

class CoReturnStatementNode : public CompoundNode
{
public:
    CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_);
    CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& coReturnPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ReturnValue() const { return returnValue.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& CoReturnPos() const { return coReturnPos; }
private:
    std::unique_ptr<Node> returnValue;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos coReturnPos;
};

class GotoStatementNode : public CompoundNode
{
public:
    GotoStatementNode(const soul::ast::SourcePos& sourcePos_);
    GotoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* target_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& gotoPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Target() const { return target.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semimcolon() const { return semicolon.get(); }
    inline const soul::ast::SourcePos& GotoPos() const { return gotoPos; }
private:
    std::unique_ptr<Node> target;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos gotoPos;
};

class TryStatementNode : public CompoundNode
{
public:
    TryStatementNode(const soul::ast::SourcePos& sourcePos_);
    TryStatementNode(const soul::ast::SourcePos& sourcePos_, Node* tryBlock_, Node* handlers_, Node* attributes_, const soul::ast::SourcePos& tryPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TryBlock() const { return tryBlock.get(); }
    inline Node* Handlers() const { return handlers.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline const soul::ast::SourcePos& TryPos() const { return tryPos; }
private:
    std::unique_ptr<Node> tryBlock;
    std::unique_ptr<Node> handlers;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos tryPos;
};

class HandlerSequenceNode : public SequenceNode
{
public:
    HandlerSequenceNode(const soul::ast::SourcePos& sourcePos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class HandlerNode : public CompoundNode
{
public:
    HandlerNode(const soul::ast::SourcePos& sourcePos_);
    HandlerNode(const soul::ast::SourcePos& sourcePos_, Node* exception_, Node* catchBlock_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Exception() const { return exception.get(); }
    inline Node* CatchBlock() const { return catchBlock.get(); }
    inline const soul::ast::SourcePos& LParenPos() const { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const { return rpPos; }
private:
    std::unique_ptr<Node> exception;
    std::unique_ptr<Node> catchBlock;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class ExceptionDeclarationNode : public CompoundNode
{
public:
    ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_);
    ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_, Node* ellipsis_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeSpecifiers() const { return typeSpecifiers.get(); }
    inline Node* Declarator() const { return declarator.get(); }
    inline Node* Ellipsis() const { return ellipsis.get(); }
    inline Node* Attributes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> typeSpecifiers;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> ellipsis;
    std::unique_ptr<Node> attributes;
};

class ExpressionStatementNode : public CompoundNode
{
public:
    ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_);
    ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* attributes_, Node* semicolon_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Expression() const { return expr.get(); }
    inline Node* Attributes() const { return attributes.get(); }
    inline Node* Semicolon() const { return semicolon.get(); }
private:
    std::unique_ptr<Node> expr;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

class DeclarationStatementNode : public CompoundNode
{
public:
    DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_);
    DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_, Node* declaration_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Declaration() const { return declaration.get(); }
private:
    std::unique_ptr<Node> declaration;
};

class InitConditionNode : public CompoundNode
{
public:
    InitConditionNode(const soul::ast::SourcePos& sourcePos_);
    InitConditionNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifiers_, Node* declarator_, Node* initializer_, Node* attributes_);
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* DeclSpecifiers() const { return declSpecifiers.get(); }
    inline Node* Declarator() const { return declarator.get(); }
    inline Node* Initializer() const { return initializer.get(); }
    inline Node* Attributes() const { return attributes.get(); }
private:
    std::unique_ptr<Node> declSpecifiers;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> initializer;
    std::unique_ptr<Node> attributes;
};

class BoundStatementNode : public Node
{
public:
    BoundStatementNode(void* boundStatementNode_, const soul::ast::SourcePos& sourcePos_);
    inline void* GetBoundStatementNode() const { return boundStatementNode; }
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
private:
    void* boundStatementNode;
};

} // namespace otava::ast
