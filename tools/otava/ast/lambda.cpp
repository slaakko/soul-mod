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

void LambdaExpressionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(introducer.get());
    writer.Write(templateParams.get());
    writer.Write(declarator.get());
    writer.Write(body.get());
}

void LambdaExpressionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    introducer.reset(reader.ReadNode());
    templateParams.reset(reader.ReadNode());
    declarator.reset(reader.ReadNode());
    body.reset(reader.ReadNode());
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

void LambdaIntroducerNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(capture.get());
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void LambdaIntroducerNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    capture.reset(reader.ReadNode());
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
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

void SimpleCaptureNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(identifier.get());
    writer.Write(byRefCapture.get());
    writer.Write(ellipsis.get());
}

void SimpleCaptureNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    identifier.reset(reader.ReadNode());
    byRefCapture.reset(reader.ReadNode());
    ellipsis.reset(reader.ReadNode());
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

void CurrentObjectCopyCapture::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(thisPos);
}

void CurrentObjectCopyCapture::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    thisPos = reader.ReadSourcePos();
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

void CurrentObjectByRefCapture::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(thisPos);
}

void CurrentObjectByRefCapture::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    thisPos = reader.ReadSourcePos();
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

void InitCaptureNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(identifier.get());
    writer.Write(initializer.get());
    writer.Write(byRefCapture.get());
    writer.Write(ellipsis.get());
}

void InitCaptureNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    identifier.reset(reader.ReadNode());
    initializer.reset(reader.ReadNode());
    byRefCapture.reset(reader.ReadNode());
    ellipsis.reset(reader.ReadNode());
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

void LambdaDeclaratorNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(parameterList.get());
    writer.Write(specifiers.get());
    writer.Write(requiresClause.get());
}

void LambdaDeclaratorNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    parameterList.reset(reader.ReadNode());
    specifiers.reset(reader.ReadNode());
    requiresClause.reset(reader.ReadNode());
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

void LambdaSpecifiersNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declSpecifiers.get());
    writer.Write(noexceptSpecifier.get());
    writer.Write(attributes.get());
    writer.Write(trailingReturnType.get());
}

void LambdaSpecifiersNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declSpecifiers.reset(reader.ReadNode());
    noexceptSpecifier.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    trailingReturnType.reset(reader.ReadNode());
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

void LambdaTemplateParamsNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(templateParams.get());
    writer.Write(requiresClause.get());
}

void LambdaTemplateParamsNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    templateParams.reset(reader.ReadNode());
    requiresClause.reset(reader.ReadNode());
}

} // namespace otava::ast
