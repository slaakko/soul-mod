// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

export module otava.ast.statement;

import std;
import otava.ast.node;
import util.uuid;
import soul.ast.lexer.pos.pair;

export namespace otava::ast {

class LabeledStatementNode : public CompoundNode
{
public:
    LabeledStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    LabeledStatementNode(const soul::ast::SourcePos& sourcePos_, Node* label_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& colonPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Label() const noexcept { return label.get(); }
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& ColonPos() const noexcept { return colonPos; }
private:
    std::unique_ptr<Node> label;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos colonPos;
};

class CaseStatementNode : public CompoundNode
{
public:
    CaseStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    CaseStatementNode(const soul::ast::SourcePos& sourcePos_, Node* caseExpr_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& casePos_, 
        const soul::ast::SourcePos& colonPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* CaseExpression() const noexcept { return caseExpr.get(); }
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& CasePos() const noexcept { return casePos; }
    inline const soul::ast::SourcePos& ColonPos() const noexcept { return colonPos; }
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
    DefaultStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DefaultStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& defaultPos_, 
        const soul::ast::SourcePos& colonPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& DefaultPos() const noexcept { return defaultPos; }
    inline const soul::ast::SourcePos& ColonPos() const noexcept { return colonPos; }
private:
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos defaultPos;
    soul::ast::SourcePos colonPos;
};

class CompoundStatementNode : public SequenceNode
{
public:
    CompoundStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline void SetAttributes(Node* attributes_) noexcept { attributes.reset(attributes_); }
    void SetLexerPosPair(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair_) noexcept;
    inline const soul::ast::lexer::pos::pair::LexerPosPair& GetLexerPosPair() const noexcept { return lexerPosPair; }
    inline void SetLBracePos(const soul::ast::SourcePos& lbPos_) noexcept { lbPos = lbPos_; }
    inline void SetRBracePos(const soul::ast::SourcePos& rbPos_) noexcept { rbPos = rbPos_; }
    inline const soul::ast::SourcePos& LBracePos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracePos() const noexcept { return rbPos; }
    int Level() const noexcept;
    inline void* FunctionScope() const noexcept { return functionScope; }
    inline void SetFunctionScope(void* functionScope_) noexcept { functionScope = functionScope_; }
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos lbPos;
    soul::ast::SourcePos rbPos;
    soul::ast::lexer::pos::pair::LexerPosPair lexerPosPair;
    void* functionScope;
    int blockId;
};

class SequenceStatementNode : public CompoundNode
{
public:
    SequenceStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    SequenceStatementNode(const soul::ast::SourcePos& sourcePos_, Node* firstStmt_, Node* secondStmt_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* FirstStmt() const noexcept { return firstStmt.get(); }
    inline Node* SecondStmt() const noexcept { return secondStmt.get(); }
private:
    std::unique_ptr<Node> firstStmt;
    std::unique_ptr<Node> secondStmt;
};

class IfStatementNode : public CompoundNode
{
public:
    IfStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    IfStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, Node* thenStmt_, Node* elseStmt_, Node* attributes_,
        const soul::ast::SourcePos& ifPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_, const soul::ast::SourcePos& constExprPos_, 
        const soul::ast::SourcePos& elsePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Condition() const noexcept { return cond.get(); }
    inline Node* ThenStatement() const noexcept { return thenStmt.get(); }
    inline Node* ElseStatement() const noexcept { return elseStmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& IfPos() const noexcept { return ifPos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    inline const soul::ast::SourcePos& ConstExprSourcePos() const noexcept { return constExprPos; }
    inline const soul::ast::SourcePos& ElsePos() const noexcept { return elsePos; }
    inline bool IsConstExprIf() const noexcept { return constExprPos.IsValid(); }
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> thenStmt;
    std::unique_ptr<Node> elseStmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos ifPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
    soul::ast::SourcePos constExprPos;
    soul::ast::SourcePos elsePos;
    int blockId;
};

class SwitchStatementNode : public CompoundNode
{
public:
    SwitchStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    SwitchStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& switchPos_, 
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Condition() const noexcept { return cond.get(); }
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& SwitchPos() const noexcept { return switchPos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos switchPos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
    int blockId;
};

class WhileStatementNode : public CompoundNode
{
public:
    WhileStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    WhileStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& whilePos_,
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Condition() const noexcept { return cond.get(); }
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& WhilePos() const noexcept { return whilePos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
private:
    std::unique_ptr<Node> cond;
    std::unique_ptr<Node> stmt;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos whilePos;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
    int blockId;
};

class DoStatementNode : public CompoundNode
{
public:
    DoStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* expr_, Node* attributes_, Node* semicolon_,
        const soul::ast::SourcePos& doPos_, const soul::ast::SourcePos& whilePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Expression() const noexcept { return expr.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& DoPos() const noexcept { return doPos; }
    inline const soul::ast::SourcePos& WhilePos() const noexcept { return whilePos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
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
    RangeForStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    RangeForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* declaration_, Node* initializer_, Node* stmt_, Node* attributes_,
        const soul::ast::SourcePos& forPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_, const soul::ast::SourcePos& colonPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* InitStatement() const noexcept { return initStmt.get(); }
    inline Node* Declaration() const noexcept { return declaration.get(); }
    inline Node* Initializer() const noexcept { return initializer.get(); }
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& ForPos() const noexcept { return forPos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    inline const soul::ast::SourcePos& ColonPos() const noexcept { return colonPos; }
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
    void SetRangeForId(const util::uuid& rangeForId_) noexcept;
    inline const util::uuid& RangeForId() const noexcept { return rangeForId; }
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
    int blockId;
    util::uuid rangeForId;
};

class ForRangeDeclarationNode : public BinaryNode
{
public:
    ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* declarator_, Node* attributes_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const noexcept { return attributes.get(); }
private:
    std::unique_ptr<Node> attributes;
};

class StructuredBindingNode : public CompoundNode
{
public:
    StructuredBindingNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    StructuredBindingNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* refQualifier_, Node* identifiers_, Node* initializer_, 
        Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* DeclSpecifiers() const noexcept { return declSpecifiers.get(); }
    inline Node* RefQualifier() const noexcept { return refQualifier.get(); }
    inline Node* Identifiers() const noexcept { return identifiers.get(); }
    inline Node* Initializer() const noexcept { return initializer.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& LBracketPos() const noexcept { return lbPos; }
    inline const soul::ast::SourcePos& RBracketPos() const noexcept { return rbPos; }
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
    ForStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* loopExpr_, Node* stmt_, Node* attributes_,
        Node* semicolon_, const soul::ast::SourcePos& forPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* InitStatement() const noexcept { return initStmt.get(); }
    inline Node* Condition() const noexcept { return cond.get(); }
    inline Node* LoopExpr() const noexcept { return loopExpr.get(); }
    inline Node* Statement() const noexcept { return stmt.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& ForPos() const noexcept { return forPos; }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
    inline int BlockId() const noexcept { return blockId; }
    inline void SetBlockId(int blockId_) noexcept { blockId = blockId_; }
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
    int blockId;
};

class BreakStatementNode : public CompoundNode
{
public:
    BreakStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    BreakStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& breakPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& BreakPos() const noexcept { return breakPos; }
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos breakPos;
};

class ContinueStatementNode : public CompoundNode
{
public:
    ContinueStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ContinueStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& continuePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& ContinuePos() const noexcept { return continuePos; }
private:
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos continuePos;
};

class ReturnStatementNode : public CompoundNode
{
public:
    ReturnStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& returnPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ReturnValue() const noexcept { return returnValue.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& ReturnPos() const noexcept { return returnPos; }
private:
    std::unique_ptr<Node> returnValue;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos returnPos;
};

class CoReturnStatementNode : public CompoundNode
{
public:
    CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, 
        const soul::ast::SourcePos& coReturnPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* ReturnValue() const noexcept { return returnValue.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& CoReturnPos() const noexcept { return coReturnPos; }
private:
    std::unique_ptr<Node> returnValue;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos coReturnPos;
};

class GotoStatementNode : public CompoundNode
{
public:
    GotoStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    GotoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* target_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& gotoPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Target() const noexcept { return target.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semimcolon() const noexcept { return semicolon.get(); }
    inline const soul::ast::SourcePos& GotoPos() const noexcept { return gotoPos; }
private:
    std::unique_ptr<Node> target;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
    soul::ast::SourcePos gotoPos;
};

class TryStatementNode : public CompoundNode
{
public:
    TryStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    TryStatementNode(const soul::ast::SourcePos& sourcePos_, Node* tryBlock_, Node* handlers_, Node* attributes_, const soul::ast::SourcePos& tryPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TryBlock() const noexcept { return tryBlock.get(); }
    inline Node* Handlers() const noexcept { return handlers.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline const soul::ast::SourcePos& TryPos() const noexcept { return tryPos; }
private:
    std::unique_ptr<Node> tryBlock;
    std::unique_ptr<Node> handlers;
    std::unique_ptr<Node> attributes;
    soul::ast::SourcePos tryPos;
};

class HandlerSequenceNode : public SequenceNode
{
public:
    HandlerSequenceNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
};

class HandlerNode : public CompoundNode
{
public:
    HandlerNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    HandlerNode(const soul::ast::SourcePos& sourcePos_, Node* exception_, Node* catchBlock_, 
        const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Exception() const noexcept { return exception.get(); }
    inline Node* CatchBlock() const noexcept { return catchBlock.get(); }
    inline const soul::ast::SourcePos& LParenPos() const noexcept { return lpPos; }
    inline const soul::ast::SourcePos& RParenPos() const noexcept { return rpPos; }
private:
    std::unique_ptr<Node> exception;
    std::unique_ptr<Node> catchBlock;
    soul::ast::SourcePos lpPos;
    soul::ast::SourcePos rpPos;
};

class ExceptionDeclarationNode : public CompoundNode
{
public:
    ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_, Node* ellipsis_, Node* attributes_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* TypeSpecifiers() const noexcept { return typeSpecifiers.get(); }
    inline Node* Declarator() const noexcept { return declarator.get(); }
    inline Node* Ellipsis() const noexcept { return ellipsis.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
private:
    std::unique_ptr<Node> typeSpecifiers;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> ellipsis;
    std::unique_ptr<Node> attributes;
};

class ExpressionStatementNode : public CompoundNode
{
public:
    ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* attributes_, Node* semicolon_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Expression() const noexcept { return expr.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
    inline Node* Semicolon() const noexcept { return semicolon.get(); }
private:
    std::unique_ptr<Node> expr;
    std::unique_ptr<Node> attributes;
    std::unique_ptr<Node> semicolon;
};

class DeclarationStatementNode : public CompoundNode
{
public:
    DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_, Node* declaration_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* Declaration() const noexcept { return declaration.get(); }
private:
    std::unique_ptr<Node> declaration;
};

class InitConditionNode : public CompoundNode
{
public:
    InitConditionNode(const soul::ast::SourcePos& sourcePos_) noexcept;
    InitConditionNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifiers_, Node* declarator_, Node* initializer_, Node* attributes_) noexcept;
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
    void Write(Writer& writer) override;
    void Read(Reader& reader) override;
    inline Node* DeclSpecifiers() const noexcept { return declSpecifiers.get(); }
    inline Node* Declarator() const noexcept { return declarator.get(); }
    inline Node* Initializer() const noexcept { return initializer.get(); }
    inline Node* Attributes() const noexcept { return attributes.get(); }
private:
    std::unique_ptr<Node> declSpecifiers;
    std::unique_ptr<Node> declarator;
    std::unique_ptr<Node> initializer;
    std::unique_ptr<Node> attributes;
};

class BoundStatementNode : public Node
{
public:
    BoundStatementNode(void* boundStatementNode_, const soul::ast::SourcePos& sourcePos_) noexcept;
    inline void* GetBoundStatementNode() const noexcept { return boundStatementNode; }
    Node* Clone() const override;
    void Accept(Visitor& visitor) override;
private:
    void* boundStatementNode;
};

} // namespace otava::ast
