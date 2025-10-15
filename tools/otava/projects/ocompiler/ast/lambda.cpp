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

Node* LambdaExpressionNode::Clone() const
{
    Node* clonedTemplateParams = nullptr;
    if (templateParams)
    {
        clonedTemplateParams = templateParams->Clone();
    }
    LambdaExpressionNode* clone = new LambdaExpressionNode(GetSourcePos(), introducer->Clone(), clonedTemplateParams, declarator->Clone(), body->Clone());
    return clone;
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

Node* LambdaIntroducerNode::Clone() const
{
    Node* clonedCapture = nullptr;
    if (capture)
    {
        clonedCapture = capture->Clone();
    }
    LambdaIntroducerNode* clone = new LambdaIntroducerNode(GetSourcePos(), clonedCapture, lbPos, rbPos);
    return clone;
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

Node* LambdaCaptureNode::Clone() const
{
    LambdaCaptureNode* clone = new LambdaCaptureNode(GetSourcePos());
    for (const auto& node : Nodes())
    {
        clone->AddNode(node->Clone());
    }
    return clone;
}

void LambdaCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultRefCaptureNode::DefaultRefCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultRefCaptureNode, sourcePos_)
{
}

Node* DefaultRefCaptureNode::Clone() const
{
    DefaultRefCaptureNode* clone = new DefaultRefCaptureNode(GetSourcePos());
    return clone;
}

void DefaultRefCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultCopyCaptureNode::DefaultCopyCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultCopyCaptureNode, sourcePos_)
{
}

Node* DefaultCopyCaptureNode::Clone() const
{
    DefaultCopyCaptureNode* clone = new DefaultCopyCaptureNode(GetSourcePos());
    return clone;
}

void DefaultCopyCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ByRefCaptureNode::ByRefCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::byRefCaptureNode, sourcePos_)
{
}

Node* ByRefCaptureNode::Clone() const
{
    ByRefCaptureNode* clone = new ByRefCaptureNode(GetSourcePos());
    return clone;
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

Node* SimpleCaptureNode::Clone() const
{
    Node* clonedByRefCapture = nullptr;
    if (byRefCapture)
    {
        clonedByRefCapture = byRefCapture->Clone();
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        clonedEllipsis = ellipsis->Clone();
    }
    SimpleCaptureNode* clone = new SimpleCaptureNode(GetSourcePos(), identifier->Clone(), clonedByRefCapture, clonedEllipsis);
    return clone;
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

Node* CurrentObjectCopyCapture::Clone() const
{
    CurrentObjectCopyCapture* clone = new CurrentObjectCopyCapture(GetSourcePos(), thisPos);
    return clone;
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

Node* CurrentObjectByRefCapture::Clone() const
{
    CurrentObjectByRefCapture* clone = new CurrentObjectByRefCapture(GetSourcePos(), thisPos);
    return clone;
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

Node* InitCaptureNode::Clone() const
{
    Node* clonedByRefCapture = nullptr;
    if (byRefCapture)
    {
        clonedByRefCapture = byRefCapture->Clone();
    }
    Node* clonedEllipsis = nullptr;
    if (ellipsis)
    {
        clonedEllipsis = ellipsis->Clone();
    }
    InitCaptureNode* clone = new InitCaptureNode(GetSourcePos(), identifier->Clone(), initializer->Clone(), clonedByRefCapture, clonedEllipsis);
    return clone;
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

Node* LambdaDeclaratorNode::Clone() const
{
    Node* clonedRequiresClause = nullptr;
    if (requiresClause)
    {
        clonedRequiresClause = requiresClause->Clone();
    }
    Node* clonedParameterList = nullptr;
    if (parameterList)
    {
        clonedParameterList = parameterList->Clone();
    }
    LambdaDeclaratorNode* clone = new LambdaDeclaratorNode(GetSourcePos(), clonedParameterList, specifiers->Clone(), clonedRequiresClause);
    return clone;
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

Node* LambdaSpecifiersNode::Clone() const
{
    Node* clonedDeclSpecifiers = nullptr;
    if (declSpecifiers)
    {
        clonedDeclSpecifiers = declSpecifiers->Clone();
    }
    Node* clonedNoexceptSpecifier = nullptr;
    if (noexceptSpecifier)
    {
        clonedNoexceptSpecifier = noexceptSpecifier->Clone();
    }
    Node* clonedAttributes = nullptr;
    if (attributes)
    {
        clonedAttributes = attributes->Clone();
    }
    Node* clonedTrailingReturnType = nullptr;
    if (trailingReturnType)
    {
        clonedTrailingReturnType = trailingReturnType->Clone();
    }
    LambdaSpecifiersNode* clone = new LambdaSpecifiersNode(GetSourcePos(), clonedDeclSpecifiers, clonedNoexceptSpecifier, clonedAttributes, clonedTrailingReturnType);
    return clone;
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

Node* LambdaTemplateParamsNode::Clone() const
{
    Node* clonedRequiresClause = nullptr;
    if (requiresClause)
    {
        clonedRequiresClause = requiresClause->Clone();
    }
    LambdaTemplateParamsNode* clone = new LambdaTemplateParamsNode(GetSourcePos(), templateParams->Clone(), clonedRequiresClause);
    return clone;
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
