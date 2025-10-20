// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.statement;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

LabeledStatementNode::LabeledStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::labeledStatementNode, sourcePos_)
{
}

LabeledStatementNode::LabeledStatementNode(const soul::ast::SourcePos& sourcePos_, Node* label_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& colonPos_) :
    CompoundNode(NodeKind::labeledStatementNode, sourcePos_), label(label_), stmt(stmt_), attributes(attributes_), colonPos(colonPos_)
{
}

std::expected<Node*, int> LabeledStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> l = label->Clone();
    if (!l) return l;
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    LabeledStatementNode* clone = new LabeledStatementNode(GetSourcePos(), *l, *s, clonedAttributes, colonPos);
    return std::expected<Node*, int>(clone);
}

void LabeledStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LabeledStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(label.get());
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(colonPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LabeledStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    label.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    colonPos = *posRv;
    return std::expected<bool, int>(true);
}

CaseStatementNode::CaseStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::caseStatmentNode, sourcePos_)
{
}

CaseStatementNode::CaseStatementNode(const soul::ast::SourcePos& sourcePos_, Node* caseExpr_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& casePos_,
    const soul::ast::SourcePos& colonPos_) :
    CompoundNode(NodeKind::caseStatmentNode, sourcePos_), caseExpr(caseExpr_), stmt(stmt_), attributes(attributes_), casePos(casePos_), colonPos(colonPos_)
{
}

std::expected<Node*, int> CaseStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> e = caseExpr->Clone();
    if (!e) return e;
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    CaseStatementNode* clone = new CaseStatementNode(GetSourcePos(), *e, *s, clonedAttributes, casePos, colonPos);
    return std::expected<Node*, int>(clone);
}

void CaseStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CaseStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(caseExpr.get());
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(casePos);
    if (!rv) return rv;
    rv = writer.Write(colonPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CaseStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    caseExpr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    casePos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    colonPos = *posRv;
    return std::expected<bool, int>(true);
}

DefaultStatementNode::DefaultStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::defaultStatementNode, sourcePos_)
{
}

DefaultStatementNode::DefaultStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& defaultPos_,
    const soul::ast::SourcePos& colonPos_) :
    CompoundNode(NodeKind::defaultStatementNode, sourcePos_), stmt(stmt_), attributes(attributes_), defaultPos(defaultPos_), colonPos(colonPos_)
{
}

std::expected<Node*, int> DefaultStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    DefaultStatementNode* clone = new DefaultStatementNode(GetSourcePos(), *s, clonedAttributes, defaultPos, colonPos);
    return std::expected<Node*, int>(clone);
}

void DefaultStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DefaultStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(defaultPos);
    if (!rv) return rv;
    rv = writer.Write(colonPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DefaultStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    defaultPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    colonPos = *posRv;
    return std::expected<bool, int>(true);
}

CompoundStatementNode::CompoundStatementNode(const soul::ast::SourcePos& sourcePos_) :
    SequenceNode(NodeKind::compoundStatementNode, sourcePos_), functionScope(nullptr)
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

std::expected<Node*, int> CompoundStatementNode::Clone() const
{
    CompoundStatementNode* clone = new CompoundStatementNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clone->SetAttributes(*a);
    }
    clone->SetLBracePos(lbPos);
    clone->SetRBracePos(rbPos);
    return std::expected<Node*, int>(clone);
}

void CompoundStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CompoundStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = SequenceNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CompoundStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = SequenceNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> IfStatementNode::Clone() const
{
    Node* clonedInitStmt = nullptr;
    if (initStmt)
    {
        std::expected<Node*, int> i = initStmt->Clone();
        if (!i) return i;
        clonedInitStmt = *i;
    }
    Node* clonedElseStmt = nullptr;
    if (elseStmt)
    {
        std::expected<Node*, int> e = elseStmt->Clone();
        if (!e) return e;
        clonedElseStmt = *e;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> c = cond->Clone();
    if (!c) return c;
    std::expected<Node*, int> t = thenStmt->Clone();
    if (!t) return t;
    IfStatementNode* clone = new IfStatementNode(GetSourcePos(), clonedInitStmt, *c, *t, clonedElseStmt, clonedAttributes,
        ifPos, lpPos, rpPos, constExprPos, elsePos);
    return std::expected<Node*, int>(clone);
}

void IfStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> IfStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(initStmt.get());
    if (!rv) return rv;
    rv = writer.Write(cond.get());
    if (!rv) return rv;
    rv = writer.Write(thenStmt.get());
    if (!rv) return rv;
    rv = writer.Write(elseStmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(ifPos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    rv = writer.Write(constExprPos);
    if (!rv) return rv;
    rv = writer.Write(elsePos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> IfStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initStmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    cond.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    thenStmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    elseStmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    ifPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    constExprPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    elsePos = *posRv;
    return std::expected<bool, int>(true);
}

SwitchStatementNode::SwitchStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::switchStatemeNode, sourcePos_)
{
}

SwitchStatementNode::SwitchStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& switchPos_,
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::switchStatemeNode, sourcePos_), initStmt(initStmt_), cond(cond_), stmt(stmt_), attributes(attributes_), switchPos(switchPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> SwitchStatementNode::Clone() const
{
    Node* clonedInitStmt = nullptr;
    if (initStmt)
    {
        std::expected<Node*, int> i = initStmt->Clone();
        if (!i) return i;
        clonedInitStmt = *i;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> c = cond->Clone();
    if (!c) return c;
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    SwitchStatementNode* clone = new SwitchStatementNode(GetSourcePos(), clonedInitStmt, *c, *s, clonedAttributes, switchPos, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void SwitchStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SwitchStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(initStmt.get());
    if (!rv) return rv;
    rv = writer.Write(cond.get());
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(switchPos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SwitchStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initStmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    cond.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    switchPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

WhileStatementNode::WhileStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::whileStatementNode, sourcePos_)
{
}

WhileStatementNode::WhileStatementNode(const soul::ast::SourcePos& sourcePos_, Node* cond_, Node* stmt_, Node* attributes_, const soul::ast::SourcePos& whilePos_,
    const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::whileStatementNode, sourcePos_), cond(cond_), stmt(stmt_), attributes(attributes_), whilePos(whilePos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> WhileStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> c = cond->Clone();
    if (!c) return c;
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    WhileStatementNode* clone = new WhileStatementNode(GetSourcePos(), *c, *s, clonedAttributes, whilePos, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void WhileStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> WhileStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(cond.get());
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(whilePos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> WhileStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    cond.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    whilePos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

DoStatementNode::DoStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::doStatementNode, sourcePos_)
{
}

DoStatementNode::DoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* stmt_, Node* expr_, Node* attributes_, Node* semicolon_,
    const soul::ast::SourcePos& doPos_, const soul::ast::SourcePos& whilePos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::doStatementNode, sourcePos_), stmt(stmt_), expr(expr_), attributes(attributes_), semicolon(semicolon_), doPos(doPos_), whilePos(whilePos_),
    lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> DoStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = attributes->Clone();
    }
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    std::expected<Node*, int> e = expr->Clone();
    if (!e) return e;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    DoStatementNode* clone = new DoStatementNode(GetSourcePos(), *s, *e, clonedAttributes, *sc, doPos, whilePos, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void DoStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DoStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(expr.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(doPos);
    if (!rv) return rv;
    rv = writer.Write(whilePos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DoStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    expr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    doPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    whilePos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
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

std::expected<Node*, int> RangeForStatementNode::Clone() const
{
    Node* clonedInitStmt = nullptr;
    if (initStmt)
    {
        std::expected<Node*, int> i = initStmt->Clone();
        if (!i) return i;
        clonedInitStmt = *i;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> d = declaration->Clone();
    if (!d) return d;
    std::expected<Node*, int> i = initializer->Clone();
    if (!i) return i;
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    RangeForStatementNode* clone = new RangeForStatementNode(GetSourcePos(), clonedInitStmt, *d, *i, *s, clonedAttributes, forPos, lpPos, rpPos, colonPos);
    return std::expected<Node*, int>(clone);
}

void RangeForStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> RangeForStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(initStmt.get());
    if (!rv) return rv;
    rv = writer.Write(declaration.get());
    if (!rv) return rv;
    rv = writer.Write(initializer.get());
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(forPos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    rv = writer.Write(colonPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> RangeForStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initStmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declaration.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initializer.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    forPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    colonPos = *posRv;
    return std::expected<bool, int>(true);
}

ForRangeDeclarationNode::ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::forRangeDeclarationNode, sourcePos_, nullptr, nullptr)
{
}

ForRangeDeclarationNode::ForRangeDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* declarator_, Node* attributes_) :
    BinaryNode(NodeKind::forRangeDeclarationNode, sourcePos_, declSpecifierSeq_, declarator_), attributes(attributes_)
{
}

std::expected<Node*, int> ForRangeDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> l = Left()->Clone();
    if (!l) return l;
    std::expected<Node*, int> r = Right->Clone();
    if (!r) return r;
    ForRangeDeclarationNode* clone = new ForRangeDeclarationNode(GetSourcePos(), *l, *r, clonedAttributes);
    return std::expected<Node*, int>(clone);
}

void ForRangeDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ForRangeDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = BinaryNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ForRangeDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = BinaryNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

StructuredBindingNode::StructuredBindingNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::structuredBindingNode, sourcePos_)
{
}

StructuredBindingNode::StructuredBindingNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifierSeq_, Node* refQualifier_, Node* identifiers_, Node* initializer_,
    Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::structuredBindingNode, sourcePos_), declSpecifiers(declSpecifierSeq_), refQualifier(refQualifier_), identifiers(identifiers_), initializer(initializer_),
    attributes(attributes_), semicolon(semicolon_), lbPos(lbPos_), rbPos(rbPos_)
{
}

std::expected<Node*, int> StructuredBindingNode::Clone() const
{
    Node* clonedRefQualifier = nullptr;
    if (refQualifier)
    {
        std::expected<Node*, int> r = refQualifier->Clone();
        if (!r) return r;
        clonedRefQualifier = *r;
    }
    Node* clonedInitializer = nullptr;
    if (initializer)
    {
        std::expected<Node*, int> i = initializer->Clone();
        if (!i) return i;
        clonedInitializer = *i;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    Node* clonedSemicolon = nullptr;
    if (semicolon)
    {
        std::expected<Node*, int> s = semicolon->Clone();
        if (!s) return s;
        clonedSemicolon = *s;
    }
    std::expected<Node*, int> d = declSpecifiers->Clone();
    if (!d) return d;
    std::expected<Node*, int> i = identifiers->Clone();
    if (!i) return i;
    StructuredBindingNode* clone = new StructuredBindingNode(GetSourcePos(), *d, clonedRefQualifier, *i, clonedInitializer, clonedAttributes, clonedSemicolon, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void StructuredBindingNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> StructuredBindingNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(refQualifier.get());
    if (!rv) return rv;
    rv = writer.Write(identifiers.get());
    if (!rv) return rv;
    rv = writer.Write(initializer.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> StructuredBindingNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    refQualifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    identifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initializer.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
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

ForStatementNode::ForStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::forStatementNode, sourcePos_)
{
}

ForStatementNode::ForStatementNode(const soul::ast::SourcePos& sourcePos_, Node* initStmt_, Node* cond_, Node* loopExpr_, Node* stmt_, Node* attributes_, Node* semicolon_,
    const soul::ast::SourcePos& forPos_, const soul::ast::SourcePos& lpPos_, const soul::ast::SourcePos& rpPos_) :
    CompoundNode(NodeKind::forStatementNode, sourcePos_), initStmt(initStmt_), cond(cond_), loopExpr(loopExpr_), stmt(stmt_), attributes(attributes_), semicolon(semicolon_),
    forPos(forPos_), lpPos(lpPos_), rpPos(rpPos_)
{
}

std::expected<Node*, int> ForStatementNode::Clone() const
{
    Node* clonedCond = nullptr;
    if (cond)
    {
        std::expected<Node*, int> c = cond->Clone();
        if (!c) return c;
        clonedCond = *c;
    }
    Node* clonedLoopExpr = nullptr;
    if (loopExpr)
    {
        std::expected<Node*, int> e = loopExpr->Clone();
        if (!e) return e;
        clonedLoopExpr = *e;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> i = initStmt->Clone();
    if (!i) return i;
    std::expected<Node*, int> s = stmt->Clone();
    if (!s) return s;
    std::expected<Node*, int> sc = semicolon->Clone();
    if (!sc) return sc;
    ForStatementNode* clone = new ForStatementNode(GetSourcePos(), *i, clonedCond, clonedLoopExpr, *s, clonedAttributes, *sc, forPos, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void ForStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ForStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(initStmt.get());
    if (!rv) return rv;
    rv = writer.Write(cond.get());
    if (!rv) return rv;
    rv = writer.Write(loopExpr.get());
    if (!rv) return rv;
    rv = writer.Write(stmt.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(forPos);
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ForStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initStmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    cond.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    loopExpr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    stmt.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    forPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

BreakStatementNode::BreakStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::breakStatementNode, sourcePos_)
{
}

BreakStatementNode::BreakStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& breakPos_) :
    CompoundNode(NodeKind::breakStatementNode, sourcePos_), attributes(attributes_), semicolon(semicolon_), breakPos(breakPos_)
{
}

std::expected<Node*, int> BreakStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    BreakStatementNode* clone = new BreakStatementNode(GetSourcePos(), clonedAttributes, *s, breakPos);
    return std::expected<Node*, int>(clone);
}

void BreakStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> BreakStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(breakPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> BreakStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    breakPos = *posRv;
    return std::expected<bool, int>(true);
}

ContinueStatementNode::ContinueStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::continueStatementNode, sourcePos_)
{
}

ContinueStatementNode::ContinueStatementNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& continuePos_) :
    CompoundNode(NodeKind::continueStatementNode, sourcePos_), attributes(attributes_), semicolon(semicolon_), continuePos(continuePos_)
{
}

std::expected<Node*, int> ContinueStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    ContinueStatementNode* clone = new ContinueStatementNode(GetSourcePos(), clonedAttributes, *s, continuePos);
    return std::expected<Node*, int>(clone);
}

void ContinueStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ContinueStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(continuePos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ContinueStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    continuePos = *posRv;
    return std::expected<bool, int>(true);
}

ReturnStatementNode::ReturnStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::returnStatementNode, sourcePos_)
{
}

ReturnStatementNode::ReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& returnPos_) :
    CompoundNode(NodeKind::returnStatementNode, sourcePos_), returnValue(returnValue_), attributes(attributes_), semicolon(semicolon_), returnPos(returnPos_)
{
}

std::expected<Node*, int> ReturnStatementNode::Clone() const
{
    Node* clonedReturnValue = nullptr;
    if (returnValue)
    {
        std::expected<Node*, int> r = returnValue->Clone();
        if (!r) return r;
        clonedReturnValue = *r;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    ReturnStatementNode* clone = new ReturnStatementNode(GetSourcePos(), clonedReturnValue, clonedAttributes, *s, returnPos);
    return std::expected<Node*, int>(clone);
}

void ReturnStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ReturnStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(returnValue.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(returnPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ReturnStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    returnValue.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    returnPos = *posRv;
    return std::expected<bool, int>(true);
}

CoReturnStatementNode::CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::coReturnStatementNode, sourcePos_)
{
}

CoReturnStatementNode::CoReturnStatementNode(const soul::ast::SourcePos& sourcePos_, Node* returnValue_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& coReturnPos_) :
    CompoundNode(NodeKind::coReturnStatementNode, sourcePos_), returnValue(returnValue_), attributes(attributes_), semicolon(semicolon_), coReturnPos(coReturnPos_)
{
}

std::expected<Node*, int> CoReturnStatementNode::Clone() const
{
    Node* clonedReturnValue = nullptr;
    if (returnValue)
    {
        std::expected<Node*, int> r = returnValue->Clone();
        if (!r) return r;
        clonedReturnValue = *r;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    CoReturnStatementNode* clone = new CoReturnStatementNode(GetSourcePos(), clonedReturnValue, clonedAttributes, *s, coReturnPos);
    return std::expected<Node*, int>(clone);
}

void CoReturnStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CoReturnStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(returnValue.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(coReturnPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CoReturnStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    returnValue.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    coReturnPos = *posRv;
    return std::expected<bool, int>(true);
}

GotoStatementNode::GotoStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::gotoStatementNode, sourcePos_)
{
}

GotoStatementNode::GotoStatementNode(const soul::ast::SourcePos& sourcePos_, Node* target_, Node* attributes_, Node* semicolon_, const soul::ast::SourcePos& gotoPos_) :
    CompoundNode(NodeKind::gotoStatementNode, sourcePos_), target(target_), attributes(attributes_), semicolon(semicolon_), gotoPos(gotoPos_)
{
}

std::expected<Node*, int> GotoStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        clonedAttributes = *a;
    }
    std::expected<Node*, int> t = target->Clone();
    if (!t) return t;
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    GotoStatementNode* clone = new GotoStatementNode(GetSourcePos(), *t, clonedAttributes, *s, gotoPos);
    return std::expected<Node*, int>(clone);
}

void GotoStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> GotoStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(target.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    rv = writer.Write(gotoPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> GotoStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    target.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    gotoPos = *posRv;
    return std::expected<bool, int>(true);
}

TryStatementNode::TryStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::tryStatementNode, sourcePos_)
{
}

TryStatementNode::TryStatementNode(const soul::ast::SourcePos& sourcePos_, Node* tryBlock_, Node* handlers_, Node* attributes_, const soul::ast::SourcePos& tryPos_) :
    CompoundNode(NodeKind::tryStatementNode, sourcePos_), tryBlock(tryBlock_), handlers(handlers_), attributes(attributes_), tryPos(tryPos_)
{
}

std::expected<Node*, int> TryStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> t = tryBlock->Clone();
    if (!t) return t;
    std::expected<Node*, int> h = handlers->Clone();
    if (!h) return h;
    TryStatementNode* clone = new TryStatementNode(GetSourcePos(), *t, *h, clonedAttributes, tryPos);
    return std::expected<Node*, int>(clone);
}

void TryStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> TryStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(tryBlock.get());
    if (!rv) return rv;
    rv = writer.Write(handlers.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(tryPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> TryStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    tryBlock.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    handlers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    tryPos = *posRv;
    return std::expected<bool, int>(true);
}

HandlerSequenceNode::HandlerSequenceNode(const soul::ast::SourcePos& sourcePos_) : SequenceNode(NodeKind::handlerSequenceNode, sourcePos_)
{
}

std::expected<Node*, int> HandlerSequenceNode::Clone() const
{
    HandlerSequenceNode* clone = new HandlerSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
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

std::expected<Node*, int> HandlerNode::Clone() const
{
    std::expected<Node*, int> e = exception->Clone();
    if (!e) return e;
    std::expected<Node*, int> c = catchBlock->Clone();
    if (!c) return c;
    HandlerNode* clone = new HandlerNode(GetSourcePos(), *e, *c, lpPos, rpPos);
    return std::expected<Node*, int>(clone);
}

void HandlerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> HandlerNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(exception.get());
    if (!rv) return rv;
    rv = writer.Write(catchBlock.get());
    if (!rv) return rv;
    rv = writer.Write(lpPos);
    if (!rv) return rv;
    rv = writer.Write(rpPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> HandlerNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    exception.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    catchBlock.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lpPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rpPos = *posRv;
    return std::expected<bool, int>(true);
}

ExceptionDeclarationNode::ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::exceptionDeclarationNode, sourcePos_)
{
}

ExceptionDeclarationNode::ExceptionDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifiers_, Node* declarator_, Node* ellipsis_, Node* attributes_) :
    CompoundNode(NodeKind::exceptionDeclarationNode, sourcePos_), typeSpecifiers(typeSpecifiers_), declarator(declarator_), ellipsis(ellipsis_), attributes(attributes_)
{
}

std::expected<Node*, int> ExceptionDeclarationNode::Clone() const
{
    Node* clonedTypeSpecifiers = nullptr;
    if (typeSpecifiers)
    {
        std::expected<Node*, int> t = typeSpecifiers->Clone();
        if (!t) return t;
        clonedTypeSpecifiers = *t;
    }
    Node* clonedDeclarator = nullptr;
    if (declarator)
    {
        std::expected<Node*, int> d = declarator->Clone();
        if (!d) return d;
        clonedDeclarator = *d;
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        std::expected<Node*, int> e = ellipsis->Clone();
        if (!e) return e;
        clonedEllipsis = *e;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    ExceptionDeclarationNode* clone = new ExceptionDeclarationNode(GetSourcePos(), clonedTypeSpecifiers, clonedDeclarator, clonedEllipsis, clonedAttributes);
    return std::expected<Node*, int>(clone);
}

void ExceptionDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExceptionDeclarationNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(typeSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(ellipsis.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExceptionDeclarationNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    typeSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ellipsis.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

ExpressionStatementNode::ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::expressionStatementNode, sourcePos_)
{
}

ExpressionStatementNode::ExpressionStatementNode(const soul::ast::SourcePos& sourcePos_, Node* expr_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::expressionStatementNode, sourcePos_), expr(expr_), attributes(attributes_), semicolon(semicolon_)
{
}

std::expected<Node*, int> ExpressionStatementNode::Clone() const
{
    Node* clonedExpr = nullptr;
    if (expr)
    {
        std::expected<Node*, int> e = expr->Clone();
        if (!e) return e;
        clonedExpr = *e;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> s = semicolon->Clone();
    if (!s) return s;
    ExpressionStatementNode* clone = new ExpressionStatementNode(GetSourcePos(), clonedExpr, clonedAttributes, *s);
    return std::expected<Node*, int>(clone);
}

void ExpressionStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> ExpressionStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(expr.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(semicolon.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> ExpressionStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    expr.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    semicolon.reset(*nrv);
    return std::expected<bool, int>(true);
}

DeclarationStatementNode::DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::declarationStatementNode, sourcePos_)
{
}

DeclarationStatementNode::DeclarationStatementNode(const soul::ast::SourcePos& sourcePos_, Node* declaration_) :
    CompoundNode(NodeKind::declarationStatementNode, sourcePos_), declaration(declaration_)
{
}

std::expected<Node*, int> DeclarationStatementNode::Clone() const
{
    std::expected<Node*, int> d = declaration->Clone();
    if (!d) return d;
    DeclarationStatementNode* clone = new DeclarationStatementNode(GetSourcePos(), *d);
    return std::expected<Node*, int>(clone);
}

void DeclarationStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> DeclarationStatementNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declaration.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> DeclarationStatementNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declaration.reset(*nrv);
    return std::expected<bool, int>(true);
}

InitConditionNode::InitConditionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::initConditionNode, sourcePos_)
{
}

InitConditionNode::InitConditionNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifiers_, Node* declarator_, Node* initializer_, Node* attributes_) :
    CompoundNode(NodeKind::initConditionNode, sourcePos_), declSpecifiers(declSpecifiers_), declarator(declarator_), initializer(initializer_), attributes(attributes_)
{
}

std::expected<Node*, int> InitConditionNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    std::expected<Node*, int> d = declSpecifiers->Clone();
    if (!d) return d;
    std::expected<Node*, int> e = declarator->Clone();
    if (!e) return e;
    std::expected<Node*, int> i = initializer->Clone();
    if (!i) return i;
    InitConditionNode* clone = new InitConditionNode(GetSourcePos(), *d, *e, *i, clonedAttributes);
    return std::expected<Node*, int>(clone);
}

void InitConditionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> InitConditionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(initializer.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> InitConditionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initializer.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    return std::expected<bool, int>(true);
}

BoundStatementNode::BoundStatementNode(void* boundStatementNode_, const soul::ast::SourcePos& sourcePos_) :
    Node(NodeKind::boundStatementNode, sourcePos_), boundStatementNode(boundStatementNode_)
{
}

std::expected<Node*, int> BoundStatementNode::Clone() const
{
    return std::expected<Node*, int>(new BoundStatementNode(boundStatementNode, GetSourcePos()));
}

void BoundStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
