// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.statement;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

LabeledStatementNode::LabeledStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::labeledStatementNode, sourcePos_)
{
}

LabeledStatementNode::LabeledStatementNode(const soul::ast::SourcePos& sourcePos_, Node* label_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& colonPos_) :
    CompoundNode(NodeKind::labeledStatementNode, sourcePos_), label(label_), stmt(stmt_), attributes(attributes_), colonPos(colonPos_)
{
}

void LabeledStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void LabeledStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(label.get());
    writer.Write(stmt.get());
    writer.Write(attributes.get());
    writer.Write(colonPos);
}

void LabeledStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    label.reset(reader.ReadNode());
    stmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    colonPos = reader.ReadSourcePos();
}

CaseStatementNode::CaseStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::caseStatmentNode, sourcePos_)
{
}

CaseStatementNode::CaseStatementNode(const soul::ast::SourcePos& sourcePos_, Node* caseExpr_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& casePos_, const soul::ast::SourcePos& colonPos_) :
    CompoundNode(NodeKind::caseStatmentNode, sourcePos_), caseExpr(caseExpr_), stmt(stmt_), attributes(attributes_), casePos(casePos_), colonPos(colonPos_)
{
}

void CaseStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void CaseStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(caseExpr.get());
    writer.Write(stmt.get());
    writer.Write(attributes.get());
    writer.Write(casePos);
    writer.Write(colonPos);
}

void CaseStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    caseExpr.reset(reader.ReadNode());
    stmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    casePos = reader.ReadSourcePos();
    colonPos = reader.ReadSourcePos();
}

DefaultStatementNode::DefaultStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::defaultStatementNode, sourcePos_)
{
}

DefaultStatementNode::DefaultStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& defaultPos_, const soul::ast::SourcePos& colonPos_) :
    CompoundNode(NodeKind::defaultStatementNode, sourcePos_), stmt(stmt_), attributes(attributes_), defaultPos(defaultPos_), colonPos(colonPos_)
{
}

void DefaultStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DefaultStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(stmt.get());
    writer.Write(attributes.get());
    writer.Write(defaultPos);
    writer.Write(colonPos);
}

void DefaultStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    stmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    defaultPos = reader.ReadSourcePos();
    colonPos = reader.ReadSourcePos();
}

CompoundStatementNode::CompoundStatementNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::compoundStatementNode, sourcePos_)
{
}

int CompoundStatementNode::Level() const
{
    Node* parent = Parent();
    while (parent)
    {
        if (parent->Kind() == NodeKind::compoundStatementNode)
        {
            CompoundStatementNode* compoundStatement = static_cast<CompoundStatementNode*>(parent);
            return compoundStatement->Level() + 1;
        }
        parent = parent->Parent();
    }
    return 0;
}

void CompoundStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void CompoundStatementNode::Write(Writer& writer)
{
    SequenceNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void CompoundStatementNode::Read(Reader& reader)
{
    SequenceNode::Read(reader);
    attributes.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

void CompoundStatementNode::SetLexerPosPair(const soul::ast::lexer::pos::pair::LexerPosPair& lexerPosPair_)
{
    lexerPosPair = lexerPosPair_;
}

IfStatementNode::IfStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::ifStatementNode, sourcePos_)
{
}

IfStatementNode::IfStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* thenStmt_, Node* elseStmt_, Node* attributes_,
    const soul::ast::SourcePos& ifPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_, const soul::ast::SourcePos& constExprPos_, const soul::ast::SourcePos& elsePos_) :
    CompoundNode(NodeKind::ifStatementNode, sourcePos_), initStmt(initStmt_), cond(cond_), thenStmt(thenStmt_), elseStmt(elseStmt_), attributes(attributes_),
    ifPos(ifPos_), lpPos(lpPos_), rpPos(rpPos_), constExprPos(constExprPos_), elsePos(elsePos_)
{
}

void IfStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void IfStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(initStmt.get());
    writer.Write(cond.get());
    writer.Write(thenStmt.get());
    writer.Write(elseStmt.get());
    writer.Write(attributes.get());
    writer.Write(ifPos);
    writer.Write(lpPos);
    writer.Write(rpPos);
    writer.Write(constExprPos);
    writer.Write(elsePos);
}

void IfStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    initStmt.reset(reader.ReadNode());
    cond.reset(reader.ReadNode());
    thenStmt.reset(reader.ReadNode());
    elseStmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    ifPos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
    constExprPos = reader.ReadSourcePos();
    elsePos = reader.ReadSourcePos();
}

SwitchStatementNode::SwitchStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::switchStatemeNode, sourcePos_)
{
}

SwitchStatementNode::SwitchStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& switchPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::switchStatemeNode, sourcePos_), initStmt(initStmt_), cond(cond_), stmt(stmt_), attributes(attributes_), switchPos(switchPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void SwitchStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void SwitchStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(initStmt.get());
    writer.Write(cond.get());
    writer.Write(stmt.get());
    writer.Write(attributes.get());
    writer.Write(switchPos);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void SwitchStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    initStmt.reset(reader.ReadNode());
    cond.reset(reader.ReadNode());
    stmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    switchPos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

WhileStatementNode::WhileStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::whileStatementNode, sourcePos_)
{
}

WhileStatementNode::WhileStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& whilePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::whileStatementNode, sourcePos_), cond(cond_), stmt(stmt_), attributes(attributes_), whilePos(whilePos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void WhileStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void WhileStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(cond.get());
    writer.Write(stmt.get());
    writer.Write(attributes.get());
    writer.Write(whilePos);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void WhileStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    cond.reset(reader.ReadNode());
    stmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    whilePos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

DoStatementNode::DoStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::doStatementNode, sourcePos_)
{
}

DoStatementNode::DoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* expr_, Node* attributes_, Node* semicolon_,
    const soul::ast::SourcePos& doPos_, const soul::ast::SourcePos& whilePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::doStatementNode, sourcePos_), stmt(stmt_), expr(expr_), attributes(attributes_), semicolon(semicolon_), doPos(doPos_), whilePos(whilePos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void DoStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DoStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(stmt.get());
    writer.Write(expr.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(doPos);
    writer.Write(whilePos);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void DoStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    stmt.reset(reader.ReadNode());
    expr.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    doPos = reader.ReadSourcePos();
    whilePos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

RangeForStatementNode::RangeForStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::rangeForStatementNode, sourcePos_)
{
}

RangeForStatementNode::RangeForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* declaration_, Node* initializer_, Node* stmt_, Node* attributes_,
    const soul::ast::SourcePos& forPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_, const soul::ast::SourcePos& colonPos_) :
    CompoundNode(NodeKind::rangeForStatementNode, sourcePos_), initStmt(initStmt_), declaration(declaration_), initializer(initializer_), stmt(stmt_), attributes(attributes_),
    forPos(forPos_), lpPos(lpPos_), rpPos(rpPos_), colonPos(colonPos_)
{
}

void RangeForStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void RangeForStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(initStmt.get());
    writer.Write(declaration.get());
    writer.Write(initializer.get());
    writer.Write(stmt.get());
    writer.Write(attributes.get());
    writer.Write(forPos);
    writer.Write(lpPos);
    writer.Write(rpPos);
    writer.Write(colonPos);
}

void RangeForStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    initStmt.reset(reader.ReadNode());
    declaration.reset(reader.ReadNode());
    initializer.reset(reader.ReadNode());
    stmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    forPos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
    colonPos = reader.ReadSourcePos();
}

ForRangeDeclarationNode::ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::forRangeDeclarationNode, sourcePos_, nullptr, nullptr)
{
}

ForRangeDeclarationNode::ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* declarator_, Node* attributes_) :
    BinaryNode(NodeKind::forRangeDeclarationNode, sourcePos_, declSpecifierSeq_, declarator_), attributes(attributes_)
{
}

void ForRangeDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ForRangeDeclarationNode::Write(Writer& writer)
{
    BinaryNode::Write(writer);
    writer.Write(attributes.get());
}

void ForRangeDeclarationNode::Read(Reader& reader)
{
    BinaryNode::Read(reader);
    attributes.reset(reader.ReadNode());
}

StructuredBindingNode::StructuredBindingNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::structuredBindingNode, sourcePos_)
{
}

StructuredBindingNode::StructuredBindingNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* refQualifier_, Node* identifiers_, Node* initializer_, Node* attributes_, Node* semicolon_,
    const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::structuredBindingNode, sourcePos_), declSpecifiers(declSpecifierSeq_), refQualifier(refQualifier_), identifiers(identifiers_), initializer(initializer_),
    attributes(attributes_), semicolon(semicolon_), lbPos(lbPos_), rbPos(rbPos_)
{
}

void StructuredBindingNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void StructuredBindingNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declSpecifiers.get());
    writer.Write(refQualifier.get());
    writer.Write(identifiers.get());
    writer.Write(initializer.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void StructuredBindingNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declSpecifiers.reset(reader.ReadNode());
    refQualifier.reset(reader.ReadNode());
    identifiers.reset(reader.ReadNode());
    initializer.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

ForStatementNode::ForStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::forStatementNode, sourcePos_)
{
}

ForStatementNode::ForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* loopExpr_, Node* stmt_, Node* attributes_, Node* semicolon_,
    const soul::ast::SourcePos& forPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::forStatementNode, sourcePos_), initStmt(initStmt_), cond(cond_), loopExpr(loopExpr_), stmt(stmt_), attributes(attributes_), semicolon(semicolon_),
    forPos(forPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void ForStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ForStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(initStmt.get());
    writer.Write(cond.get());
    writer.Write(loopExpr.get());
    writer.Write(stmt.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(forPos);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ForStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    initStmt.reset(reader.ReadNode());
    cond.reset(reader.ReadNode());
    loopExpr.reset(reader.ReadNode());
    stmt.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    forPos = reader.ReadSourcePos();
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

BreakStatementNode::BreakStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::breakStatementNode, sourcePos_)
{
}

BreakStatementNode::BreakStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& breakPos_) :
    CompoundNode(NodeKind::breakStatementNode, sourcePos_), attributes(attributes_), semicolon(semicolon_), breakPos(breakPos_)
{
}

void BreakStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void BreakStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(breakPos);
}

void BreakStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    breakPos = reader.ReadSourcePos();
}

ContinueStatementNode::ContinueStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::continueStatementNode, sourcePos_)
{
}

ContinueStatementNode::ContinueStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& continuePos_) :
    CompoundNode(NodeKind::continueStatementNode, sourcePos_), attributes(attributes_), semicolon(semicolon_), continuePos(continuePos_)
{
}

void ContinueStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ContinueStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(continuePos);
}

void ContinueStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    continuePos = reader.ReadSourcePos();
}

ReturnStatementNode::ReturnStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::returnStatementNode, sourcePos_)
{
}

ReturnStatementNode::ReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& returnPos_) :
    CompoundNode(NodeKind::returnStatementNode, sourcePos_), returnValue(returnValue_), attributes(attributes_), semicolon(semicolon_), returnPos(returnPos_)
{
}

void ReturnStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ReturnStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(returnValue.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(returnPos);
}

void ReturnStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    returnValue.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    returnPos = reader.ReadSourcePos();
}

CoReturnStatementNode::CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::coReturnStatementNode, sourcePos_)
{
}

CoReturnStatementNode::CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& coReturnPos_) :
    CompoundNode(NodeKind::coReturnStatementNode, sourcePos_), returnValue(returnValue_), attributes(attributes_), semicolon(semicolon_), coReturnPos(coReturnPos_)
{
}

void CoReturnStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void CoReturnStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(returnValue.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(coReturnPos);
}

void CoReturnStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    returnValue.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    coReturnPos = reader.ReadSourcePos();
}

GotoStatementNode::GotoStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::gotoStatementNode, sourcePos_)
{
}

GotoStatementNode::GotoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* target_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& gotoPos_) :
    CompoundNode(NodeKind::gotoStatementNode, sourcePos_), target(target_), attributes(attributes_), semicolon(semicolon_), gotoPos(gotoPos_)
{
}

void GotoStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void GotoStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(target.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
    writer.Write(gotoPos);
}

void GotoStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    target.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
    gotoPos = reader.ReadSourcePos();
}

TryStatementNode::TryStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::tryStatementNode, sourcePos_)
{
}

TryStatementNode::TryStatementNode(const soul::ast::SourcePos& sourcePos_, Node* tryBlock_, Node* handlers_, Node* attributes_, const soul::ast::SourcePos& tryPos_) :
    CompoundNode(NodeKind::tryStatementNode, sourcePos_), tryBlock(tryBlock_), handlers(handlers_), attributes(attributes_), tryPos(tryPos_)
{
}

void TryStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void TryStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(tryBlock.get());
    writer.Write(handlers.get());
    writer.Write(attributes.get());
    writer.Write(tryPos);
}

void TryStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    tryBlock.reset(reader.ReadNode());
    handlers.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    tryPos = reader.ReadSourcePos();
}

HandlerSequenceNode::HandlerSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::handlerSequenceNode, sourcePos_)
{
}

void HandlerSequenceNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

HandlerNode::HandlerNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::handlerNode, sourcePos_)
{
}

HandlerNode::HandlerNode(const soul::ast::SourcePos& sourcePos_, Node* exception_, Node* catchBlock_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::handlerNode, sourcePos_), exception(exception_), catchBlock(catchBlock_), lpPos(lpPos_), rpPos(rpPos_)
{
}

void HandlerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void HandlerNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(exception.get());
    writer.Write(catchBlock.get());
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void HandlerNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    exception.reset(reader.ReadNode());
    catchBlock.reset(reader.ReadNode());
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

ExceptionDeclarationNode::ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::exceptionDeclarationNode, sourcePos_)
{
}

ExceptionDeclarationNode::ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_, Node* attributes_) :
    CompoundNode(NodeKind::exceptionDeclarationNode, sourcePos_), typeSpecifiers(typeSpecifiers_), declarator(declarator_), attributes(attributes_)
{
}

void ExceptionDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ExceptionDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeSpecifiers.get());
    writer.Write(declarator.get());
    writer.Write(attributes.get());
}

void ExceptionDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeSpecifiers.reset(reader.ReadNode());
    declarator.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

ExpressionStatementNode::ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::expressionStatementNode, sourcePos_)
{
}

ExpressionStatementNode::ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::expressionStatementNode, sourcePos_), expr(expr_), attributes(attributes_), semicolon(semicolon_)
{
}

void ExpressionStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ExpressionStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(expr.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

void ExpressionStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    expr.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

DeclarationStatementNode::DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::declarationStatementNode, sourcePos_)
{
}

DeclarationStatementNode::DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_, Node* declaration_) :
    CompoundNode(NodeKind::declarationStatementNode, sourcePos_), declaration(declaration_)
{
}

void DeclarationStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DeclarationStatementNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declaration.get());
}

void DeclarationStatementNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declaration.reset(reader.ReadNode());
}

InitConditionNode::InitConditionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::initConditionNode, sourcePos_)
{
}

InitConditionNode::InitConditionNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifiers_, Node* declarator_, Node* initializer_, Node* attributes_) :
    CompoundNode(NodeKind::initConditionNode, sourcePos_), declSpecifiers(declSpecifiers_), declarator(declarator_), initializer(initializer_), attributes(attributes_)
{
}

void InitConditionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void InitConditionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declSpecifiers.get());
    writer.Write(declarator.get());
    writer.Write(initializer.get());
    writer.Write(attributes.get());
}

void InitConditionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declSpecifiers.reset(reader.ReadNode());
    declarator.reset(reader.ReadNode());
    initializer.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
}

} // namespace soul::cpp20::ast
