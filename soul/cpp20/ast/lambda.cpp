// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.lambda;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

LambdaExpressionNode::LambdaExpressionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::lambdaExpressionNode, sourcePos_)
{
}

LambdaExpressionNode::LambdaExpressionNode(const soul::ast::SourcePos& sourcePos_, Node* introducer_, Node* templateParams_, Node* declarator_, Node* body_) :
    CompoundNode(NodeKind::lambdaExpressionNode, sourcePos_), introducer(introducer_), templateParams(templateParams_), declarator(declarator_), body(body_)
{
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

void LambdaCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultRefCaptureNode::DefaultRefCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultRefCaptureNode, sourcePos_)
{
}

void DefaultRefCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultCopyCaptureNode::DefaultCopyCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultCopyCaptureNode, sourcePos_)
{
}

void DefaultCopyCaptureNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ByRefCaptureNode::ByRefCaptureNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::byRefCaptureNode, sourcePos_)
{
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

} // namespace soul::cpp20::ast
