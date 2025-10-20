// =================================
// Copyright (c) 2025 Seppo Laakko
// Distributed under the MIT license
// =================================

module otava.ast.lambda;

import otava.ast.visitor;
import otava.ast.reader;
import otava.ast.writer;

namespace otava::ast {

LambdaExpressionNode::LambdaExpressionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::lambdaExpressionNode, sourcePos_)
{
}

LambdaExpressionNode::LambdaExpressionNode(const soul::ast::SourcePos& sourcePos_, Node* introducer_, Node* templateParams_, Node* declarator_, Node* body_) :
    CompoundNode(NodeKind::lambdaExpressionNode, sourcePos_), introducer(introducer_), templateParams(templateParams_), declarator(declarator_), body(body_)
{
}

std::expected<Node*, int> LambdaExpressionNode::Clone() const
{
    Node* clonedTemplateParams = nullptr;
    if (templateParams)
    {
        std::expected<Node*, int> t = templateParams->Clone();
        if (!t) return t;
        clonedTemplateParams = *t;
    }
    std::expected<Node*, int> i = introducer->Clone();
    if (!i) return i;
    std::expected<Node*, int> d = declarator->Clone();
    if (!d) return d;
    std::expected<Node*, int> b = body->Clone();
    if (!b) return b;
    LambdaExpressionNode* clone = new LambdaExpressionNode(GetSourcePos(), *i, clonedTemplateParams, *d, *b);
    return std::expected<Node*, int>(clone);
}

void LambdaExpressionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LambdaExpressionNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(introducer.get());
    if (!rv) return rv;
    rv = writer.Write(templateParams.get());
    if (!rv) return rv;
    rv = writer.Write(declarator.get());
    if (!rv) return rv;
    rv = writer.Write(body.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LambdaExpressionNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    introducer.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateParams.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declarator.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    body.reset(*nrv);
    return std::expected<bool, int>(true);
}

LambdaIntroducerNode::LambdaIntroducerNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::lambdaIntroducerNode, sourcePos_)
{
}

LambdaIntroducerNode::LambdaIntroducerNode(const soul::ast::SourcePos& sourcePos_, Node* capture_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::lambdaIntroducerNode, sourcePos_), capture(capture_), lbPos(lbPos_), rbPos(rbPos_)
{
}

std::expected<Node*, int> LambdaIntroducerNode::Clone() const
{
    Node* clonedCapture = nullptr;
    if (capture)
    {
        std::expected<Node*, int> c = capture->Clone();
        if (!c) return c;
        clonedCapture = *c;
    }
    LambdaIntroducerNode* clone = new LambdaIntroducerNode(GetSourcePos(), clonedCapture, lbPos, rbPos);
    return std::expected<Node*, int>(clone);
}

void LambdaIntroducerNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LambdaIntroducerNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(capture.get());
    if (!rv) return rv;
    rv = writer.Write(lbPos);
    if (!rv) return rv;
    rv = writer.Write(rbPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LambdaIntroducerNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    capture.reset(*nrv);
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    lbPos = *posRv;
    posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    rbPos = *posRv;
    return std::expected<bool, int>(true);
}

LambdaCaptureNode::LambdaCaptureNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::lambdaCaptureNode, sourcePos_)
{
}

std::expected<Node*, int> LambdaCaptureNode::Clone() const
{
    LambdaCaptureNode* clone = new LambdaCaptureNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        std::expected<Node*, int> n = node->Clone();
        if (!n) return n;
        std::expected<bool, int> rv = clone->AddNode(*n);
        if (!rv) return std::unexpected<int>(rv.error());
    }
    return std::expected<Node*, int>(clone);
}

void LambdaCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultRefCaptureNode::DefaultRefCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultRefCaptureNode, sourcePos_)
{
}

std::expected<Node*, int> DefaultRefCaptureNode::Clone() const
{
    DefaultRefCaptureNode* clone = new DefaultRefCaptureNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DefaultRefCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultCopyCaptureNode::DefaultCopyCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultCopyCaptureNode, sourcePos_)
{
}

std::expected<Node*, int> DefaultCopyCaptureNode::Clone() const
{
    DefaultCopyCaptureNode* clone = new DefaultCopyCaptureNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void DefaultCopyCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ByRefCaptureNode::ByRefCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::byRefCaptureNode, sourcePos_)
{
}

std::expected<Node*, int> ByRefCaptureNode::Clone() const
{
    ByRefCaptureNode* clone = new ByRefCaptureNode(GetSourcePos());
    return std::expected<Node*, int>(clone);
}

void ByRefCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SimpleCaptureNode::SimpleCaptureNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::simpleCaptureNode, sourcePos_)
{
}

SimpleCaptureNode::SimpleCaptureNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* byRefCapture_, Node* ellipsis_) :
    CompoundNode(NodeKind::simpleCaptureNode, sourcePos_), identifier(identifier_), byRefCapture(byRefCapture_), ellipsis(ellipsis_)
{
}

std::expected<Node*, int> SimpleCaptureNode::Clone() const
{
    Node* clonedByRefCapture = nullptr;
    if (byRefCapture)
    {
        std::expected<Node*, int> b = byRefCapture->Clone();
        if (!b) return b;
        clonedByRefCapture = *b;
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        std::expected<Node*, int> e = ellipsis->Clone();
        if (!e) return e;
        clonedEllipsis = *e;
    }
    std::expected<Node*, int> i = identifier->Clone();
    if (!i) return i;
    SimpleCaptureNode* clone = new SimpleCaptureNode(GetSourcePos(), *i, clonedByRefCapture, clonedEllipsis);
    return std::expected<Node*, int>(clone);
}

void SimpleCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> SimpleCaptureNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(identifier.get());
    if (!rv) return rv;
    rv = writer.Write(byRefCapture.get());
    if (!rv) return rv;
    rv = writer.Write(ellipsis.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> SimpleCaptureNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    identifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    byRefCapture.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ellipsis.reset(*nrv);
    return std::expected<bool, int>(true);
}

CurrentObjectCopyCapture::CurrentObjectCopyCapture(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::currentObjectCopyCapture, sourcePos_)
{
}

CurrentObjectCopyCapture::CurrentObjectCopyCapture(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& thisPos_) : CompoundNode(NodeKind::currentObjectCopyCapture, sourcePos_), thisPos(thisPos_)
{
}

std::expected<Node*, int> CurrentObjectCopyCapture::Clone() const
{
    CurrentObjectCopyCapture* clone = new CurrentObjectCopyCapture(GetSourcePos(), thisPos);
    return std::expected<Node*, int>(clone);
}

void CurrentObjectCopyCapture::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CurrentObjectCopyCapture::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(thisPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CurrentObjectCopyCapture::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    thisPos = *posRv;
    return std::expected<bool, int>(true);
}

CurrentObjectByRefCapture::CurrentObjectByRefCapture(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::currentObjectByRefCapture, sourcePos_)
{
}

CurrentObjectByRefCapture::CurrentObjectByRefCapture(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& thisPos_) : CompoundNode(NodeKind::currentObjectByRefCapture, sourcePos_), thisPos(thisPos_)
{
}

std::expected<Node*, int> CurrentObjectByRefCapture::Clone() const
{
    CurrentObjectByRefCapture* clone = new CurrentObjectByRefCapture(GetSourcePos(), thisPos);
    return std::expected<Node*, int>(clone);
}

void CurrentObjectByRefCapture::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> CurrentObjectByRefCapture::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(thisPos);
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> CurrentObjectByRefCapture::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<soul::ast::SourcePos, int> posRv = reader.ReadSourcePos();
    if (!posRv) return std::unexpected<int>(posRv.error());
    thisPos = *posRv;
    return std::expected<bool, int>(true);
}

InitCaptureNode::InitCaptureNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::initCaptureNode, sourcePos_)
{
}

InitCaptureNode::InitCaptureNode(const soul::ast::SourcePos& sourcePos_, Node* identifier_, Node* initializer_, Node* byRefCapture_, Node* ellipsis_) :
    CompoundNode(NodeKind::initCaptureNode, sourcePos_), identifier(identifier_), initializer(initializer_), byRefCapture(byRefCapture_), ellipsis(ellipsis_)
{
}

std::expected<Node*, int> InitCaptureNode::Clone() const
{
    Node* clonedByRefCapture = nullptr;
    if (byRefCapture)
    {
        std::expected<Node*, int> b = byRefCapture->Clone();
        if (!b) return b;
        clonedByRefCapture = *b;
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        std::expected<Node*, int> e = ellipsis->Clone();
        if (!e) return e;
        clonedEllipsis = *e;
    }
    std::expected<Node*, int> i = identifier->Clone();
    if (!i) return i;
    std::expected<Node*, int> n = initializer->Clone();
    if (!n) return n;
    InitCaptureNode* clone = new InitCaptureNode(GetSourcePos(), *i, *n, clonedByRefCapture, clonedEllipsis);
    return std::expected<Node*, int>(clone);
}

void InitCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> InitCaptureNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(identifier.get());
    if (!rv) return rv;
    rv = writer.Write(initializer.get());
    if (!rv) return rv;
    rv = writer.Write(byRefCapture.get());
    if (!rv) return rv;
    rv = writer.Write(ellipsis.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> InitCaptureNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    identifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    initializer.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    byRefCapture.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    ellipsis.reset(*nrv);
    return std::expected<bool, int>(true);
}

LambdaDeclaratorNode::LambdaDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::lambdaDeclaratorNode, sourcePos_)
{
}

LambdaDeclaratorNode::LambdaDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* parameterList_, Node* specifiers_, Node* requiresClause_) :
    CompoundNode(NodeKind::lambdaDeclaratorNode, sourcePos_), parameterList(parameterList_), specifiers(specifiers_), requiresClause(requiresClause_)
{
}

std::expected<Node*, int> LambdaDeclaratorNode::Clone() const
{
    Node* clonedRequiresClause = nullptr;
    if (requiresClause)
    {
        std::expected<Node*, int> r = requiresClause->Clone();
        if (!r) return r;
        clonedRequiresClause = *r;
    }
    Node* clonedParameterList = nullptr;
    if (parameterList)
    {
        std::expected<Node*, int> p = parameterList->Clone();
        if (!p) return p;
        clonedParameterList = *p;
    }
    std::expected<Node*, int> s = specifiers->Clone();
    if (!s) return s;
    LambdaDeclaratorNode* clone = new LambdaDeclaratorNode(GetSourcePos(), clonedParameterList, *s, clonedRequiresClause);
    return std::expected<Node*, int>(clone);
}

void LambdaDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LambdaDeclaratorNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(parameterList.get());
    if (!rv) return rv;
    rv = writer.Write(specifiers.get());
    if (!rv) return rv;
    rv = writer.Write(requiresClause.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LambdaDeclaratorNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    parameterList.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    specifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    requiresClause.reset(*nrv);
    return std::expected<bool, int>(true);
}

LambdaSpecifiersNode::LambdaSpecifiersNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::lambdaSpecifiersNode, sourcePos_)
{
}

LambdaSpecifiersNode::LambdaSpecifiersNode(const soul::ast::SourcePos& sourcePos_, Node* declSpecifiers_, Node* noexceptSpecifier_, Node* attributes_, Node* trailingReturnType_) :
    CompoundNode(NodeKind::lambdaSpecifiersNode, sourcePos_), declSpecifiers(declSpecifiers_), noexceptSpecifier(noexceptSpecifier_), attributes(attributes_), trailingReturnType(trailingReturnType_)
{
}

std::expected<Node*, int> LambdaSpecifiersNode::Clone() const
{
    Node* clonedDeclSpecifiers = nullptr;
    if (declSpecifiers)
    {
        std::expected<Node*, int> d = declSpecifiers->Clone();
        if (!d) return d;
        clonedDeclSpecifiers = *d;
    }
    Node* clonedNoexceptSpecifier = nullptr;
    if (noexceptSpecifier)
    {
        std::expected<Node*, int> n = noexceptSpecifier->Clone();
        if (!n) return n;
        clonedNoexceptSpecifier = *n;
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        std::expected<Node*, int> a = attributes->Clone();
        if (!a) return a;
        clonedAttributes = *a;
    }
    Node* clonedTrailingReturnType = nullptr;
    if (trailingReturnType)
    {
        std::expected<Node*, int> t = trailingReturnType->Clone();
        if (!t) return t;
        clonedTrailingReturnType = *t;
    }
    LambdaSpecifiersNode* clone = new LambdaSpecifiersNode(GetSourcePos(), clonedDeclSpecifiers, clonedNoexceptSpecifier, clonedAttributes, clonedTrailingReturnType);
    return std::expected<Node*, int>(clone);
}

void LambdaSpecifiersNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LambdaSpecifiersNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(declSpecifiers.get());
    if (!rv) return rv;
    rv = writer.Write(noexceptSpecifier.get());
    if (!rv) return rv;
    rv = writer.Write(attributes.get());
    if (!rv) return rv;
    rv = writer.Write(trailingReturnType.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LambdaSpecifiersNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    declSpecifiers.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    noexceptSpecifier.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    attributes.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    trailingReturnType.reset(*nrv);
    return std::expected<bool, int>(true);
}

bool LambdaSpecifiersNode::IsEmpty() const
{
    return !declSpecifiers && !noexceptSpecifier && !attributes && !trailingReturnType;
}

LambdaTemplateParamsNode::LambdaTemplateParamsNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::lambdaTemplateParamsNode, sourcePos_)
{
}

LambdaTemplateParamsNode::LambdaTemplateParamsNode(const soul::ast::SourcePos& sourcePos_, Node* templateParams_, Node* requiresClause_) :
    CompoundNode(NodeKind::lambdaTemplateParamsNode, sourcePos_), templateParams(templateParams_), requiresClause(requiresClause_)
{
}

std::expected<Node*, int> LambdaTemplateParamsNode::Clone() const
{
    Node* clonedRequiresClause = nullptr;
    if (requiresClause)
    {
        std::expected<Node*, int> r = requiresClause->Clone();
        if (!r) return r;
        clonedRequiresClause = *r;
    }
    std::expected<Node*, int> t = templateParams->Clone();
    if (!t) return t;
    LambdaTemplateParamsNode* clone = new LambdaTemplateParamsNode(GetSourcePos(), *t, clonedRequiresClause);
    return std::expected<Node*, int>(clone);
}

void LambdaTemplateParamsNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

std::expected<bool, int> LambdaTemplateParamsNode::Write(Writer& writer)
{
    std::expected<bool, int> rv = CompoundNode::Write(writer);
    if (!rv) return rv;
    rv = writer.Write(templateParams.get());
    if (!rv) return rv;
    rv = writer.Write(requiresClause.get());
    if (!rv) return rv;
    return std::expected<bool, int>(true);
}

std::expected<bool, int> LambdaTemplateParamsNode::Read(Reader& reader)
{
    std::expected<bool, int> rv = CompoundNode::Read(reader);
    if (!rv) return rv;
    std::expected<Node*, int> nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    templateParams.reset(*nrv);
    nrv = reader.ReadNode();
    if (!nrv) return std::unexpected<int>(nrv.error());
    requiresClause.reset(*nrv);
    return std::expected<bool, int>(true);
}

} // namespace otava::ast
