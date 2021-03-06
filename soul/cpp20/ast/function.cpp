// =================================
// Copyright (c) 2022 Seppo Laakko
// Distributed under the MIT license
// =================================

module soul.cpp20.ast.function;

import soul.cpp20.ast.visitor;
import soul.cpp20.ast.reader;
import soul.cpp20.ast.writer;

namespace soul::cpp20::ast {

FunctionDefinitionNode::FunctionDefinitionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::functionDefinitionNode, sourcePos_)
{
}

FunctionDefinitionNode::FunctionDefinitionNode(const soul::ast::SourcePos& sourcePos_, Node* attributes_, Node* declSpecifiers_, Node* declarator_, Node* specifiers_, Node* functionBody_) :
    CompoundNode(NodeKind::functionDefinitionNode, sourcePos_), attributes(attributes_), declSpecifiers(declSpecifiers_), declarator(declarator_), specifiers(specifiers_), functionBody(functionBody_)
{
}

void FunctionDefinitionNode::ResetFunctionBody(Node* functionBody_)
{
    functionBody.reset(functionBody_);
}

void FunctionDefinitionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionDefinitionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(declSpecifiers.get());
    writer.Write(declarator.get());
    writer.Write(specifiers.get());
    writer.Write(functionBody.get());
}

void FunctionDefinitionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    attributes.reset(reader.ReadNode());
    declSpecifiers.reset(reader.ReadNode());
    declarator.reset(reader.ReadNode());
    specifiers.reset(reader.ReadNode());
    functionBody.reset(reader.ReadNode());
}

FunctionBodyNode::FunctionBodyNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::functionBodyNode, sourcePos_, nullptr)
{
}

FunctionBodyNode::FunctionBodyNode(const soul::ast::SourcePos& sourcePos_, Node* compoundStatement_) : UnaryNode(NodeKind::functionBodyNode, sourcePos_, compoundStatement_)
{
}

void FunctionBodyNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultNode::DefaultNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::defaultNode, sourcePos_)
{
}

void DefaultNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeleteNode::DeleteNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::deleteNode, sourcePos_)
{
}

void DeleteNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DefaultedOrDeletedFunctionNode::DefaultedOrDeletedFunctionNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::defaultedOrDeletedFunctionNode, sourcePos_)
{
}

DefaultedOrDeletedFunctionNode::DefaultedOrDeletedFunctionNode(const soul::ast::SourcePos& sourcePos_, Node* assign_, Node* defaultOrDelete_, Node* semicolon_) :
    CompoundNode(NodeKind::defaultedOrDeletedFunctionNode, sourcePos_), assign(assign_), defaultOrDelete(defaultOrDelete_), semicolon(semicolon_)
{
}

void DefaultedOrDeletedFunctionNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DefaultedOrDeletedFunctionNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(assign.get());
    writer.Write(defaultOrDelete.get());
    writer.Write(semicolon.get());
}

void DefaultedOrDeletedFunctionNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    assign.reset(reader.ReadNode());
    defaultOrDelete.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

NoDeclSpecFunctionDeclarationNode::NoDeclSpecFunctionDeclarationNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::noDeclSpecFunctionDeclarationNode, sourcePos_)
{
}

NoDeclSpecFunctionDeclarationNode::NoDeclSpecFunctionDeclarationNode(const soul::ast::SourcePos& sourcePos_, Node* declarator_, Node* attributes_, Node* semicolon_) :
    CompoundNode(NodeKind::noDeclSpecFunctionDeclarationNode, sourcePos_), declarator(declarator_), attributes(attributes_), semicolon(semicolon_)
{
}

void NoDeclSpecFunctionDeclarationNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NoDeclSpecFunctionDeclarationNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(declarator.get());
    writer.Write(attributes.get());
    writer.Write(semicolon.get());
}

void NoDeclSpecFunctionDeclarationNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    declarator.reset(reader.ReadNode());
    attributes.reset(reader.ReadNode());
    semicolon.reset(reader.ReadNode());
}

OperatorNode::OperatorNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::operatorNode, sourcePos_)
{
}

void OperatorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

NewArrayOpNode::NewArrayOpNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::newArrayOpNode, sourcePos_)
{
}

NewArrayOpNode::NewArrayOpNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::newArrayOpNode, sourcePos_), lbPos(lbPos_), rbPos(rbPos_)
{
}

void NewArrayOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void NewArrayOpNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(lbPos);
    writer.Write(rbPos);

}

void NewArrayOpNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

NewOpNode::NewOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::newOpNode, sourcePos_)
{
}

void NewOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

DeleteArrayOpNode::DeleteArrayOpNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::deleteArrayOpNode, sourcePos_)
{
}

DeleteArrayOpNode::DeleteArrayOpNode(const soul::ast::SourcePos& sourcePos_, const soul::ast::SourcePos& lbPos_, const soul::ast::SourcePos& rbPos_) :
    CompoundNode(NodeKind::deleteArrayOpNode, sourcePos_)
{
}

void DeleteArrayOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void DeleteArrayOpNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(lbPos);
    writer.Write(rbPos);
}

void DeleteArrayOpNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    lbPos = reader.ReadSourcePos();
    rbPos = reader.ReadSourcePos();
}

DeleteOpNode::DeleteOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::deleteOpNode, sourcePos_)
{
}

void DeleteOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

CoAwaitOpNode::CoAwaitOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::coAwaitOpNode, sourcePos_)
{
}

void CoAwaitOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

InvokeOpNode::InvokeOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::invokeOpNode, sourcePos_)
{
}

void InvokeOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

SubscriptOpNode::SubscriptOpNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::subscriptOpNode, sourcePos_)
{
}

void SubscriptOpNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

OperatorFunctionIdNode::OperatorFunctionIdNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::operatorFnIdNode, sourcePos_, nullptr, nullptr)
{
}

OperatorFunctionIdNode::OperatorFunctionIdNode(const soul::ast::SourcePos& sourcePos_, Node* operatorKwNode_, Node* op_) :
    BinaryNode(NodeKind::operatorFnIdNode, sourcePos_, operatorKwNode_, op_)
{
}

void OperatorFunctionIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConversionFunctionIdNode::ConversionFunctionIdNode(const soul::ast::SourcePos& sourcePos_) : BinaryNode(NodeKind::conversionFnIdNode, sourcePos_, nullptr, nullptr)
{
}

ConversionFunctionIdNode::ConversionFunctionIdNode(const soul::ast::SourcePos& sourcePos_, Node* operatorKwNode_, Node* conversionTypeId_) :
    BinaryNode(NodeKind::conversionFnIdNode, sourcePos_, operatorKwNode_, conversionTypeId_)
{
}

void ConversionFunctionIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ConversionTypeIdNode::ConversionTypeIdNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conversionTypeIdNode, sourcePos_)
{
}

ConversionTypeIdNode::ConversionTypeIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeSpecifierSeq_, Node* conversionDeclarator_) :
    CompoundNode(NodeKind::conversionTypeIdNode, sourcePos_), typeSpecifierSeq(typeSpecifierSeq_), conversionDeclarator(conversionDeclarator_)
{
}

void ConversionTypeIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConversionTypeIdNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(typeSpecifierSeq.get());
    writer.Write(conversionDeclarator.get());
}

void ConversionTypeIdNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    typeSpecifierSeq.reset(reader.ReadNode());
    conversionDeclarator.reset(reader.ReadNode());
}

ConversionDeclaratorNode::ConversionDeclaratorNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::conversionDeclaratorNode, sourcePos_)
{
}

ConversionDeclaratorNode::ConversionDeclaratorNode(const soul::ast::SourcePos& sourcePos_, Node* ptrOp_, Node* conversionDeclarator_) :
    CompoundNode(NodeKind::conversionDeclaratorNode, sourcePos_), ptrOp(ptrOp_), conversionDeclarator(conversionDeclarator_)
{
}

void ConversionDeclaratorNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ConversionDeclaratorNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(ptrOp.get());
    writer.Write(conversionDeclarator.get());
}

void ConversionDeclaratorNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    ptrOp.reset(reader.ReadNode());
    conversionDeclarator.reset(reader.ReadNode());
}

DestructorIdNode::DestructorIdNode(const soul::ast::SourcePos& sourcePos_) : UnaryNode(NodeKind::destructorIdNode, sourcePos_, nullptr)
{
}

DestructorIdNode::DestructorIdNode(const soul::ast::SourcePos& sourcePos_, Node* typeName_) : UnaryNode(NodeKind::destructorIdNode, sourcePos_, typeName_)
{
}

void DestructorIdNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

ParameterNode::ParameterNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::parameterNode, sourcePos_)
{
}

void ParameterNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ParameterNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(attributes.get());
    writer.Write(declSpecifiers.get());
    writer.Write(declarator.get());
    writer.Write(assign.get());
    writer.Write(initializer.get());
}

void ParameterNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    attributes.reset(reader.ReadNode());
    declSpecifiers.reset(reader.ReadNode());
    declarator.reset(reader.ReadNode());
    assign.reset(reader.ReadNode());
    initializer.reset(reader.ReadNode());
}

void ParameterNode::SetAttributes(Node* attributes_)
{
    attributes.reset(attributes_);
}

void ParameterNode::SetDeclSpecifiers(Node* declSpecifiers_)
{
    declSpecifiers.reset(declSpecifiers_);
}

void ParameterNode::SetDeclarator(Node* declarator_)
{
    declarator.reset(declarator_);
}

void ParameterNode::SetAssign(Node* assign_)
{
    assign.reset(assign_);
}

void ParameterNode::SetInitializer(Node* initializer_)
{
    initializer.reset(initializer_);
}

ParameterListNode::ParameterListNode(const soul::ast::SourcePos& sourcePos_) : ListNode(NodeKind::parameterListNode, sourcePos_)
{
}

void ParameterListNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void ParameterListNode::Write(Writer& writer)
{
    ListNode::Write(writer);
    writer.Write(lpPos);
    writer.Write(rpPos);
}

void ParameterListNode::Read(Reader& reader)
{
    ListNode::Read(reader);
    lpPos = reader.ReadSourcePos();
    rpPos = reader.ReadSourcePos();
}

NoexceptNode::NoexceptNode(const soul::ast::SourcePos& sourcePos_) : Node(NodeKind::noexceptNode, sourcePos_)
{
}

void NoexceptNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

FunctionTryBlockNode::FunctionTryBlockNode(const soul::ast::SourcePos& sourcePos_) : CompoundNode(NodeKind::functionTryBlock, sourcePos_)
{
}

FunctionTryBlockNode::FunctionTryBlockNode(const soul::ast::SourcePos& sourcePos_, Node* ctorInitializer_, Node* tryBlock_, Node* handlers_) :
    CompoundNode(NodeKind::functionTryBlock, sourcePos_), ctorInitializer(ctorInitializer_), tryBlock(tryBlock_), handlers(handlers_)
{
}

void FunctionTryBlockNode::Accept(Visitor& visitor)
{
    visitor.Visit(*this);
}

void FunctionTryBlockNode::Write(Writer& writer)
{
    CompoundNode::Write(writer);
    writer.Write(ctorInitializer.get());
    writer.Write(tryBlock.get());
    writer.Write(handlers.get());
}

void FunctionTryBlockNode::Read(Reader& reader)
{
    CompoundNode::Read(reader);
    ctorInitializer.reset(reader.ReadNode());
    tryBlock.reset(reader.ReadNode());
    handlers.reset(reader.ReadNode());
}

} // namespace soul::cpp20::ast
