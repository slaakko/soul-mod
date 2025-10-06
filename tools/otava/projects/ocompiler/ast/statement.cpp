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

Node* LabeledStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    LabeledStatementNode* clone = new LabeledStatementNode(GetSourcePos(), label->Clone(), stmt->Clone(), clonedAttributes, colonPos);
    return clone;
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

Node* CaseStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    CaseStatementNode* clone = new CaseStatementNode(GetSourcePos(), caseExpr->Clone(), stmt->Clone(), clonedAttributes, casePos, colonPos);
    return clone;
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

Node* DefaultStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    DefaultStatementNode* clone = new DefaultStatementNode(GetSourcePos(), stmt->Clone(), clonedAttributes, defaultPos, colonPos);
    return clone;
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

Node* CompoundStatementNode::Clone() const
{
    CompoundStatementNode* clone = new CompoundStatementNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    if (attributes)
    {
        clone->SetAttributes(attributes->Clone());
    }
    clone->SetLBracePos(lbPos);
    clone->SetRBracePos(rbPos);
    return clone;
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

Node* IfStatementNode::Clone() const
{
    Node* clonedInitStmt = nullptr;
    if (initStmt)
    {
        clonedInitStmt = initStmt->Clone();
    }
    Node* clonedElseStmt = nullptr;
    if (elseStmt)
    {
        clonedElseStmt = elseStmt->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    IfStatementNode* clone = new IfStatementNode(GetSourcePos(), clonedInitStmt, cond->Clone(), thenStmt->Clone(), clonedElseStmt, clonedAttributes,
        ifPos, lpPos, rpPos, constExprPos, elsePos);
    return clone;
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

Node* SwitchStatementNode::Clone() const
{
    Node* clonedInitStmt = nullptr;
    if (initStmt)
    {
        clonedInitStmt = initStmt->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    SwitchStatementNode* clone = new SwitchStatementNode(GetSourcePos(), clonedInitStmt, cond->Clone(), stmt->Clone(), clonedAttributes, switchPos, lpPos, rpPos);
    return clone;
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

Node* WhileStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    WhileStatementNode* clone = new WhileStatementNode(GetSourcePos(), cond->Clone(), stmt->Clone(), clonedAttributes, whilePos, lpPos, rpPos);
    return clone;
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

Node* DoStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    DoStatementNode* clone = new DoStatementNode(GetSourcePos(), stmt->Clone(), expr->Clone(), clonedAttributes, semicolon->Clone(), doPos, whilePos, lpPos, rpPos);
    return clone;
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

Node* RangeForStatementNode::Clone() const
{
    Node* clonedInitStmt = nullptr;
    if (initStmt)
    {
        clonedInitStmt = initStmt->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    RangeForStatementNode* clone = new RangeForStatementNode(GetSourcePos(), clonedInitStmt, declaration->Clone(), initializer->Clone(), stmt->Clone(), clonedAttributes,
        forPos, lpPos, rpPos, colonPos);
    return clone;
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

Node* ForRangeDeclarationNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ForRangeDeclarationNode* clone = new ForRangeDeclarationNode(GetSourcePos(), Left()->Clone(), Right()->Clone(), clonedAttributes);
    return clone;
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

Node* StructuredBindingNode::Clone() const
{
    Node* clonedRefQualifier = nullptr;
    if (refQualifier)
    {
        clonedRefQualifier = refQualifier->Clone();
    }
    Node* clonedInitializer = nullptr;
    if (initializer)
    {
        clonedInitializer = initializer->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    Node* clonedSemicolon = nullptr;
    if (semicolon)
    {
        clonedSemicolon = semicolon->Clone();
    }
    StructuredBindingNode* clone = new StructuredBindingNode(GetSourcePos(), declSpecifiers->Clone(), clonedRefQualifier, identifiers->Clone(), clonedInitializer,
        clonedAttributes, clonedSemicolon, lbPos, rbPos);
    return clone;
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

Node* ForStatementNode::Clone() const
{
    Node* clonedCond = nullptr;
    if (cond)
    {
        clonedCond = cond->Clone();
    }
    Node* clonedLoopExpr = nullptr;
    if (loopExpr)
    {
        clonedLoopExpr = loopExpr->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ForStatementNode* clone = new ForStatementNode(GetSourcePos(), initStmt->Clone(), clonedCond, clonedLoopExpr, stmt->Clone(), clonedAttributes, semicolon->Clone(),
        forPos, lpPos, rpPos);
    return clone;
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

Node* BreakStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    BreakStatementNode* clone = new BreakStatementNode(GetSourcePos(), clonedAttributes, semicolon->Clone(), breakPos);
    return clone;
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

Node* ContinueStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ContinueStatementNode* clone = new ContinueStatementNode(GetSourcePos(), clonedAttributes, semicolon->Clone(), continuePos);
    return clone;
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

Node* ReturnStatementNode::Clone() const
{
    Node* clonedReturnValue = nullptr;
    if (returnValue)
    {
        clonedReturnValue = returnValue->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ReturnStatementNode* clone = new ReturnStatementNode(GetSourcePos(), clonedReturnValue, clonedAttributes, semicolon->Clone(), returnPos);
    return clone;
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

Node* CoReturnStatementNode::Clone() const
{
    Node* clonedReturnValue = nullptr;
    if (returnValue)
    {
        clonedReturnValue = returnValue->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    CoReturnStatementNode* clone = new CoReturnStatementNode(GetSourcePos(), clonedReturnValue, clonedAttributes, semicolon->Clone(), coReturnPos);
    return clone;
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

Node* GotoStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    GotoStatementNode* clone = new GotoStatementNode(GetSourcePos(), target->Clone(), clonedAttributes, semicolon->Clone(), gotoPos);
    return clone;
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

Node* TryStatementNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    TryStatementNode* clone = new TryStatementNode(GetSourcePos(), tryBlock->Clone(), handlers->Clone(), clonedAttributes, tryPos);
    return clone;
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

Node* HandlerSequenceNode::Clone() const
{
    HandlerSequenceNode* clone = new HandlerSequenceNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
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

Node* HandlerNode::Clone() const
{
    HandlerNode* clone = new HandlerNode(GetSourcePos(), exception->Clone(), catchBlock->Clone(), lpPos, rpPos);
    return clone;
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

Node* ExceptionDeclarationNode::Clone() const
{
    Node* clonedTypeSpecifiers = nullptr;
    if (typeSpecifiers)
    {
        clonedTypeSpecifiers = typeSpecifiers->Clone();
    }
    Node* clonedDeclarator = nullptr;
    if (declarator)
    {
        clonedDeclarator = declarator->Clone();
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        clonedEllipsis = ellipsis->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ExceptionDeclarationNode* clone = new ExceptionDeclarationNode(GetSourcePos(), clonedTypeSpecifiers, clonedDeclarator, clonedEllipsis, clonedAttributes);
    return clone;
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
    writer.Write(ellipsis.get());
    writer.Write(attributes.get());
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

Node* ExpressionStatementNode::Clone() const
{
    Node* clonedExpr = nullptr;
    if (expr)
    {
        clonedExpr = expr->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    ExpressionStatementNode* clone = new ExpressionStatementNode(GetSourcePos(), clonedExpr, clonedAttributes, semicolon->Clone());
    return clone;
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

Node* DeclarationStatementNode::Clone() const
{
    DeclarationStatementNode* clone = new DeclarationStatementNode(GetSourcePos(), declaration->Clone());
    return clone;
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

Node* InitConditionNode::Clone() const
{
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    InitConditionNode* clone = new InitConditionNode(GetSourcePos(), declSpecifiers->Clone(), declarator->Clone(), initializer->Clone(), clonedAttributes);
    return clone;
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

Node* BoundStatementNode::Clone() const
{
    return new BoundStatementNode(boundStatementNode, GetSourcePos());
}

void BoundStatementNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

} // namespace otava::ast
